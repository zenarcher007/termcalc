#include <iostream>
#include "../termcalc.h"
#include "../buttonarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>

// Overrides class to gain access to protected members
class TestFocusTracker: public FocusTracker {
  public:
  // Constructor; initalize superclass
  TestFocusTracker(const std::string& name): FocusTracker(name) {
  }
  
  void testFocusTrackerSelectsWidget() {
    std::shared_ptr<UIWidget> mywidget1(std::make_shared<UIButton>("mywidget1"));
    std::shared_ptr<UIWidget> mywidget2(std::make_shared<UIButton>("mywidget2"));
    
  }
};

int main() {
  TestFocusTracker tft(std::string("focustracker_test"));
  tft.testFocusTrackerSelectsWidget();
  return 0;
}