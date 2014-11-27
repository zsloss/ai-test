#ifndef MIND_H
#define MIND_H

#include "person.h"
#include <unordered_map>

class Person;

class Mind {

    public:
        Mind(Person*);
        void add_relation(int);
        bool knows(int);
    private:
        Person* me;
        std::unordered_map<int, int> relations;        
};

#endif
