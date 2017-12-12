#pragma once

namespace WMT
{

	class VariadicArgumentsBase
	{
	public:
		///Will return true if all arguments satisfy lCheckParamFunc
		template<class Lambda, class T, class...Args> static Bool CheckExpression(Lambda lCheckParamFunc, T lValue, Args...args) { return lCheckParamFunc(lValue) ? CheckExpression(lCheckParamFunc, args...) : false; }
		template<class Lambda, class T> static Bool CheckExpression(Lambda lCheckParamFunc, T lValue) { return lCheckParamFunc(lValue); }

		///Will return a static value equal to the number of provided arguments.
		template<class T, class...Args> static Size NumArguments(T lDimSize, Args...args) { return NumArguments(args...) + 1; }
		template<class T> static Size NumArguments(T lDimSize) { return 1; }
	};

	//#NOTE : These perform Compile time checks.
	//If this code is wrong an invalid case may be allowed to compile
	//Change this with care
	
	///Class for handling Variadic Arguments with a known limit on arguments
	template<Size lArg> class VariadicArgumentWithLimits
	{
	public:
		///Will throw a compile time error if the number of arguments is greater than lArg.
		template<class T, class...Args> static void CheckNumArguments(Args...args) { static_assert(sizeof(Args) <= lArg, "Too many Arguments to CheckNumArguments"); }

		///Will Fill the pointer provided with the provided arguments. The pointer will be filled up to lArg places, filling missing arguments with lDefault.
		template<class T, T lDefault, class R, class...Args> static void FillPointer(T *lPointer, R lValue, Args...args) { *lPointer++ = T(lValue); VariadicArgumentWithLimits<lArg - 1>::FillPointer<T, lDefault>(lPointer, args...); }
		template<class T, T lDefault, class R> static void FillPointer(T *lPointer, R lValue) { *lPointer++ = T(lValue); VariadicArgumentWithLimits<lArg - 1>::FillPointer<T, lDefault>(lPointer); }
		template<class T, T lDefault> static void FillPointer(T *lPointer) { *lPointer++ = lDefault;  VariadicArgumentWithLimits<lArg - 1>::FillPointer<T, lDefault>(lPointer); }
	};

	///	Bounding specialisation for VariadicArgumentWithLimits. This supplies bounding functionality
	template<> class VariadicArgumentWithLimits<0>
	{
	public:
		template<class T, T lDefault, class R, class...Args> static void FillPointer(T *lPointer, R lValue, Args...args) { static_assert(false, "Too many Arguments to FillPointer"); }
		template<class T, T lDefault, class R> static void FillPointer(T *lPointer, R lValue) { static_assert(false, "Too many Arguments to FillPointer"); }
		template<class T, T lDefault> static void FillPointer(T *lPointer) {  }
	};
}
