//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_STATE_H
#define UNTITELD2_STATE_H

typedef enum {
    NOT = -1, UP, DOWN, LEFT, RIGHT
} Direction;

template<class T>

class State {
private:
    T *current;
    double cost;
    State<T> *father;
    Direction direction;
    double heuristicDistance;

public:

    //maybe changing the constructor to not-having father init, and using the set where needed
    State(T *current, double cost, State<T> *father, Direction direction) : current(current), cost(cost),
                                                                            father(father), direction(direction) {};

    void setFather(State<T> *newFather) { father = newFather; }

    double getCost() { return cost; }

    T getState() { return *current; }

    State<T> *getFather() { return father; }

    Direction getDirection() { return direction; }

    //overloading the operator instead of creating function called "Equal"
    bool operator==(State<T> another) {
        return (this->getState() == another.getState());
    }

    double getHeuristicDistance() const {
        return heuristicDistance;
    }

    void setHeuristicDistance(double heuristicDistance1) {
        State::heuristicDistance = heuristicDistance1;
    }


    virtual ~State() {

    }
};

#endif //UNTITELD2_STATE_H
