# TermCalc
### A project for Software Testing class at Knox College


### Test requirements

* There should be a UI displayed with all available buttons
* The 2nd and alpha buttons should change the functionalities of all buttons accordingly
* The user should be able to scroll back and forth with the arrow keys, and go to previous and next inputs with the up/down keys
* The calculator should not respond to any button and the screen should be blank until the user presses the "on" button
* The calculator should throw an error for dividing by zero


### User story specifications
* The calculator should support clicking buttons with the mouse and selecting them with the keyboard, and it should highlight activated buttons
* The program should throw an error and not start if the size of the terminal is smaller than needed to fit the screen representation and all buttons

### Implementation details
* There will be a text input buffer. When the text typed matches that of any button (on the normal keyboard), that button will be activated. An unordered_map from button names to buttons will be used for quick search
* Each button will have a length of 4. There will be an overlap that goes 4 chars outside of the screen area for the additional "clear", operations, and enter buttons.