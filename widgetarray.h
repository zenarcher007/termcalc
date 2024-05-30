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
#include <assert.h>
#include <format>
class WidgetArray: public FocusTracker {
  private:
  UIWidget** widgets;
  Size dims;

  bool isOutOfBounds(Point pos, Size arrdims) {
    std::cout << "pos: (" << pos.row << ", " << pos.col << ") arrdims: (" << arrdims.rows << ", " << arrdims.cols << ")" << std::endl;
    return pos.row >= arrdims.rows || pos.col >= arrdims.cols || pos.row < 0 || pos.col < 0;
  }

  public:
  WidgetArray(std::string name, Size s): FocusTracker(name) {
    widgets = (UIWidget**) std::malloc(sizeof(widgets[0]) * s.rows * s.cols);
    memset(widgets, 0, sizeof(UIWidget[0]) * s.rows * s.cols);
    this->dims = s;
  }

  ~WidgetArray() {
    delete widgets;
  }

  // Inherits the widget given by the uniqe pointer. Note: assumes ownership of the unique_ptr!
  void addWidgetAtPoint(Point p, std::shared_ptr<UIWidget> &widget) {
    if(isOutOfBounds(p, dims))  {
      throw std::out_of_range(std::format("addWidgetAtPoint(): Point ({}, {}) is out of bounds", p.col, p.row));
    }
    FocusTracker::addWidget(widget);
    widgets[p.row * dims.cols + p.col] = (UIWidget*) widget.get();
    UIWidget* above = getWidgetAtPoint(Point(p.row - 1, p.col));
    if (above) {
      add_adjacency(widget->getName(), above->getName(), KEY_UP);
    }

    UIWidget* below = getWidgetAtPoint(Point(p.row + 1, p.col));
    if (below) {
      add_adjacency(widget->getName(), below->getName(), KEY_DOWN);
    }

    UIWidget* left = getWidgetAtPoint(Point(p.row, p.col - 1));
    if (left) {
      //std::cout << widget->getName() << ",MOO, " << left->getName() << std::endl;
      add_adjacency(widget->getName(), left->getName(), KEY_LEFT);
      //std::cout << widget->getName() << ", DONE, " << below->getName() << std::endl;
    }

    UIWidget* right = getWidgetAtPoint(Point(p.row, p.col + 1));
    if (right) {
      add_adjacency(widget->getName(), right->getName(), KEY_RIGHT);
    }
  }

  // Gets the dimensions of the button array
  Size getDims() {
    return dims;
  }

  // Selects the widget at a point (could be more efficient)
  void selectAtPoint(Point p) {
    UIWidget* w = getWidgetAtPoint(p);
    assert(w != nullptr);
    std::string name = w->getName();
    FocusTracker::select(name);
  }

  // Gets the widget at the point. Returns nullptr if there is no widget at that point
  UIWidget* getWidgetAtPoint(Point p) {
    if(isOutOfBounds(p, dims))  {
      throw std::out_of_range(std::format("getWidgetAtPoint() (possibly called by selectAtPoint): Point ({}, {}) is out of bounds", p.col, p.row));
    }
    return widgets[p.row * dims.cols + p.col];
  }
  
};

#endif