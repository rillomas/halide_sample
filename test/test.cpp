#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include "HalideBuffer.h"
#include "back_projection_generic.h"
#include "back_projection_cpu.h"

TEST(IOTest, ExecuteGeneral) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat generic_output(input.size(), input.type());
	cv::Mat cpu_output(input.size(), input.type());
	// generic
	Halide::Runtime::Buffer<uint8_t> ctin(input.data, input.cols, input.rows, input.channels());
	Halide::Runtime::Buffer<uint8_t> generic_out(generic_output.data, generic_output.cols, generic_output.rows, generic_output.channels());
	auto gen_start = std::chrono::high_resolution_clock::now();
	auto gen_error = back_projection_generic(ctin, generic_out);
	auto gen_end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(0, gen_error);
	auto gen_time = std::chrono::duration_cast<std::chrono::microseconds>(gen_end-gen_start).count();
	std::cout << "generic:" << gen_time << " usec" << std::endl;
	cv::imwrite("lena_generic_out.png", generic_output);
}

TEST(IOTest, ExecuteCPU) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat cpu_output(input.size(), input.type());
	// cpu
	Halide::Runtime::Buffer<uint8_t> ctin(input.data, input.cols, input.rows, input.channels());
	Halide::Runtime::Buffer<uint8_t> cpu_out(cpu_output.data, cpu_output.cols, cpu_output.rows, cpu_output.channels());
	auto cpu_start = std::chrono::high_resolution_clock::now();
	auto cpu_error = back_projection_cpu(ctin, cpu_out);
	auto cpu_end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(0, cpu_error);
	auto cpu_time = std::chrono::duration_cast<std::chrono::microseconds>(cpu_end-cpu_start).count();
	std::cout << "cpu:" << cpu_time << " usec" << std::endl;
	cv::imwrite("lena_cpu_out.png", cpu_output);
}
