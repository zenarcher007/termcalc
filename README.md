# TermCalc
### A project for Software Testing class at Knox College

# TermCalc
### A project for Software Testing class at Knox College


### Test requirements

### From a user perspective (higher-level)
* Clicking a button different from that which is currently selected should both select and activate it.

#### FocusTracker
* A focustracker should track which widget is currently selected, and pass calls to type() to the underlying widget.
* You should be able to add a mapping from one selected widget to another based on a detected keypress in its call to type(), and these mappings should be used to switch widgets based on key presses.
* It should respond to mouse presses by selecting the widget at the location of its window.
* type() should return true if the underlying widget handled a click or key press request, and select it if so, or else do nothing.

#### ButtonArray
* A buttonarray (which inherits a focustracker), should store widgets positionally, and be able to add and reference widgets by a location.
* When adding a new widget, a buttonarray should add arrow key adjacencies to positionally neighboring widgets, and those widgets should have the opposite-key adjacency mapping back to the new widget.
* There should be a console. This console should display typed characters and wrap to the next line for long lines. Each new line for user input will start with a ‘>’ character. Pressing the enter key on an empty line should submit the current expression

#### UIConsole
* The console should have a '>' character as the first character for every new line.
* The console (inheriting a UIWidget) should respond to type() requests by outputting the given characters on the screen, one by one (if they are not "special characters or sequences", like clear, submit, etc). After outputting many characters, the corresponding text should be equal to a string containing all of the combined characters that were typed (noting that the last column is not used).
* Line wrapping should not affect the way it outputs text; it should simply go to the next line, and the resulting strings should still be equal.


### User story specifications
* The calculator should support clicking buttons with the mouse and selecting them with the keyboard, and it should highlight activated buttons, displaying typed characters in the console
* The console should support at least typing characters, and it should wrap to the next line for long lines. Each new line for user input will start with a '>' character. Pressing the enter key on an empty line should submit the current expression
* The calculator should support basic arithmetic operations (+,-,*,/), and basic trig and algebraic operations, as well as parentheses
* The calculator should at least return anything but a numerical result for syntax or calculation errors
* You should be able to clear the current line and restart your expression



### How to build and run:
* See "How to build pict" section of the report for instructions for building the PICT coverage tool.
* Build: ```docker build -t termcalc .```
* Run: ```docker run -t termcalc```
