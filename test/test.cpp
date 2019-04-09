#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include "back_projection.hpp"

TEST(IOTest, CanReadAndWrite) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat generic_output(input.size(), input.type());
	cv::Mat cpu_output(input.size(), input.type());
	ct::Image ctin(input.data, input.cols, input.rows, input.channels());
	ct::Image generic_out(generic_output.data, generic_output.cols, generic_output.rows, generic_output.channels());
	ct::Image cpu_out(cpu_output.data, cpu_output.cols, cpu_output.rows, cpu_output.channels());
	// generic
	auto start = std::chrono::high_resolution_clock::now();
	auto ret = ct::calc_back_projection_generic(&generic_out, ctin);
	auto end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(ct::Result::OK, ret);
	auto s_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	// cpu
	start = std::chrono::high_resolution_clock::now();
	ret = ct::calc_back_projection_cpu(&cpu_out, ctin);
	end = std::chrono::high_resolution_clock::now();
	EXPECT_EQ(ct::Result::OK, ret);
	auto p_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	std::cout << "generic:" << s_msec << " msec" << std::endl;
	std::cout << "cpu:" << p_msec << " msec" << std::endl;
	cv::imwrite("lena_generic_out.png", generic_output);
	cv::imwrite("lena_cpu_out.png", cpu_output);
}
