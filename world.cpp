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

// WORLD MAP

World_map::World_map(int x_max, int y_max) {
    build_map(x_max, y_max);    
}

World_map::~World_map() = default;

Zone& World_map::get_zone(int x, int y) {
    return *(map.at(y).at(x));
}

void World_map::build_map(int x_max, int y_max) {

    map.reserve(y_max); // Prevents segfault
    typedef std::vector<std::unique_ptr<Zone>> row_type;
    row_type *prev_row = nullptr;

    for (int y = 0; y < y_max; y++) { // ROW
        
        map.push_back(row_type()); // Add a new row
        row_type &row = map.back();
        row.reserve(x_max); // Prevents segfault

        Zone *prev_zone = nullptr;

        for (int x = 0; x < x_max; x++) { // ZONE
            
            row.push_back(std::unique_ptr<Zone>(new Zone())); // Add a new zone to the row
            Zone &zone = *row.back();


            // Link with adjacent zones            
            if (y > 0) { // North/South      
                zone.n = &*prev_row->at(x);
                prev_row->at(x)->s = &zone;            }

            
            if (prev_zone != nullptr) { // East/West
                zone.w = prev_zone;
                prev_zone->e = &zone;
            }

            prev_zone = row.back().get(); // Update previous zone
        }
        prev_row = &row; // Update previous row
    }
}

// WORLD

World::World() : map(10,10) {

}

World::~World() {
    
}

void World::add_people(int n) {
	for (int i = 0; i < n; i++)
		people.emplace_back(new Person(map.get_zone(0,0)));
}

void World::update() {	
	for (auto &p: people) {
		p->update();
		p->get_body(p->get_id()).get_zone()->update();
	}
}
