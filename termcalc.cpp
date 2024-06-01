#include "tinyexpr.h"
#include <ncurses.h>
#include <iostream>
#include "termcalc.h"
#include "uibutton.h"
#include "uiwidget.h"
#include "loctypes.h"
#include "widgetarray.h"
#include "focustracker.h"
#include "uiconsole.h"
#include <functional>
#include <atomic>
#include <unistd.h>

using namespace termcalc;

// Please note that all Points and Sizes, etc are in "Rows,Cols" to match with the odd way Curses does it!
class Calculator {
  private:
  std::unique_ptr<WidgetArray> numpad;
  std::unique_ptr<UIConsole> console;

  bool buttonCallback(std::string buttonName) {
    bool retVal = true;
    for(key_t ch : buttonName) {
      if(!console->type(ch)) // If any failed
        retVal = false;
    }
    console->draw();
    return retVal;
  }

  // Creates buttons 1-9
  std::unique_ptr<WidgetArray> initButtons(Point leftCorner, Size buttonSize) {
    
    std::unique_ptr<WidgetArray> wa = std::make_unique<WidgetArray>("Numpad", Size(4, 4));
    int num = 0;
    for (int row = 0; row < 3; ++row) {
      for (int col = 0; col < 3; ++col) {
        std::shared_ptr<UIWidget> button(new UIButton(std::to_string(++num).c_str()));
        std::function<bool(std::string)> callbackFunc = std::bind(&Calculator::buttonCallback, this, std::placeholders::_1);
        ((UIButton*) button.get())->setActivatorCallback(callbackFunc);
        wa->addWidgetAtPoint(Point(row, col), button);
        button->initWindow(Box(Point(leftCorner.row + row*buttonSize.rows, leftCorner.col + col*buttonSize.cols), buttonSize)); // Use constructor Box(Point, Size)
        //ptr->draw();
      }

      std::string buttonNames[7] = {"*", "/", "+", "-", ",", ".", "%"};
      Point locations[7] = {Point(0, 3), Point(1, 3), Point(2, 3), Point(3,3), Point(3, 0), Point(3, 1), Point(3, 2)};
      for(int i = 0; i < 7; ++i) {
        std::shared_ptr<UIWidget> button(new UIButton(buttonNames[i]));
        std::function<bool(std::string)> callbackFunc = std::bind(&Calculator::buttonCallback, this, std::placeholders::_1);
        ((UIButton*) button.get())->setActivatorCallback(callbackFunc);
        wa->addWidgetAtPoint(locations[i], button);
        button->initWindow(Box(Point(leftCorner.row + locations[i].row*buttonSize.rows, leftCorner.col + locations[i].col*buttonSize.cols), buttonSize)); // Use constructor Box(Point, Size)
      }
    }
    return wa;
  }

public:
  

  bool type(int ch, MEVENT* mevent = nullptr) {
    numpad->type(ch, mevent);
    //UIButton* b = (UIButton*) numpad->getFocusedWidget();
    //if(b) {
    //  b->draw();
    //}
    return false;
  }

  Calculator() { // Rows, Cols
    console = std::make_unique<UIConsole>("Console");
    console->initWindow(Box(Point(0, 0), Size(10, 25)));
    numpad = initButtons(Point(10, 0), Size(3, 3)); // Rows, Cols
  }

  void draw() {
    numpad->draw();
  }

};

int main(int argc, char** argv) {

  WINDOW* stdscr = initscr();
  wrefresh(stdscr);
  // Create a thread barrier and block it to ensure initscr() isn't called after the other functions
  // For some reason, without this, compiler optimization causes the program to crash!!!!!!!!!
  std::atomic_flag lock = ATOMIC_FLAG_INIT;
  while (lock.test_and_set()) {}

  curs_set(0); // Disable automatic displayed cursor
  noecho(); // Disable automatic character echoing
  keypad(stdscr, TRUE); // Enable keypad mode
  mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED, NULL); // Set up mouse events

  // Initialize colors
  if (has_colors()) {
    start_color();
    use_default_colors();
  }

  // Get size of the terminal
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  Calculator calc;
  calc.draw();
  
  while(true) {
    key_t ch = getch();
    // escape key
    if(ch == 27) { // Escape key
      std::cerr << "Escape key pressed! Exiting..." << std::endl;
      break;
    }

    // Pass mouse events
    MEVENT mevent;
    if (getmouse(&mevent) == OK) {
      calc.type(ch, &mevent);
    } else {
      calc.type(ch);
    }
  }

  // Tear down
  echo();
  keypad(stdscr, FALSE); // Enable keypad mode
  nocbreak();
  endwin();
  return 0;
}