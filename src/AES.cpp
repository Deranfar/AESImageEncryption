#pragma once
#include "AES.h"



// encrypts a message of any length based on a given key 
// original message, encrypted message and the key are all arrays of bytes
uint8_t* AES::aesEncrypt(uint8_t* message, int size, uint8_t* key, int keyLength) {
    // initialising variables
    uint8_t* encryptedMessage = new uint8_t[size];
    uint8_t* fullKey = (uint8_t*) generateFullKey(key, keyLength);
    State encryptionState;

    for (int i = 0; i < size; i+=16) {
        // 0th round
        uint8_t* keyPos = fullKey;
        encryptionState.fillState(message + i);
        encryptionState.applyKey(keyPos);
        keyPos += 16;
        // all rounds except final round
        for (int i = 0; i < (fullKeyLength(keyLength)/4 - 2) ; i++) {
            encryptionState.subByte();
            encryptionState.shiftRows();
            encryptionState.mixColumns();
            encryptionState.applyKey(keyPos);
            keyPos += 16;
        }
        // final round
        encryptionState.subByte();
        encryptionState.shiftRows();
        encryptionState.applyKey(keyPos);
        encryptionState.writeState(encryptedMessage + i);
    }
    return encryptedMessage;
}

// encrypts a message based on an Image object and a key, uses aesEncrypt as a helper
// key is still array of bytes
Image AES::aesEncryptImage(Image image, uint8_t* key, int keyLength) {
    uint8_t* data = aesEncrypt(image.data, image.size, key, keyLength);
    Image newImage{image};
    newImage.data = data;
    delete [] key;
    return newImage;
}

uint8_t* AES::aesDecrypt(uint8_t* message, int size, uint8_t* key, int keyLength) {
    uint8_t* decryptedMessage = new uint8_t[size];
    uint8_t* fullKey = (uint8_t*) generateFullKey(key, keyLength);
    State encryptionState;

    for (int i = 0; i < size; i+=16) {
        uint8_t* keyPos = fullKey + fullKeyLength(keyLength)*4 - 16;
        encryptionState.fillState(message + i);
        encryptionState.applyKey(keyPos);
        keyPos -= 16;
        encryptionState.inverseShiftRows();
        encryptionState.inverseSubByte();
        for (int i = 0; i < (fullKeyLength(keyLength)/4 - 2) ; i++) {
            encryptionState.applyKey(keyPos);
            keyPos -= 16;
            encryptionState.inverseMixColumns();
            encryptionState.inverseShiftRows();
            encryptionState.inverseSubByte();
            
        }
        
        encryptionState.applyKey(keyPos);
        encryptionState.writeState(decryptedMessage + i);
    }
    return decryptedMessage;
}

Image AES::aesDecryptImage(Image image, uint8_t* key, int keyLength) {
    uint8_t* data = aesDecrypt(image.data, image.size, key, keyLength);
    Image newImage{image};
    newImage.data = data;
    delete [] key;
    return newImage;
}


int AES::fullKeyLength(int keyLength) {
    switch (keyLength)
    {
    case 4:
        return 44;
    case 6:
        return 52;
    case 8:
        return 60;
    default:
        return -1;
    }
}

Word* AES::generateFullKey(uint8_t* key, int keyLength) {
    Word* fullKey = new Word[fullKeyLength(keyLength)];
    for (int i = 0; i < keyLength; i++) {
        fullKey[i] = Word(key[4*i], key[4*i+1], key[4*i+2], key[4*i+3]);
    }
    for (int i = keyLength; i < fullKeyLength(keyLength); i++) {
        Word temp = fullKey[i-1];
        if (i % keyLength == 0) {
            temp = temp.rotWord().subWord() ^ Constants::rc[i/keyLength -1];
        } else if ((keyLength > 6) && (i % keyLength == 4)) {
            temp = temp.subWord();
        }
        fullKey[i] = fullKey[i-keyLength] ^ temp;
    }
    
    return fullKey;
}

uint8_t* AES::readKey(std::string keyStr) {
    uint8_t* fullKey = new uint8_t[keyStr.size()/2];
    for (int i = 0; i < keyStr.size(); i+=2) {
        uint8_t key = readChar(keyStr[i])*16;
        key += readChar(keyStr[i+1]); 
        fullKey[i/2] = key;
    }
    return fullKey;
}

uint8_t AES::readChar(char keyChar) {
    if (48 <= keyChar && keyChar <= 57) {
        return keyChar - 48;
    } else if (65 <= keyChar && keyChar <= 70) {
        return keyChar - 55;
    } else if (97 <= keyChar && keyChar <= 102) {
        return keyChar - 87;
    }
    return 0;
}

bool validateKey(std::string key, int keyLength) {
    switch (keyLength) {
    case 4:
        return key.size() == 32;
    case 6:
        return key.size() == 48;
    case 8:
        return key.size() == 64;
    default:
        return 0;
    }
}


