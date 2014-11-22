#include "speech.h"
#include <iostream>

Speech_packet::Speech_packet(int spk, std::string cat, std::string cont, int tgt) {
    speaker_id = spk;
    category = cat;
    content = cont;
    target_id = tgt;
}

std::string Speech_packet::get_category() const {
    return category;
}

std::string Speech_packet::get_content() const {
    return content;
}

int Speech_packet::get_speaker_id() const {
    return speaker_id;
}

int Speech_packet::get_target_id() const {
    return target_id;
}
