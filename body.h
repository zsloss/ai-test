#ifndef BODY_H
#define BODY_H

#include "person.h"
#include "mind.h"

class Person;
class Mind;

class Body {
    public:
    	Body(Person*, Mind*, Environment&);
    	void update();
    	void listen();
        void look();
        void eat();
        void greet(int);
        void speak(std::string, std::string, int);
    private:
    	const int id;
    	Person* me;
    	Mind* mind;
    	int hunger;
    	Environment* get_environment() const;
        void set_environment(Environment&);
        void enter(Environment&);
        Environment* environment;
};

#endif
