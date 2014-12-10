#ifndef WORLD_H
#define WORLD_H

#include "person.h"
#include "environment.h"
#include <vector>
#include <memory>

class World {
    public:
    	World();
    	~World();
    	void add_people(int);
    	void update();
    private:
        World(const World&);
        World& operator=(const World&);
        std::vector<std::unique_ptr<Person>> people;
        Environment env;
};

#endif
