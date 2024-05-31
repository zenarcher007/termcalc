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

void testMouseEventSelectsButton() {
  // The left corner of each widget. We will click all cells in each widget one by one, starting at this corner.
  Point startPoints[9];
  startPoints[0] = Point(0,0);
  startPoints[1] = Point(0,3);
  startPoints[2] = Point(0,6);
  startPoints[3] = Point(3,0);
  startPoints[4] = Point(3,3);
  startPoints[5] = Point(3,6);
  startPoints[6] = Point(6,0);
  startPoints[7] = Point(6,3);
  startPoints[8] = Point(6,6);

  std::string expectedWidgetNames[9] = {"1","2","3","4","5","6","7","8","9"};
  
  int buttonIteration = 0;
  for(Point startPoint : startPoints) {
    std::cout << "  Testing button selection 1->" << expectedWidgetNames[buttonIteration] << "... Clicking at: ";
    Point pt;
    for  (pt.row = startPoint.row; pt.row < startPoint.row+3; ++pt.row) {
      for  (pt.col = startPoint.col; pt.col < startPoint.col+3; ++pt.col) {
        std::cout << pt << ", ";
        std::unique_ptr<WidgetArray> wa = initButtons(Point(0, 0), Size(3, 3));
        assert(wa->getFocusedWidget()->getName() == "1");
        MEVENT mevent;
        mevent.x = pt.col;
        mevent.y = pt.row;
        mevent.bstate = 1;
        assert(wa->type(BUTTON1_CLICKED, &mevent) == true);
        assert(wa->getFocusedWidget()->getName() == expectedWidgetNames[buttonIteration]);
      }
    }
    std::cout << std::endl;
    ++buttonIteration;
  }
}

void testUnhandledMouseEventDoesNotSelectButton() {
  std::unique_ptr<WidgetArray> wa = initButtons(Point(0, 0), Size(3, 3));
  MEVENT mevent;
  mevent.x = 4; // Should be button 5
  mevent.y = 4;
  assert(wa->getFocusedWidget()->getName() == "1");
  assert(wa->type(BUTTON1_CLICKED, &mevent) == false);
  assert(wa->getFocusedWidget()->getName() == "1");
}


int main() {
  std::cout << "testMouseEventSelectsButton()... ";
  testMouseEventSelectsButton();
  std::cout << "Passed!" << std::endl;

  std::cout <<  "testUnhandledMouseEventDoesNotSelectButton()... ";
  testUnhandledMouseEventDoesNotSelectButton();
  std::cout <<  "Passed!" << std::endl;
  
  return EXIT_SUCCESS;
}