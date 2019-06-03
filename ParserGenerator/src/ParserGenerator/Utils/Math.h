#pragma once

namespace ParserGenerator {

	class Math
	{
	public:
		template<typename T>
		static inline T Min(const T& A, const T& B)
		{
			return (A < B) ? A : B;
		}

		template<typename T>
		static inline T Min3(float A, float B, float C)
		{
			return Min(Min(A, B), C);
		}

		template<typename T>
		static inline T Max(const T& A, const T& B)
		{
			return (A > B) ? A : B;
		}

		template<typename T>
		static inline T Max3(float A, float B, float C)
		{
			return Max(Max(A, B), C);
		}
	};

}