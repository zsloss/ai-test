#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include "environment.h"
#include "mind.h"
#include "body.h"

class Person;
class Mind;
class Body;

class People {
    public:
        static int get_next_id();

        /**
         * Retrieves a pointer to a Person object.
         *
         * @param _id the ID of the Person.
         * @return A pointer to the Person or nullptr if there is an error.
         */
        static Person* get_person(const int _id);

        static std::vector<Person*>& get_people();
        static int num_active();
    private:
        static int next_id;
        static std::vector<Person*> people;
};

class Person {

    friend class People;

    public:        
        Person(Environment &env, std::string n = "");
        ~Person();       
        int get_id() const;
        std::string& get_name();
        void update();
        Mind& get_mind(int);
        Body& get_body(int);
    private:        
        Person(const Person&);
        Person& operator=(const Person&);
        const int id;
        std::string name;
        Mind* mind;
        Body* body;
};

#endif
