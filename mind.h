#ifndef MIND_H
#define MIND_H

#include "person.h"
#include "body.h"
#include "speech.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>

class Person;
class Body;
class Speech_packet;

class Senses {
	public:
		void rec_heard_speech(std::vector<Speech_packet*>&);
		void rec_seen_people(std::unordered_set<int>&);
		std::vector<Speech_packet*>& get_heard_speech();
		std::unordered_set<int>& get_seen_people();
	private:
		std::vector<Speech_packet*> heard_speech;
		std::unordered_set<int> seen_people;
};

class Action {
	public:
		Action(std::function<void()>);
		void execute();
		int get_priority();
	private:
		int priority;
                std::function<void()> act;
};

class Mind {
    public:
        Mind(Person*, Body*);
        Senses& get_senses();
    private:
    	const int id;
        Person* me;
        Body* body;
        std::unordered_map<int, int> relations;
        Senses senses;    
        void add_relation(int);
        bool knows(int);
        void plan();      
};

#endif
