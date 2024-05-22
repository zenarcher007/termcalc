#include <iostream>
#include <string>

class UIWidget {
  private:
  std::string name;
  
  public:

  string getName() { 
    return name;
  }
  
  UIWidget(std::string name) {
    this->name = name;
  }
};