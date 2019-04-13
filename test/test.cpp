#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include "HalideBuffer.h"
#include "back_projection_basic.h"

TEST(IOTest, CanReadAndWrite) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat generic_output(input.size(), input.type());
	cv::Mat cpu_output(input.size(), input.type());
	// generic
	Halide::Runtime::Buffer<uint8_t> ctin(input.data, input.cols, input.rows, input.channels());
	Halide::Runtime::Buffer<uint8_t> generic_out(generic_output.data, generic_output.cols, generic_output.rows, generic_output.channels());
	auto start = std::chrono::high_resolution_clock::now();
	auto error = back_projection_basic(ctin, generic_out);
	auto end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(0, error);
	auto s_usec = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	std::cout << "generic:" << s_usec << " usec" << std::endl;
	cv::imwrite("lena_generic_out.png", generic_output);
}
