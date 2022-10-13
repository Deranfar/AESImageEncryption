#pragma once
#include <stdint.h>
#include <cstdio>
#include <string>

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

enum IType {
	P /*PNG*/, 
	J /*JPG*/, 
	B /*BMP*/, 
	T/*TGA*/
};

class Colour {
	public:
		uint8_t red;
		uint8_t green;
		uint8_t blue;

		Colour(uint8_t& red, uint8_t& green, uint8_t& blue);	
};

class Image {
	public: 
		uint8_t* data = NULL;
		size_t size = 0;
		int w;
		int h;
		int channels;

		Image(std::string filename);
		Image(int w, int h, int channels);
		Image(const Image& img);
		~Image();

		bool read(std::string filename);
		bool write(std::string filename);

		IType get_file_type(std::string filename);

		// 0 based indexing
		Colour get_colour(int width, int height);

		void set_colour(int width, int height, Colour& colour);

};








