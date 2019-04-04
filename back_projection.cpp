#include "Halide.h"
#include "back_projection.hpp"
using namespace Halide;

namespace ct {

Result calc_back_projection(
	Image* output,
	const Image& input) {
	// cast raw buffer to Halide buffer
	Halide::Buffer<uint8_t> inbuf(input.data, input.width, input.height, input.channels);
	Halide::Buffer<uint8_t> outbuf(output->data, output->width, output->height, output->channels);
	Var x,y,c;
	auto val = cast<float>(inbuf(x,y,c));
	val = val * 1.5f;
	auto outval = cast<uint8_t>(clamp(val, 0.0f, 255.0f));
	Func backproj;
	backproj(x,y,c) = outval;
	backproj.realize(outbuf);
	return OK;
}

} // namespace ct
