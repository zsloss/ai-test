#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "speech.h"
#include <vector>
#include <unordered_set>

class Audio;
class Visual;
class Speech_packet;

class Environment {

    public:
        Environment();
        ~Environment();
        Audio* get_audio() const;
        Visual* get_visual() const;
        void update();
        void add_person(int);
        void remove_person(int);
    private:
        Audio* audio;
        Visual* visual;
        std::unordered_set<int> people;
};

class Audio {

    friend class Environment;

    public:
        Audio();
        std::vector<Speech_packet*>& get_speech();
        void add_speech(Speech_packet*);
    private:
        std::vector<Speech_packet*> speech;
        void update();
};

class Visual {

    friend class Environment;

    public:
        Visual();
        std::unordered_set<int>& get_people();
    private:
        void update();
        std::unordered_set<int> people;
        void add_person(int);
        void remove_person(int);
};

#endif
