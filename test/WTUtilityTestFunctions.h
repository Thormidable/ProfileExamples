#pragma once

//This file is to generate a very simple test framework for showing how the code would be tested, 
//rather than as a suggestion of a sutiable test framework

#define WMT_STRINGIFY(x) (#x)
#define WMT_BEGIN_TEST(...) \
std::cout << "-------------------------------------" << std::endl; \
VariadicsForTest::OutputAsString(__VA_ARGS__); try {

#define WT_PI 3.1415926535897

#define WMT_END_TEST() \
	std::cout << "Test Passed" << std::endl;\
	} \
	catch (...) \
	{  VariadicsForTest::OutputAsString("Test Failed or threw unexpected exception: " __FILE__ "(" , __LINE__ , ")"); }; 
	
#define WMT_CHECK(Condition) {if(!Condition) throw std::exception();}

#define WMT_CHECK_THROWS(expr) \
	try { \
		expr; \
		VariadicsForTest::OutputAsString(__FILE__ "(" , __LINE__ , "): Check throw failed"); \
		throw CheckFailedException(); \
	} \
	catch (CheckFailedException lExcept) { throw lExcept; } \
	catch (...) { }

namespace WMT
{
	namespace Test
	{
		//Class to allow detection through throwing mechanism for test which are expected to throw
		struct CheckFailedException { };

		//Function to allow checking float values to a specified tolrance
		template<class T> Bool IsNearValue(T lValue, T lExpected, T lTolerance);
		
		//Showing seperating template declaration and definition to make declaration clearer
		///Class for holding variadic functions for use by testing functions
		class VariadicsForTest
		{
		public:
			///Function to convert arguments, irrespective of type into a string (as supported by <<)
			template<class...Args> static std::string ToString(Args...args);
			///Function to send arguments to the console as a string
			template<class...Args> static void OutputAsString(Args...args);
		private:
			
			template<class T, class...Args> static void ToStringInternal(std::stringstream &lStream, const T &lString, Args...args);
			template<class T> static void ToStringInternal(std::stringstream &lStream, const T &lItem);
		};

		template<class...Args> static void VariadicsForTest::OutputAsString(Args...args)
		{
			std::cout << ToString(args...) << std::endl;
		}

		template<class...Args> static std::string VariadicsForTest::ToString(Args...args)
		{
			std::stringstream lStream;
			ToStringInternal(lStream, args...);
			return lStream.str();
		}

		template<class T, class...Args> static void VariadicsForTest::ToStringInternal(std::stringstream &lStream, const T &lString, Args...args)
		{
			lStream << lString;
			ToStringInternal(lStream, args...);
		}

		template<class T> static void VariadicsForTest::ToStringInternal(std::stringstream &lStream, const T &lItem)
		{
			lStream << lItem;
		}
	}
}