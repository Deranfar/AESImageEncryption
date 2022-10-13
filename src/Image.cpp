#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)
#include <string>
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

Colour::Colour(uint8_t& red, uint8_t& green, uint8_t& blue): red(red), green(green), blue(blue) {}

Image::Image(std::string filename) {
	if(read(filename)) {
		printf("Read %s\n", filename);
		size = w*h*channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w*h*channels;
	data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(std::string filename) {
	data = stbi_load(filename.c_str(), &w, &h, &channels, 0);
	return data != NULL;
}

bool Image::write(std::string filename) {
	IType type = get_file_type(filename);
	const char* filenameC = filename.c_str();
	int success;
  switch (type) {
    case P:
      success = stbi_write_png(filenameC, w, h, channels, data, w*channels);
      break;
    case B:
      success = stbi_write_bmp(filenameC, w, h, channels, data);
      break;
    case J:
      success = stbi_write_jpg(filenameC, w, h, channels, data, 100);
      break;
    case T:
      success = stbi_write_tga(filenameC 	, w, h, channels, data);
      break;
  }
  return success != 0;
}

IType Image::get_file_type(std::string filename) {
	std::string ext = filename.substr(filename.length() - 5, 4); 
	if(!ext.compare(".png")) {
			return IType::P;
		}
		else if(!ext.compare(".jpg")) {
			return IType::J;
		}
		else if(!ext.compare(".bmp")) {
			return IType::B;
		}
		else if(!ext.compare(".tga")) {
			return IType::T;
		}
	return IType::P;
}

Colour Image::get_colour(int width, int height) {
		int position = height*w + width;
		int index = position * channels;
		return Colour(data[index], data[index+1], data[index+2]);
	}

void Image::set_colour(int width, int height, Colour& colour) {
		int position = height*w + width;
		int index = position * channels;
		data[index] = colour.red;
		data[index+1] = colour.green;
		data[index+2] = colour.blue;
		
}
 


