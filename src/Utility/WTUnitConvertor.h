#pragma once

namespace WMT
{
	namespace Metrics
	{
		//Classes to allow determination of unit type at compile time.
		class DistanceUnitType {};
		class TemperatureUnitType {};
		class TimeUnitType {};
		class VoltageUnitType {};
		class CurrentUnitType {};
		class AngleUnitType {};
		typedef std::tuple<CurrentUnitType, TimeUnitType> ChargeUnitType;

		//Base class for handling type conversion.
		template<UInt64 StringHash, class UnitType, class ScalingClass, class OffsetClass> class UnitWithOffset
		{
		public:
			typedef ScalingClass RatioType;
			typedef OffsetClass OffsetType;
			typedef UnitType MyUnitType;
			static constexpr Float64 ScaleFactor() { return Float64(ScalingClass::num) / Float64(ScalingClass::den); };
			static constexpr Float64 InvScaleFactor() { return Float64(ScalingClass::den) / Float64(ScalingClass::num); };
			static constexpr Float64 Offset() { return Float64(OffsetClass::num) / Float64(OffsetClass::den); };
			static constexpr Float64 ConvertToStandard(Float64 lValue) { return (lValue - Offset())*InvScaleFactor(); };
			static constexpr Float64 ConvertFromStandard(Float64 lValue) { return (lValue * ScaleFactor()) + Offset(); };
			static constexpr UInt64 HashedString() { return StringHash; };
		};

		//Specialisation of class for handling type conversion.
		template<UInt64 StringHash, class UnitType, class ScalingClass> class Unit : public UnitWithOffset<StringHash, UnitType, ScalingClass, std::ratio<0, 1>> {};

		//Specialisation of class for handling multiplied units
		template<class Unit1, class Unit2, UInt64 MyStringHash> class MultipliedUnits : public Unit <
			MyStringHash,
			std::tuple<typename Unit1::MyUnitType, typename Unit2::MyUnitType>,
			std::ratio<Unit1::RatioType::num*Unit2::RatioType::num, Unit1::RatioType::den*Unit2::RatioType::den>
		> {};


		// Classes to allow compile time specifying of unit types.

		///class representing Nanometers
		class Nanometers : public Unit <Hash::VariadicHashString("nm"), DistanceUnitType, std::ratio<1, 10000000>> {};
		///class representing Micrometers
		class Micrometers : public Unit <Hash::VariadicHashString("um"), DistanceUnitType, std::ratio<1, 10000>> {};
		///class representing Millimeters
		class Millimeters : public Unit <Hash::VariadicHashString("mm"), DistanceUnitType, std::ratio<1, 10>> {};
		///class representing Centimeters
		class Centimeters : public Unit <Hash::VariadicHashString("cm"), DistanceUnitType, std::ratio<1, 1>> {};
		///class representing Meters
		class Meters : public Unit <Hash::VariadicHashString("m"), DistanceUnitType, std::ratio<100, 1>> {};
		///class representing Kilometers
		class Kilometers : public Unit<Hash::VariadicHashString("km"), DistanceUnitType, std::ratio<100000, 1>> {};
		///class representing Miles
		class Miles : public Unit<Hash::VariadicHashString("miles"), DistanceUnitType, std::ratio<160934, 1>> {};

		///class representing Nanoseconds
		class Nanoseconds : public Unit<Hash::VariadicHashString("ns"), TimeUnitType, std::ratio<1, 1000000000>> {};
		///class representing Microseconds
		class Microseconds : public Unit<Hash::VariadicHashString("us"), TimeUnitType, std::ratio<1, 1000000>> {};
		///class representing Milliseconds
		class Milliseconds : public Unit<Hash::VariadicHashString("ms"), TimeUnitType, std::ratio<1, 1000>> {};
		///class representing Seconds
		class Seconds : public Unit<Hash::VariadicHashString("s"), TimeUnitType, std::ratio<1, 1>> {};
		///class representing Minutes
		class Minutes : public Unit<Hash::VariadicHashString("mins"), TimeUnitType, std::ratio<60, 1>> {};
		///class representing Hours
		class Hours : public Unit<Hash::VariadicHashString("hours"), TimeUnitType, std::ratio<60 * 60, 1>> {};

