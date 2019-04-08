#pragma once

namespace ct {

enum Result {
	OK,
	ERROR,
};

class Image {
public:
	Image(
		uint8_t* _data,
		int _width,
		int _height,
		int _channels)
		: data(_data)
		, width(_width)
		, height(_height)
		, channels(_channels){}
	uint8_t* data;
	int width;
	int height;
	int channels;
};

Result calc_back_projection_serial(
	Image* output,
	const Image& input);

Result calc_back_projection_parallel(
	Image* output,
	const Image& input);
	
} // namespace
