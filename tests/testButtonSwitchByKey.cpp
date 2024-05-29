#include <iostream>
#include "../termcalc.h"
#include "../buttonarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

ButtonArray initButtons() {
  ButtonArray ba("Numpad", Size(3, 3));
  //std::unique_ptr<UIButton> ptr1 = make_unique<UIButton>("1");
  std::shared_ptr<UIWidget> ptr1(new UIButton("1"));
  ba.addWidget(Point(0,0), ptr1);
  
  //std::unique_ptr<UIButton> ptr2 = make_unique<UIButton>("2");
  std::shared_ptr<UIWidget> ptr2(new UIButton("2"));
  ba.addWidget(Point(0,1), ptr2);

  //std::unique_ptr<UIButton> ptr3 = make_unique<UIButton>("3");
  std::shared_ptr<UIWidget> ptr3(new UIButton("3"));
  ba.addWidget(Point(0,2), ptr3);

  //std::unique_ptr<UIButton> ptr4 = make_unique<UIButton>("4");
  std::shared_ptr<UIWidget> ptr4(new UIButton("4"));
  ba.addWidget(Point(1,0), ptr4);
  
  //std::unique_ptr<UIButton> ptr5 = make_unique<UIButton>("5");
  std::shared_ptr<UIWidget> ptr5(new UIButton("5"));
  ba.addWidget(Point(1,1), ptr5);

  //std::unique_ptr<UIButton> ptr6 = make_unique<UIButton>("6");
  std::shared_ptr<UIWidget> ptr6(new UIButton("6"));
  ba.addWidget(Point(1,2), ptr6);
  
  //std::unique_ptr<UIButton> ptr7 = make_unique<UIButton>("7");
  std::shared_ptr<UIWidget> ptr7(new UIButton("7"));
  ba.addWidget(Point(2,0), ptr7);

  //std::unique_ptr<UIButton> ptr8 = make_unique<UIButton>("8");
  std::shared_ptr<UIWidget> ptr8(new UIButton("8"));
  ba.addWidget(Point(2,1), ptr8);
  
  //std::unique_ptr<UIButton> ptr9 = make_unique<UIButton>("9");
  std::shared_ptr<UIWidget> ptr9(new UIButton("9"));
  ba.addWidget(Point(2,2), ptr9);

  return ba;
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
    //std::cout << i << "\n";
    ButtonArray ba = initButtons();
    Point p(1,1);
    UIButton* b = ba.getWidget(p);
    //std::cout << b->getName() << std::endl;
    std::cout << std::hex << b << std::endl;
    assert(b != nullptr);
    assert(b->getName() == "5");
    
    ba.type(keys[i]);
    UIButton* newFocused = ba.getFocusedWidget();
    assert(newFocused != nullptr);
    assert(newFocused->getName() == std::to_string(expected_chars[i]));
  }
 
}



int main() {
  //std::cout << "testSwitchAdjacencyFromMiddle... ";
  testSwitchAdjacencyFromMiddle();
  //std::cout << "Passed!" << std::endl;
  return 0;
}
  