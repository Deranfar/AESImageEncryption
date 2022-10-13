#include "Word.h"

Word::Word() : first(0), second(0), third(0), fourth(0) {}

Word::Word(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth) : first(first), second(second), third(third), fourth(fourth) {}

Word Word::operator ^ (Word const &rval) {
    return Word(first ^ rval.first, second ^ rval.second, third ^ rval.third, fourth ^ rval.fourth);
}

Word Word::operator ^ (uint8_t const &rval) {
    return Word(first^rval, second, third, fourth);
}

Word Word::subWord() {
    first = Constants::s[first];
    second = Constants::s[second];
    third = Constants::s[third];
    fourth = Constants::s[fourth];
    return *this;
}
Word Word::rotWord() {
    uint8_t temp = first;
    first = second;
    second = third;
    third = fourth;
    fourth = temp;
    return *this;
}



