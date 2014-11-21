#include "speech.h"
#include <iostream>

Speech_packet::Speech_packet(Person &spk, std::string cat, std::string cont, Person &tgt) {
    speaker = &spk;
    category = cat;
    content = cont;
    target = &tgt;
}

std::string Speech_packet::get_category() const {
    return category;
}

std::string Speech_packet::get_content() const {
    return content;
}

Person Speech_packet::get_speaker() const {
    return *speaker;
}
