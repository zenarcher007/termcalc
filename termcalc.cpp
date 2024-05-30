#include "tinyexpr.h"
#include <ncurses.h>
#include <iostream>
#include "termcalc.h"
#include "uibutton.h"
#include "uiwidget.h"
#include "loctypes.h"
#include "widgetarray.h"
#include "focustracker.h"
#include <atomic>

using namespace termcalc;


class Calculator {
  private:
    WidgetArray widgets;
  public:

  void type(int ch) {

  }

  Calculator(): widgets(WidgetArray("MainButtons", Size(5, 5))) { // Rows, Cols
    
  }


};

int main(int argc, char** argv) {

  initscr();
  // Create a thread barrier and block it to ensure initscr() isn't called after the other functions
  // For some reason, without this, compiler optimization causes the program to crash!!!!!!!!!
  std::atomic_flag lock = ATOMIC_FLAG_INIT;
  while (lock.test_and_set()) {}

  curs_set(0); // Disable automatic displayed cursor
  noecho(); // Disable automatic character echoing
  keypad(stdscr, TRUE); // Enable keypad mode

  
  UIWidget r;
  std::cout << "F" << std::endl;
  r.initWindow(Box(1,10,10,10));
  std::cout << "r" << std::endl;
  key_t ch = getch();
  std::cout << ch << std::endl;

  // Get size of the terminal
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  
  // Initialize colors
  /*if (has_colors()) {
    start_color();
    use_default_colors();
  }*/

  std::cout << rows << ", " << cols;

  // Tear down
  echo();
  keypad(stdscr, FALSE); // Enable keypad mode
  nocbreak();
  endwin();
  return 0;
}