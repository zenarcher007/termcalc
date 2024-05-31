#include <iostream>
#include "../termcalc.h"
#include "../widgetarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>


// Ensures that the first widget added will automatically be set as focused
void testFocusedWidgetIsFirstAdded() {
  FocusTracker ft("test");
  std::shared_ptr<UIWidget> mywidget1(std::make_shared<UIButton>("mywidget1"));
  assert(ft.getFocusedWidget() == nullptr);
  ft.addWidget(mywidget1);
  assert(ft.getFocusedWidget() == mywidget1.get());
}

void testFocusTrackerSelectsWidget() {
  FocusTracker ft("test");
  std::shared_ptr<UIWidget> mywidget1(std::make_shared<UIButton>("mywidget1"));
  std::shared_ptr<UIWidget> mywidget2(std::make_shared<UIButton>("mywidget2"));
  ft.addWidget(mywidget1);
  ft.addWidget(mywidget2);
  assert(ft.getFocusedWidget() != mywidget2.get());
  ft.select("mywidget2");
  assert(ft.getFocusedWidget() == mywidget2.get());
}

int main() {
  {
    std::cout << "testFocusedWidgetIsFirstAdded()... ";
    testFocusedWidgetIsFirstAdded();
    std::cout << "Passed!" << std::endl;
  }
  {
    std::cout << "testFocusTrackerSelectsWidget()... ";
    testFocusTrackerSelectsWidget();
    std::cout << "Passed!" << std::endl;
  }
  return 0;
}