		///class representing Millivolts
		class Millivolts : public Unit<Hash::VariadicHashString("mV"), VoltageUnitType, std::ratio<1, 1000000>> {};
		///class representing Volts
		class Volts : public Unit<Hash::VariadicHashString("V"), VoltageUnitType, std::ratio<1, 1000>> {};
		///class representing Kilovolts
		class Kilovolts : public Unit<Hash::VariadicHashString("kV"), VoltageUnitType, std::ratio<1, 1>> {};
		///class representing Megavolts
		class Megavolts : public Unit<Hash::VariadicHashString("MV"), VoltageUnitType, std::ratio<1000, 1>> {};

		///class representing Microamps
		class Microamps : public Unit<Hash::VariadicHashString("uA"), CurrentUnitType, std::ratio<1, 1000>> {};
		///class representing Milliamps
		class Milliamps : public Unit<Hash::VariadicHashString("mA"), CurrentUnitType, std::ratio<1, 1>> {};
		///class representing Amps
		class Amps : public Unit<Hash::VariadicHashString("A"), CurrentUnitType, std::ratio<1000, 1>> {};
		///class representing Kiloamps
		class Kiloamps : public Unit<Hash::VariadicHashString("kA"), CurrentUnitType, std::ratio<1000000, 1>> {};
		///class representing Megaamps
		class Megaamps : public Unit<Hash::VariadicHashString("MA"), CurrentUnitType, std::ratio<1000000000, 1>> {};

		///class representing AmpSeconds
		class AmpSeconds : public MultipliedUnits<Amps, Seconds, Hash::VariadicHashString("As")> {};
		///class representing AmpMilliseconds
		class AmpMilliseconds : public MultipliedUnits<Amps, Milliseconds, Hash::VariadicHashString("Ams")> {};
		///class representing MilliampSeconds
		class MilliampSeconds : public MultipliedUnits<Milliamps, Seconds, Hash::VariadicHashString("mAs")> {};
		///class representing AmpHours
		class AmpHours : public MultipliedUnits<Amps, Hours, Hash::VariadicHashString("Ah")> {};

		///class representing Kelvin
		class Kelvin : public UnitWithOffset<Hash::VariadicHashString("K"), TemperatureUnitType, std::ratio<1, 1>, std::ratio<27315, 100>> {};
		///class representing Centigrade
		class Centigrade : public Unit<Hash::VariadicHashString("C"), TemperatureUnitType, std::ratio<1, 1>> {};
		///class representing Farenheight
		class Farenheight : public UnitWithOffset<Hash::VariadicHashString("F"), TemperatureUnitType, std::ratio<5, 9>, std::ratio<32, 1> > {};

		///class representing Radians
		class Radians : public Unit<Hash::VariadicHashString("degrees"), AngleUnitType, std::ratio<1, 1>> {};
		///class representing Degrees
		class Degrees : public Unit<Hash::VariadicHashString("radians"), AngleUnitType, std::ratio<31415926535897932, 1800000000000000000> > {};

		/*!
		Class to allow compile time optimised conversion from one metric to another.
		This enforces unit types match.
		This also does not go through an intermediate value.
		*/
		template<class ConvertUnitFrom, class ConvertUnitTo> class ConvertBetweenTypes
		{
		public:
			static constexpr Float64 ConvertValue(Float64 lValue)
			{
				static_assert(std::is_same<ConvertUnitFrom::MyUnitType, ConvertUnitTo::MyUnitType>::value, "Cannot convert between requested types");
				return (lValue - ConvertUnitFrom::Offset()) *(ConvertUnitFrom::ScaleFactor()*ConvertUnitTo::InvScaleFactor()) + ConvertUnitTo::Offset();
			}
		};
	}
}
