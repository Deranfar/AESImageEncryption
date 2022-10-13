#ifndef AES_H
#define AES_H
#include <cstdint>
#include <string>
#include "Word.cpp"
#include "State.cpp"
#include "Image.cpp"
class AES {
    public:
        static uint8_t* aesEncrypt(uint8_t* message, int size, uint8_t* key, int keyLength);
        static Image aesEncryptImage(Image image, uint8_t* key, int keyLength);
        static uint8_t* aesDecrypt(uint8_t* message, int size, uint8_t* key, int keyLength); 
        static Image aesDecryptImage(Image image, uint8_t* key, int keyLength);
        static int fullKeyLength(int keyLength);
        static Word* generateFullKey(uint8_t* key, int keySize);
        static uint8_t* readKey(std::string keyStr);
        static uint8_t readChar(char keyChar);
};

#endif