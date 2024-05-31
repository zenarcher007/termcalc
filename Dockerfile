FROM alpine as builder

# Install make, c++ tools, etc
RUN apk update && apk add --no-cache \
    build-base \
    curl \
    git \
    libtool \
    linux-headers \
    zlib-dev \
    bash \
    ncurses-dev \
    ncurses-libs \
    clang \
    make

# Add user / group: https://stackoverflow.com/a/49955098
RUN addgroup -S termcalc && adduser -S termcalc -G termcalc
USER termcalc

COPY --chown=termcalc:termcalc . /home/termcalc/termcalc
WORKDIR /home/termcalc/termcalc
RUN make clean && touch termcalc.cpp && make test release
#RUN make release && touch termcalc.cpp && make clean release

ENTRYPOINT ["/home/termcalc/termcalc/release/termcalc"]
#ENTRYPOINT ["/bin/bash"]
#ENTRYPOINT ["/bin/bash", "-c", "make test && /home/termcalc/termcalc/release/termcalc"]
#["/home/termcalc/termcalc/release/termcalc"]
#bash -c "/home/termcalc/termcalc/release/termcalc"
#["bash", "-c", "/home/termcalc/termcalc/release/termcalc"]

#FROM alpine

#RUN addgroup -S termcalc && adduser -S termcalc -G termcalc

#WORKDIR /home/termcalc
#COPY --from=builder /home/termcalc/termcalc/release/termcalc /usr/local/bin
#USER termcalc

#ENTRYPOINT ["/usr/local/bin/termcalc"]

