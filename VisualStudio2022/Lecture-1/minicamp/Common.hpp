#pragma once // このヘッダファイルが 1 度だけインクルードされるようにするためのインクルードガード
#include <cstdint> // std::int8_t, std::int16_t, ...
#include "Common.hpp"

namespace mini
{
	using int8  = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;

	using uint8  = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;
}

// lifetimebound 属性（コンパイラ拡張）を利用するためのマクロ
#if defined(_MSC_VER) // MSVC
	#define MINI_LIFETIMEBOUND [[msvc::lifetimebound]]
	#include <CppCoreCheck/Warnings.h>
	#pragma warning(default: CPPCORECHECK_LIFETIME_WARNINGS)
#elif defined(__clang__) // Clang
	#define MINI_LIFETIMEBOUND [[clang::lifetimebound]]
#else
	#define MINI_LIFETIMEBOUND
#endif
