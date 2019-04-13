#include "Halide.h"
using namespace Halide;

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

	Input<Buffer<uint8_t>> input{"input",3};
	Output<Buffer<uint8_t>> output{"brighter",3};
	Var x,y,c;
	enum Backend {
		GENERIC,
		CPU,
	};
	GeneratorParam<Backend> backend {
		"backend",
		GENERIC,
		{{"generic", GENERIC},
		 {"cpu", CPU}}
	};
};


HALIDE_REGISTER_GENERATOR(BackProjectionGenerator, back_projection)
