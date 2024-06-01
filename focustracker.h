#ifndef FOCUSTRACKER_H
#define FOCUSTRACKER_H

#include "uiwidget.h"
#include "loctypes.h"
#include <map>
#include <ncurses.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <stdlib.h>
#include <string>
#include <sys/types.h>

class FocusTracker: public UIWidget {
  private:
    std::string focus;
    UIWidget* focusedWidget; // For caching
    std::map<std::string, std::shared_ptr<UIWidget> > widgetMap;

    // For a given widget, gives a map based on a key press to go to another widget
    std::map<std::string, std::map<key_t, std::string>> keyMap;
    //std::unordered_map<std::string, UIWidget > widgetMap;

  public:

  FocusTracker(std::string name): UIWidget(name) {
    focus = "";
    focusedWidget = nullptr;
  }

  ~FocusTracker() {
  }

  // Inherits the widget given by the unique pointer. Note: assumes ownership of the unique_ptr!
  // TODO: make this acually a unique_ptr? I do not know why this was not working with a shared ptr even with care to not copy
  void addWidget(std::shared_ptr<UIWidget> &widget) {
    //auto entry = std::make_pair(widget->getName(), std::move(widget));
    //widgetMap.emplace(widget->getName(), std::move(widget));
    //std::shared_ptr<UIWidget> entry = std::move(widget);
    widgetMap.insert(std::make_pair(widget->getName(), widget)); // TODO: Why doesn't emplace work??
    if(! keyMap.count(widget->getName())) { // Initialize an empty key map for this widget if it doesn't already exist
      keyMap[widget->getName()] = std::map<key_t, std::string>();
    }
    if(focusedWidget == nullptr) {
      select(widget->getName());
    }
  }

  // Gets the widget by name. Automatically extracts the UIWidget pointer from the unique pointer.
  UIWidget* getWidget(std::string name) {
    return widgetMap[name].get();
  }

  // Gets the currently selected widget
  UIWidget* getFocusedWidget() {
    return focusedWidget;
  }

  // Pass onFocusEnter to currently focused widget
  void onFocusEnter() {
    UIWidget* w = getFocusedWidget();
    if(w != nullptr) {
      w->onFocusEnter();
    }
  }

  // Pass onFocusExit to currently focused widget
  void onFocusExit()  {
    UIWidget* w = getFocusedWidget();
    if(w != nullptr)  {
      w->onFocusExit();
     }
   }

  // Adds a rule for which given that a current widget is selected, pressing a given key will select another widget.
  void add_adjacency(std::string name, std::string adjName, key_t keypress) {
    keyMap[name].insert(std::pair<key_t, std::string>(keypress, adjName));
  }

  // Calls onFocusExit on the currently selected widget, then selects a new widget.
  void select(std::string name) {
    focus = name;
    if(focusedWidget != nullptr) {
      focusedWidget->onFocusExit();
    }
    focusedWidget = getWidget(name);
    if(focusedWidget == nullptr)  {
      throw std::runtime_error("No such widget: " + name);
    }
    focusedWidget->onFocusEnter();
  }

  bool type(key_t c, MEVENT* mevent = nullptr) {
    // On mouse press event, get the current mouse coordinates. Then, loop through all widgets and see if the mouse is inside the
    // Box from getDims() for any widget. If so, then select that widget, pass the keypress to the widget, and return true to indicate that the keypress was consumed.
    if(c == KEY_MOUSE && mevent) {
      if (mevent->bstate & ALL_MOUSE_EVENTS) {
        for(auto it = widgetMap.begin(); it != widgetMap.end(); ++it)  {
          auto dims  = it->second->getDims();
          if (mevent->x >= dims.col0 && mevent->y >= dims.row0 && mevent->x < dims.col0+dims.cols && mevent->y < dims.row0+dims.rows)  {
            //std::cout << mevent->x << ", " << mevent->y << std::endl;
            //std::cout << it->first << std::endl;
            if(it->second->type(c, mevent)) { // If the widget handles the mouse press, select it
              //std::cout << it->first << std::endl;
              select(it->first);
              return true;
            }
            return false; // The widget did not handle the mouse press, so we do nothing
          }
        }
      }
    }

    // Passes the keypresses to the currently selected widget. If the widget returns true, the keypress is consumed and no other widgets will be notified of it.
    // If the widget returns false, then the keypress attempts to activate the next widget in the adjacency list if an ajacency is specified for that keypress
    if(! focusedWidget->type(c)) {
      auto it = keyMap[focus].find(c);
      if (it != keyMap[focus].end()) {
        select(it->second);
        return true;
      }
      return false;
    }
    return true;
  }
  
  // Redraws all widgets in the map
  void draw() {
    for(auto it : widgetMap) {
      it.second->draw();
    }
    UIWidget::draw();
  }

};

#endif