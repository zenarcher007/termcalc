#include <iostream>
#include "../termcalc.h"
#include "../widgetarray.h"
#include "../uibutton.h"
#include "../loctypes.h"
#include <assert.h>
#include <ncurses.h>
#include <memory>
#include <string>

void testButtonLookupByPoint() {
  WidgetArray ba("Numpad", Size(3, 3));
  //std::unique_ptr<UIButton> ptr1 = make_unique<UIButton>("1");
  std::shared_ptr<UIWidget> ptr1(new UIButton("1"));
  ba.addWidgetAtPoint(Point(0,0), ptr1);
  assert(ba.getWidgetAtPoint(Point(0,0)) == ptr1.get());
  
  //std::unique_ptr<UIButton> ptr2 = make_unique<UIButton>("2");
  std::shared_ptr<UIWidget> ptr2(new UIButton("2"));
  ba.addWidgetAtPoint(Point(0,1), ptr2);
  assert(ba.getWidgetAtPoint(Point(0,1)) == ptr2.get());

  //std::unique_ptr<UIButton> ptr3 = make_unique<UIButton>("3");
  std::shared_ptr<UIWidget> ptr3(new UIButton("3"));
  ba.addWidgetAtPoint(Point(0,2), ptr3);
  assert(ba.getWidgetAtPoint(Point(0,2)) == ptr3.get());

  //std::unique_ptr<UIButton> ptr4 = make_unique<UIButton>("4");
  std::shared_ptr<UIWidget> ptr4(new UIButton("4"));
  ba.addWidgetAtPoint(Point(1,0), ptr4);
  assert(ba.getWidgetAtPoint(Point(1,0)) == ptr4.get());
  
  //std::unique_ptr<UIButton> ptr5 = make_unique<UIButton>("5");
  std::shared_ptr<UIWidget> ptr5(new UIButton("5"));
  ba.addWidgetAtPoint(Point(1,1), ptr5);
  assert(ba.getWidgetAtPoint(Point(1,1)) == ptr5.get());

  //std::unique_ptr<UIButton> ptr6 = make_unique<UIButton>("6");
  std::shared_ptr<UIWidget> ptr6(new UIButton("6"));
  ba.addWidgetAtPoint(Point(1,2), ptr6);
  assert(ba.getWidgetAtPoint(Point(1,2)) == ptr6.get());
  
  //std::unique_ptr<UIButton> ptr7 = make_unique<UIButton>("7");
  std::shared_ptr<UIWidget> ptr7(new UIButton("7"));
  ba.addWidgetAtPoint(Point(2,0), ptr7);
  assert(ba.getWidgetAtPoint(Point(2,0)) == ptr7.get());

  //std::unique_ptr<UIButton> ptr8 = make_unique<UIButton>("8");
  std::shared_ptr<UIWidget> ptr8(new UIButton("8"));
  ba.addWidgetAtPoint(Point(2,1), ptr8);
  assert(ba.getWidgetAtPoint(Point(2,1)) == ptr8.get());
  
  //std::unique_ptr<UIButton> ptr9 = make_unique<UIButton>("9");
  std::shared_ptr<UIWidget> ptr9(new UIButton("9"));
  ba.addWidgetAtPoint(Point(2,2), ptr9);
  assert(ba.getWidgetAtPoint(Point(2,2)) == ptr9.get()); 
}

void testOutOfBounds() {
  WidgetArray ba("OutofBoundsTestArray", Size(2, 2));
  std::shared_ptr<UIWidget> ptr1(new UIButton("1"));
  ba.addWidgetAtPoint(Point(0, 0), ptr1);
  std::shared_ptr<UIWidget> ptr2(new UIButton("2"));
  ba.addWidgetAtPoint(Point(0, 1), ptr2);
  std::shared_ptr<UIWidget> ptr3(new UIButton("3"));
  ba.addWidgetAtPoint(Point(1, 0), ptr3);
  std::shared_ptr<UIWidget> ptr4(new UIButton("4"));
  ba.addWidgetAtPoint(Point(1, 1), ptr4);
  
  std::array expectedPoints{Point(-1, -1), Point(-1, 0), Point(-1, 1),
                            Point(-1, 2), Point(0, -1), Point(0, 3),
                            Point(1, -1), Point(1, 3), Point(2, -1),
                            Point(2, 3), Point(3, -1), Point(3, 0) };
  
  // Check getWidgetAtPoint throws out of range exceptions for all points
  for (const auto &point : expectedPoints) {
    try {
      UIWidget* widget = ba.getWidgetAtPoint(point);
      assert(false && "getWidgetAtPoint: should have thrown an exception!");
    } catch (std::out_of_range& e) {
      // Do nothing, this is the expected result
    }
  }

  // Check the same with addWidgetAtPoint
  for  (const auto &point : expectedPoints) {
    try  {
      ba.addWidgetAtPoint(point, ptr1);
      assert(false && "addWidgetAtPoint: should have thrown an exception!");
     } catch  (std::out_of_range& e)  {
     }
   }
  
  // Check the same with selectAtPoint
  for  (const auto &point : expectedPoints) {
    try  {
      ba.selectAtPoint(point);
      assert(false && "Should have thrown an exception!");
     } catch  (std::out_of_range& e)  {
     }
   }
   
}

int main() {
  std::cout << "testButtonLookupByPoint()... ";
  testButtonLookupByPoint();
  std::cout << "Passed!" << std::endl;

  std::cout << "testButtonLookupByPointOutOfBounds()... ";
  testButtonLookupByPoint();
  std::cout << "Passed!" << std::endl;
  return 0;
}
  