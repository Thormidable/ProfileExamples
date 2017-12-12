#pragma once

namespace WMT
{
	namespace Metrics
	{
		// Base class to perform various conversions between unit types where at least one unit is represented as a string.
		template<class Type1, typename...Args> class ConvertToMeasureByString
		{
		public:
			//Convert unit represented by a string to a statically defined unit type
			template<class ConvertToUnitType> static Float64 ConvertToType(Float64 lValue, const std::string &lConvertFromType) { return ConvertToHash<ConvertToUnitType>(lValue, Hash::VariadicHashString(lConvertFromType.c_str())); }

			//Convert statically defined unit type to a unit represented by a string
			template<class ConvertFromUnitType> static Float64 ConvertFromType(Float64 lValue, const std::string &lConvertToType) { return ConvertFromHash<ConvertFromUnitType>(lValue, Hash::VariadicHashString(lConvertToType.c_str())); }

			//Convert between two unit types represented by strings
			static Float64 Convert(Float64 lValue, const std::string &lConvertFromType, const std::string &lConvertToType) { return ConvertInternalCopy<Type1, Args...>(lValue, Hash::VariadicHashString(lConvertFromType.c_str()), Hash::VariadicHashString(lConvertToType.c_str())); }

		protected:
			template<class ConvertToUnitType> static Float64 ConvertToHash(Float64 lValue, UInt64 lHash)
			{
				if (Type1::HashedString() == lHash) return ConvertBetweenTypes< Type1, ConvertToUnitType>::ConvertValue(lValue);
				return ConvertToMeasureByString<Args...>::ConvertToHash<ConvertToUnitType>(lValue, lHash);
			}

			template<class ConvertFromUnitType> static Float64 ConvertFromHash(Float64 lValue, UInt64 lHash)
			{
				if (Type1::HashedString() == lHash) return ConvertBetweenTypes<ConvertFromUnitType, Type1>::ConvertValue(lValue);
				return ConvertToMeasureByString<Args...>::ConvertFromHash<ConvertFromUnitType>(lValue, lHash);
			}

			template<typename...ArgsCopy> static Float64 ConvertInternalCopy(Float64 lValue, UInt64 lHashFrom, UInt64 lHashTo)
			{
				if (Type1::HashedString() == lHashFrom) return ConvertToMeasureByString<ArgsCopy...>::ConvertFromHash<Type1>(lValue, lHashTo);
				return ConvertToMeasureByString<Args...>::ConvertInternalCopy<ArgsCopy...>(lValue, lHashFrom, lHashTo);
			}

			static Float64 ConvertHash(Float64 lValue, UInt64 lFrom, UInt64 lTo) { return ConvertInternalCopy<Type1, Args...>(lValue, lFrom, lTo); }

			friend class ConvertToMeasureByString;
		};

		//Variadic bounding class for ConvertToMeasureByString
		template<class Type1> class ConvertToMeasureByString<Type1>
		{
		private:
			template<class ConvertToUnitType> static Float64 ConvertToHash(Float64 lValue, UInt64 lHash)
			{
				if (Type1::HashedString() == lHash) return ConvertBetweenTypes< Type1, ConvertToUnitType>::ConvertValue(lValue);
				throw std::exception("ConvertMeasureByString: String provided is not recognised as a valid type");
			}

			template<class ConvertFromUnitType> static Float64 ConvertFromHash(Float64 lValue, UInt64 lHash)
			{
				if (Type1::HashedString() == lHash) return ConvertBetweenTypes<ConvertFromUnitType, Type1>::ConvertValue(lValue);
				throw std::exception("ConvertMeasureByString: String provided is not recognised as a valid type");
			}

			template<typename...ArgsCopy> static Float64 ConvertInternalCopy(Float64 lValue, UInt64 lHashFrom, UInt64 lHashTo)
			{
				if (Type1::HashedString() == lHashFrom) return ConvertToMeasureByString<ArgsCopy...>::ConvertFromHash<Type1>(lValue, lHashTo);
				throw std::exception("ConvertMeasureByString: String provided is not recognised as a valid type");
			}

			friend class ConvertToMeasureByString;
		};

		//Specialisations to make it easier to use. These require all unit types to allow checking by string.

		///Class to provide functionality to convert Distance units where one of the parameters is a string.
		class ConvertDistanceByString : public ConvertToMeasureByString<Nanometers, Micrometers, Millimeters, Centimeters, Meters, Kilometers, Miles> {};
		///Class to provide functionality to convert Temperature units where one of the parameters is a string.
		class ConvertTemperatureByString : public ConvertToMeasureByString<Centigrade, Kelvin, Farenheight> {};
		///Class to provide functionality to convert Time units where one of the parameters is a string.
		class ConvertTimeByString : public ConvertToMeasureByString<Nanoseconds, Microseconds, Milliseconds, Seconds, Minutes, Hours> {};
		///Class to provide functionality to convert Voltage units where one of the parameters is a string.
		class ConvertVoltageByString : public ConvertToMeasureByString<Millivolts, Volts, Kilovolts, Megavolts> {};
		///Class to provide functionality to convert Current units where one of the parameters is a string.
		class ConvertCurrentByString : public ConvertToMeasureByString<Microamps, Milliamps, Amps, Kiloamps, Megaamps> {};
		///Class to provide functionality to convert Angle units where one of the parameters is a string.
		class ConvertAngleByString : public ConvertToMeasureByString<Degrees, Radians> {};
		///Class to provide functionality to convert Charge units where one of the parameters is a string.
		class ConvertChargeByString : public ConvertToMeasureByString<MilliampSeconds, AmpMilliseconds, AmpSeconds, AmpHours> {};
	}
}
