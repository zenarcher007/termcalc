#!/usr/bin/env bash
set -e
### Be sure to follow the documented instructions to build the Microsoft "Pict" testing tool!

### For the compatibility tests, you will need a machine that can build docker images. This will only create a number of
# Dockerfile.(os) images, corresponding with base images to avoid re-installing software,
# one for each supported OS (for example, if there is a Dockerfile.alpine and a Dockerfile.alpine,
# 4 images will be created on your system, not one for each test, and each prepended with test_termcalc_ or test_termcalc_base_).
# A Dockerfile.base_OS image is the base image

# This works by building a base image of an OS with everything installed, and then for each compiler test, the "opposite" compiler
# is deleted upon build. For example, if the current compiler to test is "clang++", the $(which "g++") compiler is deleted.
# Note that system assumes that only two compilers "exist in the world". It is likely imperfect but this works.

PROJ_ROOT="../"
cd "$PROJ_ROOT" || exit

if [[ -z "$DOCKER_CMD" ]]; then
  DOCKER_CMD="docker"
fi
echo "Using docker command: $DOCKER_CMD"

function master_test() {
  OS="$1"; TERM="$2"; COMPILER="$3"; CPPSTANDARD="$4"
  # Check if base image currently exists:
  grep 'INSPECT_TRUE' >/dev/null <<< "$($DOCKER_CMD image inspect "test_termcalc_base_$OS":latest && echo INSPECT_TRUE || echo INSPECT_FALSE)"
  if [[ "$?" == "0" ]]; then
    echo  "  > Base image for $OS already exists, skipping build."
  else
    echo  "  > Building base image... "
    $DOCKER_CMD  build  -t  "test_termcalc_base_$OS"  --build-arg OS="$OS"  --build-arg TERM="$TERM"  --build-arg COMPILER="$COMPILER"  --build-arg CPPSTANDARD="$CPPSTANDARD"  $EXTRA_DOCKER_BUILD_ARGS -f  "CompatibilityTests/Dockerfile.base_$OS" .
    if [[  "$?"  != 0 ]]; then
      echo  >&2  "ERROR: Failed to build base image for OS: $OS, TERM: $TERM, COMPILER: $COMPILER, CPPSTANDARD: $CPPSTANDARD"
      exit  1
    fi
    echo  "  > Done."
  fi

  echo "  > Testing build of OS: $OS, TERM: $TERM, COMPILER: $COMPILER, CPPSTANDARD: $CPPSTANDARD"
  mkdir -p "/tmp/termcalc_docker_build_logs"
  dirId="os_$OS_term_$TERM_compiler_$COMPILER_std_$CPPSTANDARD_$(uuidgen)"
  opposite_compiler="$(if [ "${COMPILER}" = "clang++" ]; then echo g++; else echo clang++; fi)"
  $DOCKER_CMD build -f "CompatibilityTests/Dockerfile.$OS" -t "test_termcalc_build_$(tr '[:upper:]' '[:lower:]' <<< "$OS")" . --build-arg OPPOSITE_COMPILER="$opposite_compiler" --build-arg TERM="$TERM" --build-arg COMPILER="$COMPILER" --build-arg CPPSTANDARD="$CPPSTANDARD" $EXTRA_DOCKER_BUILD_ARGS &>"/tmp/termcalc_docker_build_logs/$dirId.log" && echo "IMAGE BUILT SUCCESSFULLY!"
  if [[ $? -ne 0 ]]; then
    echo "TEST FAILED! Here are the logs:"
    cat "/tmp/termcalc_docker_build_logs/$dirId.log"
    for i in {1..10}; do echo ; done
    exit 1
  fi
}
export -f master_test

$DOCKER_CMD run -i --rm -v ./:/var/pict:Z pict CompatibilityTests/pictmodel.txt 2>&1 | tail +2 | while IFS= read -r line; do
  # https://stackoverflow.com/a/11003457
  xargs -I {} bash -c 'master_test $@' _ {} <<< "$line"
done