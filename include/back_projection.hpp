#pragma once

namespace ct {

enum Result {
	OK,
	ERROR,
};

struct Image {
	uint8_t* data;
	int width;
	int height;
	int channels;
};

Result calc_back_projection(
	Image* output,
	const Image& input);

	
} // namespace
