#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "back_projection.hpp"

TEST(IOTest, CanReadAndWrite) {
	const std::string in_path("../test/data/lena.png");
	cv::Mat input = cv::imread(in_path);
	ASSERT_FALSE(input.empty());
	cv::Mat output(input.size(), input.type());

	cv::imwrite("lena_out.png", input);
}
