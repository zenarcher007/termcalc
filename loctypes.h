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

  // COUT operator overload
  friend std::ostream& operator<< (std::ostream& out, const Point &p) {
    out << "Point(row=" << p.row << ", col=" << p.col << ")";
    return out;
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

  // COUT operator overload
  friend std::ostream& operator<< (std::ostream& out, const Size &p) {
    out << "Size(rows=" << p.rows << ", cols=" << p.cols << ")";
    return out;
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

  // COUT operator overload
  friend std::ostream& operator<<  (std::ostream& out, const Box &b) {
    out << "Box(row0=" << b.row0 << ", col0=" << b.col0 << ") -> (rows=" << b.rows << ", cols=" << b.cols << ")";
    return out;
   }

  // Constructor that accepts raw data
  Box(int row0, int col0, int rows, int cols): row0(row0), col0(col0), rows(rows), cols(cols) {
  }

  // Constructor that accepts a Point and a Size
  Box(Point pt, Size sz): row0(pt.row), col0(pt.col), rows(sz.rows), cols(sz.cols)  {
  }
};



#endif