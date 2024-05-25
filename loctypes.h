#ifndef POINT_H
#define POINT_H

class Point {
  private:
  public:
  int row, col;
  
  Point() {
    row = 0;
    col = 0;
  }

  Point(int row, int col): row(row), col(col) {
  }
};

class Size {
  private:
  public:
  int rows, cols;
  
  Size() {
    rows = 0;
    cols = 0;
  }

  Size(int rows, int cols): rows(rows), cols(cols) {
  }
};


class Box {
  private:
  public:
  int row0, col0, rows, cols;
  
  Box() {
    row0 = 0;
    col0 = 0;
    rows = 0;
    cols = 0;
  }

  Box(int row0, int col0, int rows, int cols): row0(row0), col0(col0), rows(rows), cols(cols) {
  }
};



#endif