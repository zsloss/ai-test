#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "environment.h"

class Environment;

class Person {
    public:
        std::string name;
        Person();
        Person(std::string);
        void update();
        Environment* get_environment() const;
        void set_environment(Environment&);
        void inform(std::string);
        void inform(Person&, std::string);
    private:
        static int people;
        int id;
        int hunger;
        Environment* environment;
        void init();
        void eat();
        void greet(Person&);
        Person *interacting;
};

#endif
