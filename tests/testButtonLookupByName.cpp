#include <iostream>
#include "../termcalc.h"
#include "../widgetarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>
#include <string>

WidgetArray initButtons() {
  WidgetArray wa("Numpad", Size(3, 3));
  
  int num = 0;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      std::shared_ptr<UIWidget> ptr(new UIButton(std::to_string(++num).c_str()));
      wa.addWidgetAtPoint(Point(row, col), ptr);
    }
  }

  return wa;
}

void testButtonLookupByName() {
  WidgetArray ba = initButtons();
  for (int i = 1 ; i <= 9 ; ++i) {
    // Derive button name from index.
    std::string buttonName = std::to_string(i);
    UIButton* button = (UIButton*) ba.getWidget(buttonName);
    assert(button != nullptr);
    assert(button->getName() == buttonName);
  }
 
}

int main() {
  testButtonLookupByName();
  return 0;
}
  