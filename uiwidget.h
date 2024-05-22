#include <iostream>
#include <string>
#include <ncurses.h>

class UIWidget {
  private:
  std::string name;
  WINDOW *window;
  bool highlighted;
  
  public:
  
  // Initializes a window if not already.
  void initWindow(Box b) {
    if (window != nullptr) {
      return;
    }
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    
    window = newwin(b.height, b.width, b.y, b.x);
    box(window, 0 , 0);
    wrefresh(window);
  }

  void refresh() {
    wrefresh(window);
  }

  // Highlights every cell in the window
  void highlightAll() {
    if(window == nullptr || highlighted == true) {
      return
    } 
    for (int i = 1; i < window->_maxy - 1; ++i) {
      for (int j = 1; j < window->_maxx - 1; ++j) {
        // Use chgat to highlight the cell
        mvwchgat(window, i, j, 1, A_REVERSE, NULL);
      }
    }
    highlighted = true;
    refresh();
  }

  // Undo the highlighting from highlightAll
  void unhighlightAll() {
    if(window == nullptr || highlighted == false)  {
      return
    }
    for  (int i = 1; i < window->_maxy - 1; ++i) {
      for  (int j = 1; j < window->_maxx - 1; ++j) {
        mvwchgat(window, i, j, 1, A_NORMAL, NULL);
       }
     }
     highlighted = false;
     refresh();
  }

  string getName() { 
    return name;
  }

  // Recieves a character. Return true from this function if the character was processed, or false otherwise
  bool type(char c) {
  }

  UIWidget(std::string name) {
    this->name = name;
  }
};