#ifndef SPEECH_H
#define SPEECH_H
#include <string>
#include "person.h"

class Person;

class Speech_packet {
    public:
        Speech_packet(Person&, std::string, std::string, Person&);
        std::string get_category() const;
        std::string get_content() const;
        Person get_speaker() const;
    private:
        std::string category, content;
        Person *speaker, *target;
};

#endif
