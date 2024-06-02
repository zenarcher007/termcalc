#ifndef uiconsole_H
#define uiconsole_H

#include "uiwidget.h"
#include <ncurses.h>
#include <list>
#include <functional>

class UIConsole: public UIWidget {
private:
  Point virtualCursorPos;
  std::list<key_t> charBuffer;
  std::list<int>::iterator charBufferIterator;
  std::function<std::string(char[])> computeCallback;

  int min(int a, int b){ return (a < b)? a:b; }

public:
  UIConsole(std::string name): UIWidget(name) {
    virtualCursorPos = Point(0,0);
    charBufferIterator = charBuffer.begin();
  }

  // Disable default onFocusEnter() and onFocusExit() behavior
  void onFocusEnter() override {}
  void onFocusExit() override {}

  // Set the current position of the cursor as blinking immediately after initializing the window
  void initWindow(Box b) override {
    UIWidget::initWindow(b);
    virtualCursorPos = Point(0,0);
    moveCursorTo(virtualCursorPos);
    scrollok(window, true);
    type('>');
  }


  void moveCursorTo(Point p) {
    if(window == nullptr)
      return;
    wattr_on(window, A_BLINK, nullptr);
    mvwchgat(window, virtualCursorPos.row, virtualCursorPos.col, 1, A_NORMAL, 1, NULL);
    virtualCursorPos = p;
    wmove(window, p.row, p.col);
    //mvwchgat(window, row, 0, -1, A_REVERSE, 1, NULL);
    mvwchgat(window, p.row, p.col, 1, A_BLINK, 1, NULL);
    wattr_off(window, A_BLINK, nullptr);
  }

  virtual void draw() override {
    /*wmove(window, virtualCursorPos.row, 0);
    wclrtoeol(window);

    // Create a string out of all the characters in the buffer
    char* carr = new char[charBuffer.size()+1];
    int j = 0;
    for(key_t ch : charBuffer) {
      carr[j++] = ch;
    }
    carr[j+1] = '\0';
    int lengthOnThisLine = (charBuffer.size() % getDims().cols);
    waddnstr(window, &carr[charBuffer.size()]-lengthOnThisLine, getDims().cols);*/

    
    /*for(int i = 0; i < charBuffer.size() / getDims().cols+1; ++i) {
      wmove(window, virtualCursorPos.row-i, 0);
      wclrtoeol(window);
    }
    
    // Create a string out of all the characters in the buffer
    
    char* carr = new char[charBuffer.size()+1];
    int j = 0;
    for(key_t ch : charBuffer) {
      carr[j++] = ch;
    }
    carr[j+1] = '\0';
    for(int k = 0; k < charBuffer.size(); k+=getDims().cols)  {
      //wmove(window, virtualCursorPos.row-k/getDims().cols, k%getDims().cols);
      int row, col;
      getyx(window, row, col);
      waddnstr(window, carr+k, min(getDims().cols, charBuffer.size() - getDims().cols));
      wmove(window, row+1, 0);
    }
    //waddstr(window, carr);
    delete[] carr;
    //highlightAll();
    */
    moveCursorTo(virtualCursorPos);
    UIWidget::draw();

   }

  // Recieves a character. Return true from this function if the character was processed, or false otherwise
  virtual bool type(key_t c, MEVENT* mevent = nullptr) override {
    wmove(window, virtualCursorPos.row, virtualCursorPos.col); // Sync cursor
    if(window == nullptr)
      return false;
    switch(c) {
      case KEY_LEFT:
        if (virtualCursorPos.col <= 0) { // If at the beginning of the current line, try to go a row up
          if (virtualCursorPos.row <= 0) // Cannot go a row up
            return false;
          moveCursorTo(Point(virtualCursorPos.row - 1, getDims().cols-1)); // Go to the end of previous line
          --charBufferIterator;
          return true;
        }
        moveCursorTo(Point(virtualCursorPos.row, virtualCursorPos.col - 1)); // Go back one
        --charBufferIterator;
        return true;

      case KEY_RIGHT:
        if  (virtualCursorPos.col >= getDims().cols - 1) { // If at end of current line
          if  (virtualCursorPos.row >= getDims().rows - 1) // If cannot go a row down
            return false;
          
          moveCursorTo(Point(virtualCursorPos.row + 1, 1)); // Go to beginning of next line
          ++charBufferIterator;
          return true;
        }
        moveCursorTo(Point(virtualCursorPos.row, virtualCursorPos.col  + 1));
        //++charBufferIterator;
        return true;

      case KEY_BACKSPACE:
        if(type(KEY_LEFT, mevent)) {
          wmove(window, virtualCursorPos.row, virtualCursorPos.col);
          wdelch(window);
          charBuffer.erase(--charBufferIterator);
          return true;
        }
        return false;

      case KEY_ENTER | 61: { // Equals
        insertln();
        if(! computeCallback)
          return false;

        // Create a string out of all the characters in the buffer
        char* carr = new char[charBuffer.size()+1];
        int j = 0;
        for(key_t ch : charBuffer) {
          carr[j++] = ch;
        }
        carr[j+1] = '\0';
        for(key_t ch : computeCallback(carr))
          type(ch);
        insertln();
        waddch(window, '>');
        return true;
      }

      default:
        // ncurses function to mv and set the character at the current cursor position, without affecting the cursor
        if(! type(KEY_RIGHT, mevent)) { // If going right hit the end of the screen, advance and go to the left of the next line
          wscrl(window, 1);
          virtualCursorPos = Point(virtualCursorPos.row, 0);
        }
        mvwaddch(window, virtualCursorPos.row, virtualCursorPos.col-1, (char) c);

        // Update the char list and its iterator
        charBuffer.insert(charBufferIterator, c);
        return true;
    
    }
  }
};

#endif