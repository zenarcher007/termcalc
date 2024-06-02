# TermCalc
### A project for Software Testing class at Knox College


### Test requirements

* There should be a UI displayed with all available buttons
* The user should be able to scroll back and forth with the arrow keys, and go to previous and next inputs with the up/down keys
* The calculator should not respond to any button and the screen should be blank until the user presses the "on" button
* The calculator should throw an error for dividing by zero


### User story specifications
* The calculator should support clicking buttons with the mouse and selecting them with the keyboard, and it should highlight activated buttons, displaying typed characters in the console
* The console should support at least typing characters, and it should wrap to the next line for long lines. Each new line for user input will start with a '>' character. Pressing the enter key on an empty line should submit the current expression
* The calculator should support basic arithmetic operations (+,-,*,/) as well as parentheses


### How to build and run:
* See "How to build pict" section of the report for instructions for building the PICT coverage tool.
* Build: ```docker build -t termcalc .```
* Run: ```docker run -t termcalc```
