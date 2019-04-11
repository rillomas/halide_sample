#pragma once

namespace ct {

enum Result {
	OK,
	ERROR,
};

class Image {
public:
	Image()
		: data(nullptr)
		, width(0)
		, height(0)
		, channels(0){}
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

// Result calc_back_projection_generic(
// 	Image* output,
// 	const Image& input);

// Result calc_back_projection_cpu(
// 	Image* output,
// 	const Image& input);
	
} // namespace
