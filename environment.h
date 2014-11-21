#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "speech.h"
#include <vector>

class Audio;
class Speech_packet;

class Environment {

    public:
        Environment();
        ~Environment();
        Audio* get_audio() const;
        void update();
    private:
        Audio* audio;

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

#endif
