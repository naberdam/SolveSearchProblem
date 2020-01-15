//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_STATE_H
#define UNTITELD2_STATE_H

//this enum is for the direction and it will use us in backTrace function
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

    State(T *current, double cost, State<T> *father, Direction direction) : current(current), cost(cost),
                                                                            father(father), direction(direction) {};

    /*void setFather(State<T> *newFather) { father = newFather; }*/

    double getCost() { return cost; }

    T getState() { return *current; }

    State<T> *getFather() { return father; }

    Direction getDirection() { return direction; }

    //overloading the operator instead of creating function called "Equal"
    bool operator==(State<T> another) {
        return (this->getState() == another.getState());
    }

    //we will call this function only in algorithms that use heuristic distance
    double getHeuristicDistance() const {
        return heuristicDistance;
    }

    //set the heuristic with the cost we have already done and with the distance (h(x))
    void setHeuristicDistance(double heuristicDistance1) {
        State::heuristicDistance = heuristicDistance1;
    }

    virtual ~State() {}
};

#endif //UNTITELD2_STATE_H
