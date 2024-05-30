#include <iostream>
#include "../termcalc.h"
#include "../widgetarray.h"
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

  // Ensures that the first widget added will automatically be set as focused
  void testFocusedWidgetIsFirstAdded() {
    std::shared_ptr<UIWidget> mywidget1(std::make_shared<UIButton>("mywidget1"));
    assert(getFocusedWidget() == nullptr);
    addWidget(mywidget1);
    assert(getFocusedWidget() == mywidget1.get());
  }

  void testFocusTrackerSelectsWidget() {
    std::shared_ptr<UIWidget> mywidget1(std::make_shared<UIButton>("mywidget1"));
    std::shared_ptr<UIWidget> mywidget2(std::make_shared<UIButton>("mywidget2"));
    addWidget(mywidget1);
    addWidget(mywidget2);
    assert(getFocusedWidget() != mywidget2.get());
    select("mywidget2");
    assert(getFocusedWidget() == mywidget2.get());
  }
};

int main() {
  {
    TestFocusTracker tft(std::string("focustracker_test"));
    std::cout << "testFocusedWidgetIsFirstAdded()... ";
    tft.testFocusedWidgetIsFirstAdded();
    std::cout << "Passed!" << std::endl;
  }
  {
    TestFocusTracker tft(std::string("focustracker_test"));
    std::cout << "testFocusTrackerSelectsWidget()... ";
    tft.testFocusTrackerSelectsWidget();
    std::cout << "Passed!" << std::endl;
  }
  return 0;
}