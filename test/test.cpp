#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include "back_projection.hpp"

TEST(IOTest, CanReadAndWrite) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat serial_output(input.size(), input.type());
	cv::Mat parallel_output(input.size(), input.type());
	ct::Image ctin(input.data, input.cols, input.rows, input.channels());
	ct::Image serial_out(serial_output.data, serial_output.cols, serial_output.rows, serial_output.channels());
	ct::Image parallel_out(parallel_output.data, parallel_output.cols, parallel_output.rows, parallel_output.channels());
	auto start = std::chrono::high_resolution_clock::now();
	auto ret = ct::calc_back_projection_serial(&serial_out, ctin);
	auto end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(ct::Result::OK, ret);
	auto s_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	start = std::chrono::high_resolution_clock::now();
	ret = ct::calc_back_projection_parallel(&parallel_out, ctin);
	end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(ct::Result::OK, ret);
	auto p_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	std::cout << "serial:" << s_msec << " msec" << std::endl;
	std::cout << "parallel:" << p_msec << " msec" << std::endl;
	cv::imwrite("lena_serial_out.png", serial_output);
	cv::imwrite("lena_parallel_out.png", parallel_output);
}
