#include "speech.h"
#include "person.h"
#include <iostream>

Speech_packet::Speech_packet(int spk, std::string cat, std::string cont, int tgt) {
    speaker_id = spk;
    category = cat;
    content = cont;
    target_id = tgt;
    life = People::num_active();
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

int Speech_packet::get_life() const {
	return life;
}

bool Speech_packet::update() {
	// Simulating the speech 'fizzling out'.
	--life;
	// If life is below zero, we have an error - it should have been removed by now.
	if (life < 0)
		std::cerr << "\nWARNING: SPEECH PACKET SHOULD NOT BE IN EXISTENCE\n" << std::endl;

	// Return true if it is ready for removal.
	return life <= 0;
}
