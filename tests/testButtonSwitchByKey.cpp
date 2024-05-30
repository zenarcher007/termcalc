#include <iostream>
#include "../termcalc.h"
#include "../widgetarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>
#include <stdexcept>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

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

void testSwitchAdjacencyFromMiddle() {
  key_t* keys = new key_t[4];
  keys[0] = KEY_LEFT;
  keys[1] = KEY_RIGHT;
  keys[2] = KEY_UP;
  keys[3] = KEY_DOWN;
  
  char* expected_chars = new char[4];
  expected_chars[0] = 4;
  expected_chars[1] = 6;
  expected_chars[2] = 2;
  expected_chars[3] = 8;


  for (int i = 0; i < 4; ++i) {
    //std::cout << "BEGIN " << i << std::endl;
    WidgetArray wa = initButtons();
    Point p(1,1);
    wa.selectAtPoint(p);
    UIButton* b = (UIButton*) wa.getFocusedWidget(); //wa.getWidget(p);
    //std::cout << b->getName() << std::endl;
    //std::cout << std::hex << b << std::endl;
    assert(b != nullptr);
    assert(b->getName() == "5");
    
    assert(wa.type(keys[i]) == true); // If an object handles the keypress, type() should return true
    UIButton* newFocused = (UIButton*) wa.getFocusedWidget();
    assert(newFocused != nullptr);
    assert(newFocused->getName() == std::to_string(expected_chars[i]));
    //std::cout << "END " << i << std::endl;
  }
  delete[] keys;
  delete[] expected_chars;
 
}



int main() {
  //std::cout << "testSwitchAdjacencyFromMiddle... ";
  testSwitchAdjacencyFromMiddle();
  std::cout << "Passed!" << std::endl;
  return 0;
}
  