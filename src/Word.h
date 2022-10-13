#ifndef WORD
#define WORD
#include <cstdint>
#include "Constants.h"

// a set of 4 bytes used in the key schedule
class Word {
    public:
        uint8_t first;
        uint8_t second;
        uint8_t third;
        uint8_t fourth;

        Word();
        Word(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth);

        Word operator ^ (Word const &rval);

        Word operator ^ (uint8_t const &rval);

        Word subWord();

        Word rotWord();
};
#endif