#include "world.h"

World::World() {

}

World::~World() {

}

void World::add_people(int n) {
	for (int i = 0; i < n; i++)
		people.emplace_back(new Person(env));
}

void World::update() {	
	for (auto &p: people) {
		p->update();
		p->get_body(p->get_id()).get_environment()->update();
	}
}
