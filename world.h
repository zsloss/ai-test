#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <unordered_set>
#include <memory>
#include "speech.h"

class Person;
class Zone;
class Map;

class Environment {
    public:
        Environment(Zone*);
        ~Environment();
        std::unordered_set<int> get_people();
        std::vector<Speech_packet>& get_speech();
        void add_speech(const int, const std::string, const std::string, const int);
        void update();
    private:
        Environment(const Environment&);
        Environment& operator=(const Environment&);        
        std::vector<Speech_packet> speech;
        Zone* zone;
};

class Zone {
    friend class World_map;
    public:
        Zone();
        ~Zone();
        Zone* north();
        Zone* south();
        Zone* east();
        Zone* west();
        Environment& get_environment();
        void add_person(const int);
        void remove_person(const int);
        std::unordered_set<int>& get_people();
        void update();
    private:
        Zone *n, *s, *e, *w;		
        std::unique_ptr<Environment> env;
        std::unordered_set<int> people;
};

class World_map {
public:
    World_map(const int x_max, const int y_max);
    ~World_map();
    Zone& get_zone(const int, const int);
private:
    void build_map(const int, const int);
    std::vector<std::vector<std::unique_ptr<Zone>>> map;
};

class World {
    public:
        World();
        ~World();
        void add_people(const int);
        void update();
    private:
        World(const World&);
        World& operator=(const World&);
        std::vector<std::unique_ptr<Person>> people;
        World_map map;
};

#endif
