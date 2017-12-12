#pragma once

namespace WMT
{
	/*!
	Class for generating Hashes of various data streams.
	Can hash a series of datasets into a single hash.
	*/
	class Hash
	{
	public:

		Hash() : mHash(0) {};
		void Reset() { mHash = 0; }
		
		///Hash a single Value
		template<class T> Hash &HashValue(const T lValue)
		{
			HashData(&lValue, 1);
			return *this;
		}

		///Hash a std::vector
		template<class T> Hash &HashVector(const std::vector<T> &lVect)
		{
			HashData(lVect.data(), lVect.size());
			return *this;
		}

		///Hash a memory array
		template<class T> Hash &HashData(const T *lData, Size lNumElements)
		{
			Size lNumBytes = lNumElements * sizeof(T);
			Size lNumUInt64 = lNumBytes / sizeof(UInt64);
			Size lNumUInt8 = lNumBytes % sizeof(UInt64);

			const UInt64 *lpUInt64 = reinterpret_cast<const UInt64*>(lData);
			HashValueInternal(lpUInt64, lNumUInt64);

			HashValueInternal(reinterpret_cast<const UInt8*>(&lpUInt64[lNumUInt64]), lNumUInt8);
			return *this;
		}

		UInt64 GetHashValue() { return mHash; }
		void SetHashValue(UInt64 lHash) { mHash = lHash; }

		///Allow hashing several values through the << operator
		template<class T> Hash &operator<<(T lObject)
		{
			return HashValue(lObject);
		}
		template<> inline Hash &operator<<(std::string lString) { return HashData(lString.c_str(), lString.length()); }

		///Hash values supplied variadically at Compile time.
		template<class...Args> static constexpr UInt64 VariadicHash(UInt64 lHash, UInt64 lValue, Args...args)
		{
			return VariadicHash(VariadicHash(lHash, lValue), args...);
		}
		///Hash string supplied variadically at Compile time.
		static constexpr UInt64 VariadicHashString(const Char* lString, UInt64 Index = 0)
		{
			return !lString[Index] ? 5381 : (VariadicHashString(lString, Index + 1) * 33) ^ lString[Index];
		}
		static constexpr UInt64 VariadicHash(UInt64 lHash, UInt64 lValue) { return lValue + (lHash << 6) + (lHash << 16) - lHash; }
	protected:

		inline void HashValueInternal(const UInt64 lValue) { mHash = VariadicHash(mHash, lValue); }

		template<class T> void HashValueInternal(const T *lValue, Size lElements)
		{
			while (lElements--) { HashValueInternal(*lValue++); }
		}
		UInt64 mHash;
	};

}