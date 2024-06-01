#include <iostream>
#include "../termcalc.h"
#include "../widgetarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>
#include <stdexcept>



std::unique_ptr<WidgetArray> initButtons(Point leftCorner, Size buttonSize) {
  std::unique_ptr<WidgetArray> wa = std::make_unique<WidgetArray>("Numpad", Size(3, 3));
  int num = 0;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      std::shared_ptr<UIWidget> ptr(new UIButton(std::to_string(++num).c_str()));
      wa->addWidgetAtPoint(Point(row, col), ptr);
      ptr->initWindow(Box(Point(row*buttonSize.rows, col*buttonSize.cols), buttonSize)); // Use constructor Box(Point, Size)
      //ptr->draw();
    }
  }
  return wa;
}

void isolatedButtonWindowsDontInterfereFlakily() {
  std::cout << "  Checkpoint 0/2" << std::endl;
  {
    UIButton b ("1");
    b.initWindow(Box(Point(0,0), Size(3,3)));
    //std::cout << "After Init" << std::endl;
    //volatile std::unique_ptr<WidgetArray> wa = initButtons(Point(0,0), Size(3,3));
  }
  std::cout << "  Checkpoint 1/2" << std::endl;
  {
    UIButton b ("1");
    b.initWindow(Box(Point(0,0), Size(3,3)));
    //ptr->initWindow(Box(Point(0,0), Size(2,2), Size(3,3)))
    //volatile std::unique_ptr<WidgetArray> wa = initButtons(Point(0,0), Size(3,3));
  }
  std::cout <<  "Checkpoint 2/2" << std::endl;
}

void isolatedInitsDontInterfereFlakily() {
  std::cout << "  Checkpoint 0/2" << std::endl;
  {
    volatile std::unique_ptr<WidgetArray> wa = initButtons(Point(0,0), Size(3,3));
  }
  std::cout << "  Checkpoint 1/2" << std::endl;
  {
    volatile std::unique_ptr<WidgetArray> wa = initButtons(Point(0,0), Size(3,3));
  }
  std::cout <<  "Checkpoint 2/2" << std::endl;
}

int main() {
  std::cout << "Testing isolatedInitsDontInterfereFlakily()... " << std::endl;
  isolatedButtonWindowsDontInterfereFlakily();
  std::cout << "Passed!" << std::endl;

  std::cout <<  "Testing isolatedInitsDontInterfereFlakily()...  "  << std::endl;
  isolatedInitsDontInterfereFlakily();
  std::cout <<  "Passed!"  << std::endl;
}