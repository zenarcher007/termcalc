#include "tinyexpr.h"
#include <ncurses.h>
#include <iostream>
#include "termcalc.h"
#include "uibutton.h"
#include "uiwidget.h"
#include "point.h"
#include "buttonarray.h"

using namespace termcalc;


class Calculator {
  private:
    ButtonArray buttons;
  public:

  void type(int ch) {

  }

  Calculator(): buttons(ButtonArray(5, 5)) { // Rows, Cols
    
  }


};

int main(int argc, char** argv) {
  initscr();
  curs_set(0); // Disable automatic displayed cursor
  noecho(); // Disable automatic character echoing
  keypad(stdscr, TRUE); // Enable keypad mode
  
  // Get size of the terminal
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  // Initialize colors
  if (has_colors()) {
    start_color();
    use_default_colors();
  }

  std::cout << rows << ", " << cols;

  // Tear down
  echo();
  endwin();
  return 0;
}