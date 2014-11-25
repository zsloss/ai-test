#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include "environment.h"
#include "mind.h"

class Mind;

class Person {
    public:
        std::string name;
        Person();
        Person(std::string);
        ~Person();

        /**
         * Retrieves a pointer to a Person object.
         *
         * @param _id the ID of the Person.
         * @return A pointer to the Person or nullptr if there is an error.
         */
        static Person* get_person(const int _id);

        int get_id() const;
        void update();
        Environment* get_environment() const;
        void set_environment(Environment&);
        void enter(Environment&);
    private:
        static int next_id;
        static std::vector<Person*> people;
        const int id;
        Mind* mind;
        int hunger;
        Environment* environment;
        void init();
        void listen();
        void look();
        void eat();
        void greet(int);
        void speak(std::string, std::string, int);
        void inform(std::string);
        void inform(int, std::string);
};

#endif
