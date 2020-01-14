//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_STRINGREVSER_H
#define UNTITELD2_STRINGREVSER_H

#include <string>

using namespace std;

template<typename Problem, typename Solution>
class StringReverser : public Solver<string, string> {
public:
    virtual string solve(string strWeWantToReverse) {
        int n = strWeWantToReverse.length();
        // Swap the character starting from two
        for (int i = 0; i < n / 2; i++) {
            swap(strWeWantToReverse[i], strWeWantToReverse[n - i - 1]);
        }
        return strWeWantToReverse;
    }

    virtual ~StringReverser() {

    }
};

#endif //UNTITELD2_STRINGREVSER_H
