#include "environment.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include "person.h"

Environment::Environment() {
    audio = new Audio();
    visual = new Visual();
}

Environment::~Environment() {
    delete audio;
    delete visual;
}

void Environment::update() {
    get_audio()->update();
    get_visual()->update();
}

Audio* Environment::get_audio() const {
    return audio;
}

Visual* Environment::get_visual() const {
    return visual;
}

void Environment::add_person(int p_id) {
    people.insert(p_id);
    get_visual()->add_person(p_id);
}

void Environment::remove_person(int p_id) {
    people.erase(p_id);
    get_visual()->remove_person(p_id);
}

Audio::Audio() {

}

void Audio::update() {
    speech.erase(std::remove_if(speech.begin(), speech.end(), [](Speech_packet &sp) -> bool {return sp.update();}), std::end(speech));
}

std::vector<Speech_packet>& Audio::get_speech() {
    return speech;
}

void Audio::add_speech(int spk, std::string cat, std::string cont, int tgt) {    
    speech.emplace_back(spk, cat, cont, tgt);
    std::cout << People::get_person(spk)->get_name() << ": \"" << cont << "\"" << std::endl;
}

Visual::Visual() {

}

std::unordered_set<int>& Visual::get_people() {
    return people;
}

void Visual::update() {

}

void Visual::add_person(int p_id) {
    people.insert(p_id);
}

void Visual::remove_person(int p_id) {
    people.erase(p_id);
}
