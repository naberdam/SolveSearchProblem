//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_STATE_H
#define UNTITELD2_STATE_H

typedef enum {NOT = -1 ,UP, DOWN, LEFT, RIGHT} Direction;

template <class T>

class State {
private:
    T* current;
    double cost;
    State<T> *father;
    Direction direction;

public:

    //maybe changing the constructor to not-having father init, and using the set where needed
    State(T *current, double cost, State<T> *father, Direction direction) : current(current), cost(cost),
                                                                           father(father), direction(direction) {};

    void setCost(double newCost) {cost = newCost;}

    void setFather(State<T> *newFather) {father = newFather;}

    double getCost() {return cost;}

    T getState() {return *current;}

    State<T> *getFather() {return father;}

    Direction getDirection() { return direction; }

    //overloading the operator instead of creating function called "Equal"
    bool operator==(State<T> another) {
        return (this->getState() == another.getState());
    }

    T getT(){
        return T::class_name;
    }
};

#endif //UNTITELD2_STATE_H
