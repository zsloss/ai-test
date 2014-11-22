#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "speech.h"
#include <vector>

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
    private:
        Audio* audio;
        Visual* visual;

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
    private:
    void update();
};

#endif
