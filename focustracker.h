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

class FocusTracker: public UIWidget {
  private:
    std::string focus;
    UIWidget* focusedWidget; // For caching
    std::map<std::string, std::shared_ptr<UIWidget> > widgetMap;
    //std::unordered_map<std::string, UIWidget > widgetMap;

  public:

  FocusTracker(std::string name): UIWidget(name) {
    focus = "";
    focusedWidget = nullptr;
  }

  ~FocusTracker() {
  }

  // Inherits the widget given by the unique pointer. Note: assumes ownership of the unique_ptr!
  // TODO: make this acually a unique_ptr. I do not know why this was not working with a shared ptr even with care to not copy
  void setWidget(std::shared_ptr<UIWidget> &widget) {
    //auto entry = std::make_pair(widget->getName(), std::move(widget));
    //widgetMap.emplace(widget->getName(), std::move(widget));
    //std::shared_ptr<UIWidget> entry = std::move(widget);
    widgetMap.insert(std::make_pair(widget->getName(), widget)); // TODO: Why doesn't emplace work??
  }

  // Gets the widget by name. Automatically extracts the UIWidget pointer from the unique pointer.
  UIWidget* getWidget(std::string name) {
    // TODO: When the map is working correctly, add .get()
    return widgetMap[name].get();
  }

  // Gets the currently selected button
  UIButton* getFocusedWidget() {
    return (UIButton*)focusedWidget;
  }

  // Adds a rule for which given that a current widget is selected, pressing a given key will select another widget.
  void add_adjacency(std::string name, std::string adjName, key_t keypress) {
    
  }

  void select(std::string name) {
    focusedWidget = getWidget(name);
  }

  // Passes the keypresses to the currently selected widget. If the widget returns true, the keypress is consumed and no other widgets will be notified of it.
  // If the widget returns false, then the keypress attempts to activate the next widget in the adjacency list if an ajacency is specified for that keypress
  bool type(key_t c) {
    return false;
  }

};

#endif