#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "uiwidget.h"
#include <iostream>
#include <string>
#include <cstring>
#include <functional>

class UIButton: public UIWidget {
  private:
    // Pointer to a boolean function that accepts a std::string argument
    //bool (*activatorCallback)(std::string);
    std::function<bool(std::string)> activatorCallback;
  public:

  UIButton(std::string name): UIWidget(name) {
    activatorCallback = nullptr;
  }

  // Sets the callback function when this button is activated. Thus function must accept a std::string argument and return a bool
  void setActivatorCallback(std::function<bool(std::string)> callback) {
    activatorCallback = callback;
  }

  // Override type() of UIWidget
  virtual bool type(key_t ch, MEVENT* mevent = nullptr) {
    if(ch == 10 || ch == KEY_ENTER || (ch == KEY_MOUSE && mevent && (mevent->bstate == BUTTON1_PRESSED || mevent->bstate == BUTTON1_CLICKED) )) {
      if(activatorCallback != nullptr)
        return activatorCallback(name);
      return true;
    }
    return false;
  }

  virtual void initWindow(Box b) {
    UIWidget::initWindow(b);
    //unhighlightAll();
  }

  virtual void draw() {
    if(window == nullptr) return;
    int len = std::strlen(name.c_str());
    Box d = getDims();
    int textRows = len / d.rows;
    int textCols = len;
    if(textCols > d.cols) textCols = d.cols;
    mvwaddstr(window, d.rows/2 - (textRows/2), d.cols/2 - (textCols/2), name.c_str()); // Center the text in the window if possible
    UIWidget::draw();
  }

  virtual void onFocusEnter() {
    if(window == nullptr) return;
    wattron(window, COLOR_PAIR(1));
    highlightAll();
    draw();
  }

  virtual void onFocusExit() {
    if(window == nullptr) return;
    wattroff(window, COLOR_PAIR(1));
    unhighlightAll();
    draw();
    //std::cout << "Exiting button: " << name << std::endl;
  }


};

#endif