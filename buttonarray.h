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
  std::unique_ptr<UIButton> *buttons;
  Size dims;


  public:
  ButtonArray(std::string name, Size s): FocusTracker(name) {
    buttons = (std::unique_ptr<UIButton>*) std::malloc(sizeof(buttons[0]) * s.rows * s.cols);
    memset(buttons, 0, sizeof(UIButton[0]) * s.rows * s.cols);
    this->dims = s;
  }

  ~ButtonArray() {
    delete buttons;
  }

  // Inherits the widget given by the uniqe pointer. Note: assumes ownership of the unique_ptr!
  void setWidget(Point p, std::unique_ptr<UIButton> &button) {
    // Call the superclass method of setWidget:
    FocusTracker::setWidget(p, (std::unique_ptr<UIWidget>) std::move(button));

    // Register all the positionally neighboring buttons in the array as neighbors using the FocusTracker class method:
    // add_adjacency(string name, string adjName, char keypress)
    // Each button will be registered using the names of its neighbors, and the up/down/left/right keys as keypresses:
    if(p.row - 1 >= 0) {
      add_adjacency(button->getName(), getWidget(Point(p.row - 1, p.col))->getName(), KEY_UP);
    }
    if(p.row + 1 < dims.rows) {
      add_adjacency(button->getName(), getWidget(Point(p.row + 1, p.col))->getName(), KEY_DOWN);
    }
    if(p.col - 1 >= 0) {
      add_adjacency(button->getName(), getWidget(Point(p.row, p.col - 1))->getName(), KEY_LEFT);
    }
    if(p.col + 1 < dims.cols) {
      add_adjacency(button->getName(), getWidget(Point(p.row, p.col + 1))->getName(), KEY_RIGHT);
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
    return buttons[p.row * dims.rows + p.col].get();
  }
  
};

#endif