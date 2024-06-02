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
#include <sstream>
class WidgetArray: public FocusTracker {
  private:
  UIWidget** widgets;
  Size dims;

  bool isOutOfBounds(Point pos, Size arrdims) {
    return pos.row >= arrdims.rows || pos.col >= arrdims.cols || pos.row < 0 || pos.col < 0;
  }

  public:
  WidgetArray(std::string name, Size s): FocusTracker(name) {
    widgets = new UIWidget*[s.rows * s.cols]{0};
    this->dims = s;
  }

  /*
  // Override getDims()
  // This is necessary for mouse click detection to work correctly
  Box getDims() {
    // Find the minimum start row (Box.row0) and column (Box.col0) of all widgets in the array
    int minRow = INT32_MAX;
    int minCol = INT32_MAX;
    for(int i = 0; i < dims.rows * dims.cols; ++i)  {
      if(!widgets[i]) continue;
      Box b = widgets[i]->getDims();
      if(b.row0 < minRow) minRow = b.row0;
      if(b.col0 < minCol) minCol = b.col0;
    }
    // Find the maximum row and column size (Box.rows, Box.cols) for all widgets in the array
    int maxRowSize = 0;
    int maxColSize = 0;
    for(int i = minRow; i < dims.rows * dims.cols; ++i)   {
      if(!widgets[i]) continue;
      Box b = widgets[i]->getDims();
      if(b.row0 + b.rows > maxRowSize) maxRowSize = b.row0 + b.rows;
      if(b.col0 + b.cols > maxColSize) maxColSize = b.col0 + b.cols;
     }
     std::cout<<"min row "<<minRow <<" max row size "<<maxRowSize - minRow<<std::endl;
    return Box{minRow, minCol, maxRowSize - minRow, maxColSize - minCol};
  }
  */


  ~WidgetArray() {
    delete widgets;
  }

  // Inherits the widget given by the uniqe pointer. Note: assumes ownership of the unique_ptr!
  void addWidgetAtPoint(Point p, std::shared_ptr<UIWidget> &widget) {
    if(isOutOfBounds(p, dims))  {
      std::ostringstream oss;
      oss << "addWidgetAtPoint(): Point " << p << " is out of bounds";
      throw std::out_of_range(oss.str());
    }
    
    widgets[p.row * dims.cols + p.col] = (UIWidget*) widget.get();
    FocusTracker::addWidget(widget);
    if (!isOutOfBounds(Point(p.row - 1, p.col), dims)) {
      auto above = getWidgetAtPoint(Point(p.row - 1, p.col));
      if (above) {
        add_adjacency(widget->getName(), above->getName(), KEY_UP);
        add_adjacency(above->getName(), widget->getName(), KEY_DOWN); // Update neigboring widget to link to this newly added one
      }
    }

    if (!isOutOfBounds(Point(p.row + 1, p.col), dims)) {
      auto below = getWidgetAtPoint(Point(p.row + 1, p.col));
      if (below) {
        add_adjacency(widget->getName(), below->getName(), KEY_DOWN);
        add_adjacency(below->getName(), widget->getName(), KEY_UP);
      }
    }

    if (!isOutOfBounds(Point(p.row, p.col - 1), dims)) {
      auto left = getWidgetAtPoint(Point(p.row, p.col - 1));
      if (left) {
        add_adjacency(widget->getName(), left->getName(), KEY_LEFT);
        add_adjacency(left->getName(), widget->getName(), KEY_RIGHT);
      }
    }

    if (!isOutOfBounds(Point(p.row, p.col + 1), dims)) {
      auto right = getWidgetAtPoint(Point(p.row, p.col + 1));
      if (right) {
        add_adjacency(widget->getName(), right->getName(), KEY_RIGHT);
        add_adjacency(right->getName(), widget->getName(), KEY_LEFT);
      }
    }
  }

  // Gets the dimensions of the button array
  Size getDims() {
    return dims;
  }

  // Selects the widget at a point (could be more efficient)
  void selectAtPoint(Point p) {
    UIWidget* w = getWidgetAtPoint(p);
    if(w == nullptr) {
      std::ostringstream oss;
      oss << "No widget at location " << p;
      throw std::runtime_error(oss.str());
    }
    std::string name = w->getName();
    FocusTracker::select(name);
  }

  // Gets the widget at the point. Returns nullptr if there is no widget at that point
  UIWidget* getWidgetAtPoint(Point p) {
    if(isOutOfBounds(p, dims))  {
      std::ostringstream oss;
      oss << "getWidgetAtPoint() (possibly called by selectAtPoint): Point " << p << " is out of bounds";
      throw std::runtime_error(oss.str());
    }
    return widgets[p.row * dims.cols + p.col];
  }
  
};

#endif