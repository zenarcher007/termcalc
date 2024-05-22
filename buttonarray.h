#include "uibutton.h"
#include "focustracker.h"
#include "loctypes.h"
#include <map>

class ButtonArray: FocusTracker {
  private:
  std::unique_ptr<UIButton> *buttons;
  Box dims;

  public:
  ButtonArray(Box dims) {
    buttons = (std::unique_ptr<UIButton>*) malloc(sizeof(buttons[0]) * dims.rows * dims.cols);
    memset(buttons, 0, sizeof(UIButton[0]) * rows * cols);
    this->dims = dims;
  }

  ~ButtonArray() {
    delete buttons;
  }

  // Inherits the widget given by the uniqe pointer. Note: assumes ownership of the unique_ptr!
  void setWidget(Point p, std::unique_ptr<UIButton> button) {
    // Call the superclass method of setWidget:
    UIWidget::setWidget(p, std::move(button));

    // Register all the positionally neighboring buttons in the array as neighbors using the FocusTracker class method:
    // add_adjacency(string name, string adjName, char keypress)
    // Each button will be registered using the names of its neighbors, and the up/down/left/right keys as keypresses:
    if (p.row > 0) {
      if(p.row - 1 >= 0) {
        add_adjacency(button->getName(), getWidget(Point(p.row - 1, p.col)).getName(), KEY_UP);
      }
      if(p.row + 1 < dims.rows) {
        add_adjacency(button->getName(), getWidget(Point(p.row + 1, p.col)).getName(), KEY_DOWN);
      }
      if(p.col - 1 >= 0) {
        add_adjacency(button->getName(), getWidget(Point(p.row, p.col - 1)).getName(), KEY_LEFT);
      }
      if(p.col + 1 < dims.cols) {
        add_adjacency(button->getName(), getWidget(Point(p.row, p.col + 1)).getName(), KEY_RIGHT);
      }
  }


  // Gets the widget by name. Automatically extracts the UIWidget from the pointer.
  void getWidget(std::string name) {
    return buttonMap[name];
  }

  // Gets the dimensions of the button array
  Box getDims() {
    return dims;
  }

  // Gets the widget at the point
  void getWidget(Point p) {
    return buttons[p.row * dims.rows + p.col].get();
  }
  
  // Selects the button at the point
  void selectButton(Point p) {
  }

};
