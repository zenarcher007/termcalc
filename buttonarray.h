#include "uibutton.h"
#include "loctypes.h"
#include <map>

class ButtonArray {
  private:
  std::unique_ptr<UIWidget> *buttons;
  std::map<std::string, UIWidget*> buttonMap;
  Box dims;

  public:
  ButtonArray(Box dims) {
    buttons = (std::unique_ptr<UIWidget>*) malloc(sizeof(buttons[0]) * dims.rows * dims.cols);
    memset(buttons, 0, sizeof(buttons[0]) * rows * cols);
    this->dims = dims;
  }

  ~ButtonArray() {
    delete buttons;
  }

  // Inherits the widget given by the uniqe pointer. Note: assumes ownership of the unique_ptr!
  void setWidget(Point p, std::unique_ptr<UIWidget> widget) {
    buttons[row*rows+col] = std::move(widget); // Take ownership of the unique_ptr.
    buttonMap[widget->getName()] = buttons[row*rows+col].get();
  }

  // Gets the widget by name. Automatically extracts the UIWidget from the pointer.
  void getWidget(std::string name) {
    return buttonMap[name];
  }

  // Gets the widget at the row and column
  void getWidget(int row, int col) {
    return buttons[row*rows+col].get();
  }
  
};
