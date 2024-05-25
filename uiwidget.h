#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include "loctypes.h"

class UIWidget {
  private:
  std::string name;
  WINDOW *window;
  bool highlighted;
  Box dims;
  
  public:
  
  UIWidget(std::string name) {
    this->name = name;
  }

  UIWidget() {
    name = "default";
  }

  ~UIWidget() {
    if(window != nullptr)  {
      // TODO: delwin() does not seem to work on my machine????? Is this a problem?
      delete window;
      
      //delwin(window);
    }
  }

  // Initializes a window if not already. If this is not already initialized, the behavior of several other functions is undefined,
  // while many getters will return null.
  void initWindow(Box b) {
    if (window != nullptr) {
      return;
    }
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    
    window = newwin(b.rows, b.cols, b.row0, b.col0);
    dims = b;
    wrefresh(window);
  }

  void refresh() {
    wrefresh(window);
  }

  Box getDims() {
    return dims;
  }

  // Highlights every cell in the window
  void highlightAll() {
    if(window == nullptr || highlighted == true) {
      return;
    }
    // Save the current cursor position
    int cur_y, cur_x;
    getyx(window, cur_y, cur_x);
    for (int row = 0; row < dims.rows; row++) {
      // Move to the start of each row and
      // change attributes for the entire row
      mvwchgat(window, row, 0, -1, A_REVERSE, 1, NULL);
    }
    // Restore the cursor position
    wmove(window, cur_y, cur_x);
    highlighted = true;
    refresh();
  }

  // Undo the highlighting from highlightAll
  void unhighlightAll() {
    if(window == nullptr || highlighted == false)  {
      return;
    }
    // Save the current cursor position
    int cur_y, cur_x;
    getyx(window, cur_y, cur_x);
    for (int row = 0; row < dims.rows; row++) {
      // Move to the start of each row and
      // change attributes for the entire row
      mvwchgat(window, row, 0, -1, A_REVERSE, 1, NULL);
    }
    // Restore the cursor position
    wmove(window, cur_y, cur_x);
    highlighted = false;
    refresh();
  }

  std::string getName() { 
    return name;
  }

  // Recieves a character. Return true from this function if the character was processed, or false otherwise
  virtual bool type(key_t c) {
    return false;
  }

};

#endif