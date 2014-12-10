#ifndef BODY_H
#define BODY_H

#include <string>
#include <memory>
#include "world.h"
#include "person.h"
#include "mind.h"

class Zone;
class Person;
class Mind;
class Action;

class Body {
    public:
    	Body(Person*, Zone&);
        ~Body();
    	void update();
    	void listen();
        void look();
        void speak(std::string, std::string, int);
        void set_next_action(const Action&);
        void execute_next_action();
        Zone* get_zone() const;
        Mind& mind();
    private:
        Body(const Body&);
        Body& operator=(const Body&);
    	const int id;
    	Person* me;
    	int hunger;
        void set_zone(Zone&);
        void enter(Zone&);
        Zone* zone;
        std::unique_ptr<Action> next_action;        
};

#endif
