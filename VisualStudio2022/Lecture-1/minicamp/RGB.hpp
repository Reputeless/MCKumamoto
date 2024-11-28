#pragma once
#include <iostream> // std::ostream, std::istream
#include <concepts> // std::integral
#include <format> // std::formatter
#include "Common.hpp"

namespace mini
{
	/// @brief 色（RGBA）
	struct RGB
	{
		/// @brief 赤成分
		uint8 r;

		/// @brief 緑成分
		uint8 g;

		/// @brief 青成分
		uint8 b;

		/// @brief デフォルトコンストラクタ
		[[nodiscard]]
		RGB() = default;

		/// @brief 色を作成します。
		/// @param rgb RGB 成分 [0, 255]
		[[nodiscard]]
		explicit constexpr RGB(uint8 rgb) noexcept
			: r{ rgb }
			, g{ rgb }
			, b{ rgb } {}

		/// @brief 色を作成します。
		/// @param rgb RGB 成分 [0, 255]
		[[nodiscard]]
		explicit constexpr RGB(std::integral auto rgb) noexcept
			: r{ static_cast<uint8>(rgb) }
			, g{ static_cast<uint8>(rgb) }
			, b{ static_cast<uint8>(rgb) } {}

		/// @brief 色を作成します。
		/// @param _r R 成分 [0, 255]
		/// @param _g G 成分 [0, 255]
		/// @param _b B 成分 [0, 255]
		[[nodiscard]]
		constexpr RGB(uint8 _r, uint8 _g, uint8 _b) noexcept
			: r{ _r }
			, g{ _g }
			, b{ _b } {}

		/// @brief 色を作成します。
		/// @param _r R 成分 [0, 255]
		/// @param _g G 成分 [0, 255]
		/// @param _b B 成分 [0, 255]
		[[nodiscard]]
		constexpr RGB(std::integral auto _r, std::integral auto _g, std::integral auto _b) noexcept
			: r{ static_cast<uint8>(_r) }
			, g{ static_cast<uint8>(_g) }
			, b{ static_cast<uint8>(_b) } {}

		[[nodiscard]]
		friend constexpr bool operator ==(const RGB& lhs, const RGB& rhs) noexcept = default;

		/// @brief グレースケール値を返します。
		/// @return グレースケール値
		[[nodiscard]]
		constexpr uint8 grayscaleUint8() const noexcept
		{
			return static_cast<uint8>((0.299 * r) + (0.587 * g) + (0.114 * b));
		}

		/// @brief グレースケール値を返します。
		/// @return グレースケール値
		[[nodiscard]]
		constexpr double grayscale() const noexcept
		{
			return ((0.299 / 255.0 * r) + (0.587 / 255.0 * g) + (0.114 / 255.0 * b));
		}

		/// @brief 出力ストリームに書き込みます。
		/// @param os 出力ストリーム
		/// @param c 書き込む値
		/// @return 出力ストリーム
		friend std::ostream& operator <<(std::ostream& os, const RGB& c)
		{
			return os << '(' << static_cast<uint16>(c.r) << ", "
				<< static_cast<uint16>(c.g) << ", "
				<< static_cast<uint16>(c.b) << ')';
		}

		/// @brief 入力ストリームから読み込みます。
		/// @param is 入力ストリーム
		/// @param c 読み込んだ値の格納先
		/// @return 入力ストリーム
		friend std::istream& operator >>(std::istream& is, RGB& c)
		{
			char t;
			uint16 r, g, b;
			is >> t >> r >> t >> g >> t >> b >> t;

			c.r = static_cast<uint8>(r);
			c.g = static_cast<uint8>(g);
			c.b = static_cast<uint8>(b);
			return is;
		}
	};

	namespace Palette
	{
		/// @brief 黒色
		inline constexpr RGB Black{ 0, 0, 0 };

		/// @brief 白色
		inline constexpr RGB White{ 255, 255, 255 };
	}
}

/// @brief RGB 型を std::format に対応させるための std::formatter 特殊化
template<>
struct std::formatter<mini::RGB>
{
	template <class ParseContext>
	constexpr auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <class FormtContext>
	auto format(const mini::RGB& c, FormtContext& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {}, {})", c.r, c.g, c.b);
	}
};
