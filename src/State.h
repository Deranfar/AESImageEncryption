#ifndef STATE
#define STATE
#include <cstdint>
#include "Constants.h"

// a 4*4 matrix of bytes consisting of 128 bits that is encrypted at a time
class State {
    public:
        uint8_t matrix[4][4];

        // helper for filling the state with an array of bytes
        void fillState(uint8_t* byte); 

        // writing the state back unto an array of byytes
        void writeState(uint8_t* ptr);

        // helper for applying a 128 bit key to the state
        void applyKey(uint8_t* key);

        // helper for doing the byte substitution operation
        void subByte();

        // helper for inverting the byte sysbsitution operation
        void inverseSubByte();

        // heper for the row shift opperation
        void shiftRows();

        // helper for inverting the row shift operation
        void inverseShiftRows();

        // helper for the column mix opperation
        void mixColumns();

        // helper for inverting the column mix operation
        void inverseMixColumns();
        
        void fillStateTest();
};

#endif