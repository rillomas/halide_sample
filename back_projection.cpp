#include "Halide.h"
#include "back_projection.hpp"
using namespace Halide;

namespace ct {

	
// static Func calc_back_projection_generic(
// 	Buffer<uint8_t> inbuf,
// 	Var x,
// 	Var y,
// 	Var c) {
// 	// cast raw buffer to Halide buffer
// 	auto val = cast<float>(inbuf(x,y,c));
// 	val = val * 1.5f;
// 	auto outval = cast<uint8_t>(clamp(val, 0.0f, 255.0f));
// 	Func backproj;
// 	backproj(x,y,c) = outval;
// 	return backproj;
// }

// Result calc_back_projection_generic(
// 	Image* output,
// 	const Image& input) {
// 	Var x,y,c;
// 	Buffer<uint8_t> inbuf(input.data, input.width, input.height, input.channels);
// 	auto backproj = calc_back_projection_generic(inbuf, x, y, c);
// 	Buffer<uint8_t> outbuf(output->data, output->width, output->height, output->channels);
// 	backproj.realize(outbuf);
// 	return OK;
// }

// Result calc_back_projection_cpu(
// 	Image* output,
// 	const Image& input) {
// 	Var x,y,c;
// 	Buffer<uint8_t> inbuf(input.data, input.width, input.height, input.channels);
// 	auto backproj = calc_back_projection_generic(inbuf, x, y, c);
// 	Buffer<uint8_t> outbuf(output->data, output->width, output->height, output->channels);
// 	backproj.vectorize(x, 8).parallel(y);
// 	backproj.realize(outbuf);
// 	return OK;
// }

} // namespace ct

enum Backend {
	GENERIC,
	CPU,
};

class BackProjectionGenerator : public Generator<BackProjectionGenerator> {
public:
	void generate() {
		// cast raw buffer to Halide buffer
		auto val = cast<float>(input(x,y,c));
		val = val * 1.5f;
		output(x,y,c) = cast<uint8_t>(clamp(val, 0.0f, 255.0f));
	}

	void schedule() {
		switch(backend) {
		case GENERIC:
			break;
		case CPU:
			output.vectorize(x, 8).parallel(y);
			break;
		}
	}

	Input<Buffer<uint8_t>> input{"input",2};
	Output<Buffer<uint8_t>> output{"brighter",2};
	Var x,y,c;
	GeneratorParam<Backend> backend {
		"backend",
		GENERIC,
		{{"generic", GENERIC},
		 {"cpu", CPU}}
	};
};


HALIDE_REGISTER_GENERATOR(BackProjectionGenerator, back_projection)
