#ifndef SPEECH_H
#define SPEECH_H
#include <string>

class Speech_packet {
    public:
        Speech_packet(int, std::string, std::string, int);
        std::string get_category() const;
        std::string get_content() const;
        int get_speaker_id() const;
        int get_target_id() const;
    private:
        std::string category, content;
        int speaker_id, target_id;
};

#endif
