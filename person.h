#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include "library.h"

class Person {
    public:
        int hunger;
        std::string name;
        Person();
        Person(std::string);
        void update();
        void inform(std::string);
        void inform(Person&, std::string);
        void eat();
        void greet(Person&);
    private:
        static int people;
        int id;
        void init();
        Person *interacting;
};

#endif
