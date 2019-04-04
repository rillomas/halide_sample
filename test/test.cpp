#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include "back_projection.hpp"

TEST(IOTest, CanReadAndWrite) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat output(input.size(), input.type());
	ct::Image ctin(input.data, input.cols, input.rows, input.channels());
	ct::Image ctout(output.data, output.cols, output.rows, output.channels());
	auto start = std::chrono::high_resolution_clock::now();
	auto ret = ct::calc_back_projection(&ctout, ctin);
	auto end = std::chrono::high_resolution_clock::now();
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	std::cout
		<< msec << " msec" << std::endl;
	EXPECT_EQ(ct::Result::OK, ret);
	cv::imwrite("lena_out.png", output);
}
