#include "WTTestHeader.h"

using namespace WMT;

template<class T> Bool Test::IsNearValue(T lValue, T lExpected, T lTolerance) 
{
	//To make the tolerance a relative measure of tolerance
	lTolerance *= std::max(std::abs(lExpected), std::abs(lValue));
	return abs(lValue - lExpected) <= lTolerance; 
}

template Bool Test::IsNearValue(Float32 lValue, Float32 lExpected, Float32 lTolerance);
template Bool Test::IsNearValue(Float64 lValue, Float64 lExpected, Float64 lTolerance);
