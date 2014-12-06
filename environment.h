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
        Environment(const Environment&);
        Environment& operator=(const Environment&);
        Audio* audio;
        Visual* visual;
        std::unordered_set<int> people;
};

class Audio {

    friend class Environment;

    public:
        Audio();
        std::vector<Speech_packet>& get_speech();
        void add_speech(int, std::string, std::string, int);
    private:
        Audio(const Audio&);
        Audio& operator=(const Audio&);
        std::vector<Speech_packet> speech;
        std::vector<Speech_packet> temp_speech;
        void update();
};

class Visual {

    friend class Environment;

    public:
        Visual();
        std::unordered_set<int>& get_people();
    private:
        Visual(const Visual&);
        Visual& operator=(const Visual&);
        void update();
        std::unordered_set<int> people;
        void add_person(int);
        void remove_person(int);
};

#endif
