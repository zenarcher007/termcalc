#ifndef BUTTONARRAY_H
#define BUTTONARRAY_H

#include "uibutton.h"
#include "uiwidget.h"
#include "focustracker.h"
#include "loctypes.h"
#include <ncurses.h>
#include <map>
#include <memory>
#include <stdlib.h>
#include <string>
#include <cstring>

class ButtonArray: public FocusTracker {
  private:
  UIButton** buttons;
  Size dims;


  public:
  ButtonArray(std::string name, Size s): FocusTracker(name) {
    buttons = (UIButton**) std::malloc(sizeof(buttons[0]) * s.rows * s.cols);
    memset(buttons, 0, sizeof(UIButton[0]) * s.rows * s.cols);
    this->dims = s;
  }

  ~ButtonArray() {
    delete buttons;
  }

  // Inherits the widget given by the uniqe pointer. Note: assumes ownership of the unique_ptr!
  void addWidget(Point p, std::shared_ptr<UIWidget> &button) {
    FocusTracker::addWidget(button);
    buttons[p.row * dims.cols + p.col] = (UIButton*) button.get();
    UIWidget* above = getWidget(Point(p.row - 1, p.col));
    if (above) {
      add_adjacency(button->getName(), above->getName(), KEY_UP);
    }

    UIWidget* below = getWidget(Point(p.row + 1, p.col));
    if (below) {
      add_adjacency(button->getName(), below->getName(), KEY_DOWN);
    }

    UIWidget* left = getWidget(Point(p.row, p.col - 1));
    if (left) {
      add_adjacency(button->getName(), left->getName(), KEY_LEFT);
    }

    UIWidget* right = getWidget(Point(p.row, p.col + 1));
    if (right) {
      add_adjacency(button->getName(), right->getName(), KEY_RIGHT);
    }
  }

  // Gets the widget by name. Automatically extracts the UIWidget pointer from the unique pointer.
  UIButton* getWidget(std::string name) {
    return (UIButton*) FocusTracker::getWidget(name);
  }

  // Gets the dimensions of the button array
  Size getDims() {
    return dims;
  }

  // Gets the widget at the point
  UIButton* getWidget(Point p) {
    return buttons[p.row * dims.cols + p.col];
  }
  
};

#endif