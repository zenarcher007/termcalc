#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "uiwidget.h"
#include <iostream>
#include <string>

class UIButton: public UIWidget {
  private:
  public:

  // Override type() of UIWidget
  virtual bool type(key_t ch, MEVENT* mevent = nullptr) {
    if(ch == KEY_ENTER || ch == BUTTON1_CLICKED) {
      return true;
    }
    return false;
  }

  virtual void initWindow(Box b) {
    UIWidget::initWindow(b);
    unhighlightAll();
  }

  virtual void draw() {
    int len = strlen(name.c_str());
    Box d = getDims();
    int textRows = len / d.rows;
    int textCols = len;
    if(textCols > d.cols) textCols = d.cols;
    mvwaddstr(window, d.rows/2 - (textRows/2), d.cols/2 - (textCols/2), name.c_str()); // Center the text in the window if possible
    UIWidget::draw();
  }

  virtual void onFocusEnter() {
    wattron(window, COLOR_PAIR(1));
    highlightAll();
    draw();
  }

  virtual void onFocusExit() {
    wattroff(window, COLOR_PAIR(1));
    unhighlightAll();
    draw();
    //std::cout << "Exiting button: " << name << std::endl;
  }


  UIButton(std::string name): UIWidget(name) {
  }
};

#endif