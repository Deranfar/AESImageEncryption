#include <iostream>
#include <iomanip>
#include "Image.cpp"
#include "AES.cpp"
#include "Test.cpp"










int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "Incorrect Number of Inputs" << std::endl;
        return 0;
    }
    std::string key = argv[4];
    int keylength = std::stoi(argv[5]);
    if (!validateKey(key, keylength)) {
        std::cout << "Incorrect Key" << std::endl;
        return 0;
    }
    std::string inputName = argv[2];
    std::string outputName = argv[3];
    if (!std::stoi(argv[1])){
        Image input = Image(inputName);
        Image output = AES::aesEncryptImage(input, AES::readKey(key), keylength);
        output.write(outputName);
    } else {
        Image input = Image(inputName);
        Image output = AES::aesDecryptImage(input, AES::readKey(key), keylength);
        output.write(outputName);
    }
    
    return 0;
}



