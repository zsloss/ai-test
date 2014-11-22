#include "environment.h"
#include <iostream>
#include "person.h"

Environment::Environment() {
    audio = new Audio();
}

Environment::~Environment() {
    delete audio;
}

void Environment::update() {
    get_audio()->update();
}


Audio* Environment::get_audio() const {
    return audio;
}

Audio::Audio() {

}

void Audio::update() {
    for (Speech_packet* p: get_speech()) {
        delete p;
    }
    speech.clear();
}

std::vector<Speech_packet*>& Audio::get_speech() {
    return speech;
}

void Audio::add_speech(Speech_packet *packet) {
    get_speech().push_back(packet);
    std::cout << Person::get_person(packet->get_speaker_id())->name << ": \"" << packet->get_content() << "\"" << std::endl;
}
