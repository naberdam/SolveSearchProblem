//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_POINT_H
#define UNTITELD2_POINT_H
class Point {
    int row;
    int col;
public:
    Point(int row1, int col1){
        this->row=row1;
        this->col=col1;
    }

    void setRow(int row1){
        this->row=row1;
    }

    void setCol(int col){
        this->col=col;
    }

    int getRow(){
        return this->row;
    }

    int getCol(){
        return this->col;
    }
};

#endif //UNTITELD2_POINT_H
