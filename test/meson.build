sources = [
	'test.cpp',
]
thread = dependency('threads')
gtest = dependency('gtest_main')
executable('test_halide',
	sources,
	link_with:[ctlib],
	dependencies:[
		thread,
		gtest
	])
