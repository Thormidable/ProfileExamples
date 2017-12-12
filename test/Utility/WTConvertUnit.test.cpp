#include "WTTestHeader.h"

using namespace WMT;
using namespace WMT::Metrics;

using namespace WMT::Test;

template<class TypeFrom, class TypeTo> void TestConvertTypes(Float64 lInput, Float64 lExpectedOutput)
{
    WMT_BEGIN_TEST("Test Convert Types : with values : ", lInput, " -> ", lExpectedOutput);
    WMT_CHECK(IsNearValue(ConvertBetweenTypes<TypeFrom, TypeTo>::ConvertValue(lInput), lExpectedOutput, 0.000001));
    WMT_END_TEST();
}

// Mock class to expose protected ConvertHash function for testing
template<class T> class MockClassExpose : private T
{
	public:
		using T::ConvertHash;
};

template<class ConvertType, class TypeFrom, class TypeTo> void TestConvertTypesByHashedStrings(Float64 lInput, Float64 lExpectedOutput)
{
    WMT_BEGIN_TEST("Test Convert Types using Hash Values : with values : ", lInput, " -> ", lExpectedOutput);
    WMT_CHECK(IsNearValue(MockClassExpose<ConvertType>::ConvertHash(lInput, TypeFrom::HashedString(), TypeTo::HashedString()), lExpectedOutput, 0.000001));
    WMT_END_TEST();
}

template<class TypeTo> void TestConvertDistanceTypeTo(Float64 lInput, const std::string &lName, Float64 lExpectedOutput)
{
    WMT_BEGIN_TEST("Test Convert Distance Types To : with values : ", lInput, " -> ", lExpectedOutput);
    WMT_CHECK(IsNearValue(ConvertDistanceByString::ConvertToType<TypeTo>(lInput, lName), lExpectedOutput, 0.000001));
    WMT_END_TEST();
}

template<class TypeFrom> void TestConvertDistanceTypeFrom(Float64 lInput, const std::string &lName, Float64 lExpectedOutput)
{
    WMT_BEGIN_TEST("Test Convert Distance Types From : with values : ", lInput, " -> ", lExpectedOutput);
    WMT_CHECK(IsNearValue(ConvertDistanceByString::ConvertFromType<TypeFrom>(lInput, lName), lExpectedOutput, 0.000001));
    WMT_END_TEST();
}

template<class T> void TestConvertType(Float64 lInput, const std::string &lFrom, const std::string &lTo, Float64 lExpectedOutput)
{
    WMT_BEGIN_TEST("Test Convert Types using Strings : with values : ", lInput, " -> ", lExpectedOutput, " ", lFrom, "->", lTo);
    WMT_CHECK(IsNearValue(T::Convert(lInput, lFrom, lTo), lExpectedOutput, 0.000001));
    WMT_END_TEST();
}

template<class T> void TestConvertTypeFail(Float64 lInput, const std::string &lFrom, const std::string &lTo)
{
    WMT_BEGIN_TEST("Test Convert Types Invalid conversion: ", lFrom, "->", lTo);
    WMT_CHECK_THROWS(T::Convert(lInput, lFrom, lTo));
    WMT_END_TEST();
}

