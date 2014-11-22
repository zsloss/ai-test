#ifndef MIND_H
#define MIND_H

#include "person.h"

class Person;

class Mind {
    public:
        Mind(Person*);
    private:
        Person *me;
};

#endif
