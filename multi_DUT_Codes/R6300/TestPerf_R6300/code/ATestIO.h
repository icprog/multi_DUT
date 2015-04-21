#ifndef A_TEST_IO_H
#define A_TEST_IO_H
//IO control cmd value
enum CTL_TPERF_CMD
{
	T_START_TEST,// start test
	T_END_TEST,// test finish
	T_EXIT,// exit testperf
};
// IO report testperf status
enum TPERF_STS
{
	STS_ERROR,
};
#endif
