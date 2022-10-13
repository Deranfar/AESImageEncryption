#pragma once
#include "AES.cpp"
#include <iostream>
#include <iomanip>

// file basic test fucntions for different part of the encryption process
class KeyExpansionTest {
    public:
        uint8_t key128[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
        uint8_t* expandedKey128;
        
        uint8_t key192[24] = {0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 
        0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b};
        uint8_t* expandedKey192;

        uint8_t key256[32] = {0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 
        0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};
        uint8_t* expandedKey256;

        void test128() {
            expandedKey128 = (uint8_t*) AES::generateFullKey(key128, 4);
            for (int i = 0; i < 176; i++){
                std::cout << std::dec <<  i/4 << ". " << std::hex << (int) expandedKey128[i] << std::endl;
            }    
        }

        void test192() {
            expandedKey192 = (uint8_t*) AES::generateFullKey(key192, 6);
            for (int i = 0; i < 208; i++){
                std::cout << std::dec <<  i/4 << ". " << std::hex << (int) expandedKey192[i] << std::endl;
            }    
        }

        void test256() {
            expandedKey256 = (uint8_t*) AES::generateFullKey(key256, 8);
            for (int i = 0; i < 240; i++){
                std::cout << std::dec <<  i/4 << ". " << std::hex << (int) expandedKey256[i] << std::endl;
            }    
        }
};

class StateOperationsTest {
    public:
        State test;
        uint8_t*  input = new uint8_t[16] {0x19, 0x3d, 0xe3, 0xbe, 0xa0, 0xf4, 0xe2, 0x2b, 0x9a, 0xc6, 0x8d, 0x2a, 0xe9, 0xf8, 0x48, 0x08};
        uint8_t* key = new uint8_t[16]{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

        StateOperationsTest() {
            test.fillState(input);
        }

        void subByteTest() {
            test.subByte();
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }

        void inverseSubByteTest() {
            test.inverseSubByte();
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }

        void shiftRowsTest() {
            test.shiftRows();
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }

        void inverseShiftRowsTest() {
            test.inverseShiftRows();
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }

        void mixColumnsTest() {
            test.mixColumns();
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }

        void inverseMixColumnsTest() {
            test.inverseMixColumns();
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }

        void applyKeyTest() {
            uint8_t* fullKey = (uint8_t*) AES::generateFullKey(key, 4);
            test.applyKey(fullKey + 16);
            uint8_t* testArray = new uint8_t[16];
            test.writeState(testArray);
            for (int i = 0; i < 16; i++) {
                std::cout << std::dec << i << ". " << std::hex << (int) testArray[i] << std::endl;
            }
            delete [] testArray;
        }
};

class AESTest {
    public:
    uint8_t  input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t* result;
    
    void testEncrypt() {
        result = AES::aesEncrypt(input, 16, key, 4);
        for (int i = 0; i < 16; i++) {
            std::cout << std::dec << i << ". " << std::hex << (int) result[i] << std::endl;
        }
    }

    void testDecrypt() {
        uint8_t* dResult = AES::aesDecrypt(result, 16, key, 4);
        for (int i = 0; i < 16; i++) {
            std::cout << std::dec << i << ". " << std::hex << (int) dResult[i] << std::endl;
        }
    }

};

void readKeyTest() {
    std::string key = "3243F6a8885a308D313198a2E0370734";
    uint8_t* fullKey = AES::readKey(key);
    for (int i = 0; i < 16; i++) {
            std::cout << std::dec << i << ". " << std::hex << (int) fullKey[i] << std::endl;
        }
} 

void testAll() {
    // State testState;
    // testState.fillStateTest();
    // KeyExpansionTest testKE;
    // testKE.test128();
    // testKE.test192();
    // testKE.test256();
    // StateOperationsTest test;
    // test.subByteTest();
    // test.inverseSubByteTest();
    // test.shiftRowsTest();
    // test.inverseShiftRowsTest();
    // test.mixColumnsTest();
    // test.inverseMixColumnsTest();
    // test.applyKeyTest();
    // AESTest testEncrypt;
    // testEncrypt.testEncrypt();
    // testEncrypt.testDecrypt();
    readKeyTest();

}