#ifndef MIND_H
#define MIND_H

#include "person.h"
#include "body.h"
#include <unordered_map>

class Person;
class Body;

class Mind {
    public:
        Mind(Person*, Body*);
        void add_relation(int);
        bool knows(int);
    private:
    	const int id;
        Person* me;
        Body* body;
        std::unordered_map<int, int> relations;        
};

#endif
