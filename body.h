#ifndef BODY_H
#define BODY_H

#include <string>
#include "environment.h"
#include "person.h"
#include "mind.h"

class Environment;
class Person;
class Mind;
class Action;

class Body {
    public:
    	Body(Person*, Environment&);
        ~Body();
    	void update();
    	void listen();
        void look();
        void speak(std::string, std::string, int);
        void set_next_action(const Action&);
        void execute_next_action();
        Mind& mind();
    private:
        Body(const Body&);
        Body& operator=(const Body&);
    	const int id;
    	Person* me;
    	int hunger;
    	Environment* get_environment() const;
        void set_environment(Environment&);
        void enter(Environment&);
        Environment* environment;
        Action* next_action;        
};

#endif
