#ifndef MIND_H
#define MIND_H

#include "person.h"

class Person;

class Mind {
    public:
        Mind(Person*);
        int interacting;
    private:
        Person *me;
};

#endif