void Test::RunUnitConversionTests()
{
    //Test Basic Conversions
    TestConvertTypes<Centimeters, Centimeters>(2.5, 2.5);
    TestConvertTypes<Centimeters, Meters>(2.5, 0.025);
    TestConvertTypes<Centimeters, Millimeters>(2.5, 25);

    //Test Conversion is compile time inlined
    TestConvertTypes<Miles, Miles>((std::numeric_limits<Float64>::max)(), (std::numeric_limits<Float64>::max)());
    TestConvertTypes<Nanometers, Nanometers>((std::numeric_limits<Float64>::max)(), (std::numeric_limits<Float64>::max)());
    TestConvertTypes<Nanometers, Nanometers>((std::numeric_limits<Float64>::epsilon)(), (std::numeric_limits<Float64>::epsilon)());

    //Test All types convert correctly
    TestConvertTypes<Nanometers, Micrometers>(1000, 1.0);
    TestConvertTypes<Micrometers, Millimeters>(1000, 1.0);
    TestConvertTypes<Millimeters, Centimeters>(10, 1.0);
    TestConvertTypes<Centimeters, Meters>(100, 1.0);
    TestConvertTypes<Meters, Kilometers>(1000, 1.0);
    TestConvertTypes<Meters, Miles>(1609.34, 1.0);

    TestConvertTypes<Nanoseconds, Microseconds>(1000, 1.0);
    TestConvertTypes<Microseconds, Milliseconds>(1000, 1.0);
    TestConvertTypes<Milliseconds, Seconds>(1000, 1.0);
    TestConvertTypes<Seconds, Minutes>(60, 1.0);
    TestConvertTypes<Minutes, Hours>(60, 1.0);

    TestConvertTypes<Millivolts, Volts>(1000, 1.0);
    TestConvertTypes<Volts, Kilovolts>(1000, 1.0);
    TestConvertTypes<Kilovolts, Megavolts>(1000, 1.0);

    TestConvertTypes<Microamps, Milliamps>(1000, 1.0);
    TestConvertTypes<Milliamps, Amps>(1000, 1.0);
    TestConvertTypes<Amps, Kiloamps>(1000, 1.0);
    TestConvertTypes<Kiloamps, Megaamps>(1000, 1.0);

    TestConvertTypes<Farenheight, Centigrade>(64, 17.777777);
    TestConvertTypes<Kelvin, Centigrade>(0, -273.15);
    TestConvertTypes<Centigrade, Kelvin>(100, 373.15);

    TestConvertTypes<Degrees, Radians>(180, WT_PI);

    //Test All Type conversions by strings
    TestConvertTypesByHashedStrings<ConvertDistanceByString, Nanometers, Micrometers>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertDistanceByString, Micrometers, Millimeters>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertDistanceByString, Millimeters, Centimeters>(10, 1.0);
    TestConvertTypesByHashedStrings<ConvertDistanceByString, Centimeters, Meters>(100, 1.0);
    TestConvertTypesByHashedStrings<ConvertDistanceByString, Meters, Kilometers>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertDistanceByString, Meters, Miles>(1609.34, 1.0);

    TestConvertTypesByHashedStrings<ConvertTimeByString, Nanoseconds, Microseconds>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertTimeByString, Microseconds, Milliseconds>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertTimeByString, Milliseconds, Seconds>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertTimeByString, Seconds, Minutes>(60, 1.0);
    TestConvertTypesByHashedStrings<ConvertTimeByString, Minutes, Hours>(60, 1.0);

    TestConvertTypesByHashedStrings<ConvertVoltageByString, Millivolts, Volts>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertVoltageByString, Volts, Kilovolts>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertVoltageByString, Kilovolts, Megavolts>(1000, 1.0);

    TestConvertTypesByHashedStrings<ConvertCurrentByString, Microamps, Milliamps>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertCurrentByString, Milliamps, Amps>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertCurrentByString, Amps, Kiloamps>(1000, 1.0);
    TestConvertTypesByHashedStrings<ConvertCurrentByString, Kiloamps, Megaamps>(1000, 1.0);

    TestConvertTypesByHashedStrings<ConvertTemperatureByString, Farenheight, Centigrade>(64, 17.777777);
    TestConvertTypesByHashedStrings<ConvertTemperatureByString, Kelvin, Centigrade>(0, -273.15);
    TestConvertTypesByHashedStrings<ConvertTemperatureByString, Centigrade, Kelvin>(100, 373.15);

    TestConvertTypesByHashedStrings<ConvertAngleByString, Degrees, Radians>(180, WT_PI);

    //Test Strings
    TestConvertDistanceTypeTo<Centimeters>(2.5, "cm", 2.5);
    TestConvertDistanceTypeTo<Meters>(2.5, "cm", 0.025);
    TestConvertDistanceTypeTo<Millimeters>(2.5, "cm", 25);

    TestConvertDistanceTypeFrom<Centimeters>(2.5, "cm", 2.5);
    TestConvertDistanceTypeFrom<Centimeters>(2.5, "m", 0.025);
    TestConvertDistanceTypeFrom<Centimeters>(2.5, "mm", 25);

    TestConvertType<ConvertDistanceByString>(2.5, "cm", "cm", 2.5);
    TestConvertType<ConvertDistanceByString>(2.5, "cm", "m", 0.025);
    TestConvertType<ConvertDistanceByString>(2.5, "cm", "mm", 25);

    //Test Strings are parsed case sensitive
    TestConvertType<ConvertCurrentByString>(250000000, "mA", "MA", 0.25);
    TestConvertType<ConvertCurrentByString>(0.25, "MA", "mA", 250000000);
    TestConvertType<ConvertCurrentByString>(2.5, "A", "mA", 2500);

    //Test that run time check won't convert invalid types
    TestConvertTypeFail<ConvertCurrentByString>(2.5, "m", "mA");
    TestConvertTypeFail<ConvertDistanceByString>(2.5, "m", "mA");

}