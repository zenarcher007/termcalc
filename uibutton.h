#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "uiwidget.h"
#include <iostream>
#include <string>

class UIButton: public UIWidget {
  private:
  public:

  // Overwrite type() of UIWidget
  virtual bool type(key_t ch) {
    if(ch == KEY_ENTER) {
      return true;
    }
    return false;
  }

  UIButton(std::string name): UIWidget(name) {
    
  }
};

#endif