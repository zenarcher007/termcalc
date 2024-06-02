#include <ncurses.h>
#include "../uiconsole.h"
#include <iostream>
#include <assert.h>
#include <string>

// Tests if typing "123" displays correctly, in the correct order, and with nothing else on the screen
void testSmallOrdering() {
  UIConsole console("TestConsole");
  int rows = 5;
  int cols = 8;
  console.initWindow(Box(Point(0, 0), Size(rows, cols)));
  console.type('1');
  console.type('2');
  console.type('3');
  
  // Get contents of console.window curses window
  char* str = new char[rows*cols];
  for(int row = 0; row < rows; ++row) {
    wmove(console.window, row, 0);
    winnstr(console.window, str+row*cols, cols);
  }

  std::cout << "<STRING>" << str << "</STRING> ";
  assert(str[0] == '>');
  assert (str[1] == '1');
  assert (str[2] == '2');
  assert (str[3] == '3');
  
  // Make sure that the rest of the contents of str are null characters.
  for (int i=4; i<rows*cols-1; ++i) {
    assert(str[i] == 32);
  }
  delete[] str;

}

// Repeats the essence of the above test, with a longer string of characters that should wrap:
// That the characters are displayed in the correct order and that they result in the same string
void testMultilineOrdering(int length) {
  UIConsole console("TestConsole");
  int rows = 5;
  int cols = 8;
  console.initWindow(Box(Point(0, 0), Size(rows, cols)));
  --cols; // ***** Decrement cols because the last column is not used.
  char* stringToInject = new char[length];
  int whi = 0;
  while(whi < length) {
    stringToInject[whi] = 'a' + whi % 26;
    ++whi;
  }

  for(int i = 0; i < length; ++i) {
    char ch = stringToInject[i];
    assert(console.type(ch) == true);
  }

  // Extract the string from the window like in the above method
  char* str = new char[rows * cols];
  for(int row=0; row<rows; ++row) {
    wmove(console.window, row, 0);
    winnstr(console.window, str+row*cols, cols);
  }
  
  std::cout << "<STRING>" << str <<  "</STRING> ";

  assert(str[0] == '>');

  // Compare the extracted string (starting after index 2) and stringToInject
  for(int i=1; i<length+1; ++i) {
    std::cout << str[i]  << " " << stringToInject[i-1] << std::endl;
    assert(str[i] == stringToInject[i-1]);
  }

  // Make sure the rest of the extracted string is empty
  for  (int i=length+1; i<rows*cols-1; ++i)  {
    assert(str[i]  == 32);
  }

  delete[] stringToInject;
}





int main() {
  
  // Write all curses control messages to /dev/null to fool curses into thinking it's running in a terminal.
  FILE* outputDump = fopen("/dev/null", "wb");
  try {
    SCREEN* stdscr = newterm(0, outputDump, stdin);
    std::cout << "  testSmallOrdering()... ";
    testSmallOrdering();
    std::cout << "Passed!" << std::endl;

     std::cout <<   "testMultilineOrdering(length 8 of 8 cols)... ";
    testMultilineOrdering(8);
    std::cout << "Passed!" << std::endl;

    std::cout <<   "testMultilineOrdering(length 9 of 8 cols)... ";
    testMultilineOrdering(9);
    std::cout << "Passed!" << std::endl;
    
    std::cout <<  "testMultilineOrdering(length 10 of 8 cols)... ";
    testMultilineOrdering(10);
    std::cout << "Passed!" << std::endl;

    std::cout <<  "testMultilineOrdering(length 15 of 8 cols)... ";
    testMultilineOrdering(15);
    std::cout << "Passed!" << std::endl;

    endwin();
  } catch(const char* msg) {
    endwin();
    throw(msg);
  }
  fclose(outputDump);
  
}