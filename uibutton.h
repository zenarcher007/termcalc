#include "uiwidget.h"
#include <iostream>
#include <string>

class UIButton: UIWidget {
  private:
  public:

  // Overwrite type() of UIWidget
  bool type(char ch) {
    if(ch == KEY_ENTER) {
      return true;
    }
    return false;
  }

  UIButton(std::string name): UIWidget(name) {
    
  }
};