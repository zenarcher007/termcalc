#include "UIWidget.h"
#include "loctypes.h"
#include <map>
#include <ncurses.h>

class FocusTracker: UIWidget {
  private:
  std::map<std::string, std::unique_ptr<UIWidget>> widgetMap;

  public:
  FocusTracker() {
  }

  ~FocusTracker() {
  }

  // Inherits the widget given by the unique pointer. Note: assumes ownership of the unique_ptr!
  void setWidget(Point p, std::unique_ptr<UIWidget> widget) {
    widgetMap[widget->getName()] = std::move(widget); // Take ownership of the unique_ptr.
  }

  // Gets the widget by name. Automatically extracts the UIWidget from the pointer.
  UIWidget* getWidget(std::string name) {
    return widgetMap[name].get();
  }

  // Adds a rule for which given that a current widget is selected, pressing a given key will select another widget.
  void add_adjacency(string name, string adjName, char keypress) {
    
  }

  // Passes the keypresses to the currently selected widget. If the widget returns true, the keypress is consumed and no other widgets will be notified of it.
  // If the widget returns false, then the keypress attempts to activate the next widget in the adjacency list if an ajacency is specified for that keypress
  bool type(char c) {
  }

};
