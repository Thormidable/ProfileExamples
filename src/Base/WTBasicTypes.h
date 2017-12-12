#pragma once

#define WMT_BIT(bitIndex) (1 << (bitIndex))

namespace WMT
{
	typedef uint64_t	UInt64;
	typedef uint32_t	UInt32;
	typedef uint16_t	UInt16;
	typedef uint8_t		UInt8;

	typedef size_t		Size;
	typedef size_t		Offset;
	
	typedef int64_t		Int64;
	typedef int32_t		Int32;
	typedef int16_t		Int16;
	typedef int8_t		Int8;

	typedef long double	Float80;
	typedef double		Float64;
	typedef float		Float32;

	typedef uint16_t	Flags;

	typedef bool		Bool;
	typedef char		Char;

	///Class which will determine whether class A and B are the same type at compile time.
	template <class A, class B> struct CompareTypes	{ static const Bool result = false;	};
	template <class A> struct CompareTypes<A, A> { static const Bool result = true; };
	
	///enum to allow compile time evaluation of statically known Bool values.
	template<Bool State> struct BoolToType { enum { value = State }; };

	///enum to allow compile time evaluation of statically known Int values.
	template<Int64 State> struct IntToType { enum { value = State }; };

	///Typedef to allow determination of type without passing a parameter.
	template<class T> struct TypeToType { typedef T OriginalType; };
}
