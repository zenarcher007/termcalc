#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include "loctypes.h"
#include <sys/types.h>

class UIWidget {
  private:
  bool highlighted;
  Box dims;

  public:
  std::string name;
  WINDOW *window;

  UIWidget(std::string name) {
    this->name = name;
    window = nullptr;
    highlighted = false;
  }

  UIWidget() {
    name = "default";
    window = nullptr;
    highlighted = false;
  }

  ~UIWidget() {
    if(window != nullptr)  {
      delwin(window);
    }
  }

  // Initializes a window. If already initialized, re-initializes it.
  // If this is not already initialized, the behavior of improperly-checked functions that use this may be undefined,
  // while many getters will return null.
  virtual void initWindow(Box b) {
    if (window != nullptr) {
      delwin(window);
    }
    
    window = newwin(b.rows, b.cols, b.row0, b.col0);
    dims = b;
    wrefresh(window);
  }

  virtual void draw() {
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
      mvwchgat(window, row, 0, -1, A_NORMAL, 0, NULL);
    }
    // Restore the cursor position
    wmove(window, cur_y, cur_x);
    highlighted = false;
  }

  virtual void onFocusEnter() {
    highlightAll();
  }

  virtual void onFocusExit()  {
    unhighlightAll();
  }

  std::string getName() { 
    return name;
  }

  // Recieves a character. Return true from this function if the character was processed, or false otherwise
  virtual bool type(key_t c, MEVENT* mevent = nullptr) {
    return false;
  }

};

#endif