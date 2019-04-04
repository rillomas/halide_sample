sources = [
	'test.cpp',
]
gtest = dependency('gtest_main')
opencv = dependency('opencv')
executable('test_halide',
	sources,
	link_with:[ctlib],
	include_directories:[
		inc,
		HALIDE_INC_DIR,
	],
	dependencies:[
		opencv,
		gtest
	])
