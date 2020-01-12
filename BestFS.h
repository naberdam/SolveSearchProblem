//
// Created by amitai on 09/01/2020.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H

#include "Searcher.h"
#include <queue>
#include <vector>
using namespace std;
class BestFS : public Searcher {
private:
    bool isInOpenPriorityQueue(Point place, priority_queue<Point *> open) {
        while (!open.empty()) {
            auto tempNode = open.top();
            if (place.equal(tempNode)) {
                return true;
            }
            open.pop();
        }
        return false;
    }


public:
    vector<Point *> *search(Searchable *searchable) override {
        auto start = searchable->getStart();
        auto goal = searchable->getGoal();
        priority_queue<Point*> open;
        open.push(start);
        vector<Point*> closed;
        while (!open.empty()) {
        ////////////////////////////////////////////
            //need to check about weight function
            this->totalCost++;
            // Get the best value until this time
            auto bestPointInPriority = open.top();
            open.pop();
            closed.push_back(bestPointInPriority);
            if (bestPointInPriority == goal) {
                return this->backTrace(start, bestPointInPriority);
            }
        }

        return nullptr;//there is not path
    }

};

#endif //EX4_BESTFS_H
