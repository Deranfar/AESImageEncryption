#include "State.h"

void State::fillState(uint8_t* byte) {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = *(byte + i*4 + j);
        }
    }
}

void State::writeState(uint8_t* ptr) {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            ptr[i*4+j] = matrix[i][j];
        }
    }
}

void State::applyKey(uint8_t* key) {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            matrix[i][j] ^= key[4*i+j];
        }
    }
}

void State::subByte() {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = Constants::s[matrix[i][j]];
        }
    }
}

void State::inverseSubByte() {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = Constants::iS[matrix[i][j]];
        }
    }
}

void State::shiftRows() {
    for (int j = 0; j < 4; j++) {
        uint8_t temp[4];
        for (int i = 0; i < 4; i++) {
            temp[i] = matrix[(i+j) % 4][j];
        }
        for (int i = 0; i < 4; i++) {
            matrix[i][j] = temp[i];
        }
    }
}

void State::inverseShiftRows() {
    for (int j = 0; j < 4; j++) {
        uint8_t temp[4];
        for (int i = 0; i < 4; i++) {
            temp[i] = matrix[(i-j+4) % 4][j];
        }
        for (int i = 0; i < 4; i++) {
            matrix[i][j] = temp[i];
        }
    }
}

void State::mixColumns() {
    for (int i = 0; i < 4; i++){
        gf28 temp[4];
        for (int j = 0; j < 4; j++) {
            temp[j] = gf28(matrix[i][0]) * Constants::columnShiftTable[0][j];
            temp[j] += gf28(matrix[i][1]) * Constants::columnShiftTable[1][j];
            temp[j] += gf28(matrix[i][2]) * Constants::columnShiftTable[2][j];
            temp[j] += gf28(matrix[i][3]) * Constants::columnShiftTable[3][j];
        }
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = temp [j];
        }
    }
}

void State::inverseMixColumns() {
    for (int i = 0; i < 4; i++){
        gf28 temp[4];
        for (int j = 0; j < 4; j++) {
            temp[j] = gf28(matrix[i][0]) * Constants::inverseColumnShiftTable[0][j];
            temp[j] += gf28(matrix[i][1]) * Constants::inverseColumnShiftTable[1][j];
            temp[j] += gf28(matrix[i][2]) * Constants::inverseColumnShiftTable[2][j];
            temp[j] += gf28(matrix[i][3]) * Constants::inverseColumnShiftTable[3][j];
        }
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = temp [j];
        }
    }
}

void State::fillStateTest() {
    uint8_t vals[16];
    for (int i = 0; i < 16; i++) {
        vals[i] = i;
    }
    fillState(vals);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << (int)matrix[i][j] << std::endl; 
        }
    }
    
}