#include "world.h"

#include <iostream>
#include <algorithm>
#include "person.h"

// ENVIRONMENT

Environment::Environment(Zone* z) : zone(z) {

}

Environment::~Environment() {

}

void Environment::update() {
    speech.erase(std::remove_if(speech.begin(), speech.end(), [](Speech_packet &sp) -> bool {return sp.update();}), std::end(speech));
}

std::unordered_set<int> Environment::get_people() {
    return zone->get_people(); // returns a _COPY_
}

void Environment::add_speech(int spk, std::string cat, std::string cont, int tgt) {    
    speech.emplace_back(spk, cat, cont, tgt);
    std::cout << People::get_name(spk) << ": \"" << cont << "\"" << std::endl;
}

std::vector<Speech_packet>& Environment::get_speech() {
    return speech;
}

// ZONE

Zone::Zone() : env(new Environment(this)), n(nullptr), s(nullptr), e(nullptr), w(nullptr) {

}

Zone::~Zone() = default;

Zone* Zone::north() { return n; }
Zone* Zone::south() { return s; }
Zone* Zone::east() { return e; }
Zone* Zone::west() { return w; }

Environment& Zone::get_environment() { return *env; }

void Zone::add_person(int p_id) {
	people.insert(p_id);
}

void Zone::remove_person(int p_id) {
	people.erase(p_id);
}

std::unordered_set<int>& Zone::get_people() { return people; }

void Zone::update() {
	env->update();
}

// WORLD

World::World() {
	// Just one zone for now...
	world_map.push_back(std::vector<std::unique_ptr<Zone>>());
	world_map.at(0).push_back(std::unique_ptr<Zone>(new Zone()));
}

World::~World() {
    
}

void World::add_people(int n) {
	for (int i = 0; i < n; i++)
		people.emplace_back(new Person(*world_map.at(0).at(0)));
}

void World::update() {	
	for (auto &p: people) {
		p->update();
		p->get_body(p->get_id()).get_zone()->update();
	}
}
