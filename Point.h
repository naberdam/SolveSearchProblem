//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_POINT_H
#define UNTITELD2_POINT_H
class Point {
  int x;
  int y;
 public:
  Point(int x1, int y1) {
    this->x = x1;
    this->y = y1;
  }

  virtual ~Point() {}

  int getX() {
    return this->x;
  }

  int getY() {
    return this->y;
  }
  //overloading operator ==
  bool operator==(Point another) {
    return ((this->getX() == another.getX()) && (this->getY() == another.getY()));
  }
};

#endif //UNTITELD2_POINT_H
