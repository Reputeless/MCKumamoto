﻿#pragma once
#include <concepts> // std::integral
#include <vector> // std::vector
#include "Common.hpp"
#include "RGB.hpp"
#include "Point.hpp"

namespace mini
{
	/// @brief 画像
	class Image
	{
	public:

		/// @brief 使用する配列型
		using container_type = std::vector<RGB>;

		/// @brief 要素を指すイテレータ型
		using iterator = container_type::iterator;

		/// @brief 要素を指す const イテレータ型
		using const_iterator = container_type::const_iterator;

		/// @brief デフォルトコンストラクタ
		[[nodiscard]]
		Image() = default;

		/// @brief 画像を作成します。
		/// @param width 画像の幅（ピクセル）
		/// @param height 画像の高さ（ピクセル）
		/// @param color 画像の初期色
		[[nodiscard]]
		Image(int32 width, int32 height, const RGB& color = Palette::White)
			: m_pixels{ (static_cast<size_t>(width) * static_cast<size_t>(height)), color }
			, m_size{ width, height } {}

		/// @brief 画像を作成します。
		/// @param width 画像の幅（ピクセル）
		/// @param height 画像の高さ（ピクセル）
		/// @param color 画像の初期色
		[[nodiscard]]
		Image(std::integral auto width, std::integral auto height, const RGB& color = Palette::White)
			: Image{ static_cast<int32>(width), static_cast<int32>(height), color } {}

		/// @brief 画像を作成します。
		/// @param size 画像の幅と高さ（ピクセル）
		/// @param color 画像の初期色
		[[nodiscard]]
		Image(const Size& size, const RGB& color = Palette::White)
			: Image{ size.x, size.y, color } {}

		/// @brief ファイルからデータを読み込んで画像を作成します。
		/// @param path 画像ファイルのパス
		[[nodiscard]]
		explicit Image(std::string_view path);

		/// @brief 2 つの画像が等しいかを返します。
		/// @param lhs 一方の画像データ
		/// @param rhs もう一方の画像データ
		/// @return 2 つの画像が等しい場合 true, それ以外の場合は false
		[[nodiscard]]
		friend bool operator ==(const Image& lhs, const Image& rhs) noexcept
		{
			// 画像の中身を比較する前に、画像のサイズを比較する
			return ((lhs.m_size == rhs.m_size) && (lhs.m_pixels == rhs.m_pixels));
		}

		/// @brief 画像の幅（ピクセル）を返します。
		/// @return 画像の幅（ピクセル）
		[[nodiscard]]
		int32 width() const noexcept
		{
			return m_size.x;
		}

		/// @brief 画像の高さ（ピクセル）を返します。
		/// @return 画像の高さ（ピクセル）
		[[nodiscard]]
		int32 height() const noexcept
		{
			return m_size.y;
		}

		/// @brief 画像の幅と高さ（ピクセル）を返します。
		/// @return 画像の幅と高さ（ピクセル）
		[[nodiscard]]
		Size size() const noexcept
		{
			return m_size;
		}

		/// @brief 画像の総ピクセル数を返します。
		/// @return 画像の総ピクセル数
		[[nodiscard]]
		size_t numPixels() const noexcept
		{
			return m_pixels.size();
		}

		/// @brief 画像が空であるかを返します。
		/// @return 画像が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept
		{
			return m_pixels.empty();
		}

		/// @brief 画像が空でないかを返します。
		/// @return 画像が空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept
		{
			return (!m_pixels.empty());
		}

		/// @brief 指定した行の先頭ポインタを返します。
		/// @param y 位置（行）
		/// @remark image[y][x] で指定したピクセルにアクセスします。
		/// @return 指定した行の先頭ポインタ
		[[nodiscard]]
		RGB* operator [](size_t y) noexcept MINI_LIFETIMEBOUND
		{
			return (m_pixels.data() + (y * m_size.x));
		}

		/// @brief 指定した行の先頭ポインタを返します。
		/// @param y 位置（行）
		/// @remark image[y][x] で指定したピクセルにアクセスします。
		/// @return 指定した行の先頭ポインタ
		[[nodiscard]]
		const RGB* operator [](size_t y) const noexcept MINI_LIFETIMEBOUND
		{
			return (m_pixels.data() + (y * m_size.x));
		}

		/// @brief 画像データの先頭ポインタを返します。
		/// @return 画像データの先頭ポインタ
		[[nodiscard]]
		RGB* data() noexcept MINI_LIFETIMEBOUND
		{
			return m_pixels.data();
		}

		/// @brief 画像データの先頭ポインタを返します。
		/// @return 画像データの先頭ポインタ
		[[nodiscard]]
		const RGB* data() const noexcept MINI_LIFETIMEBOUND
		{
			return m_pixels.data();
		}

		/// @brief 画像を空にします。
		void clear() noexcept
		{
			m_pixels.clear();
			m_size.clear();
		}

		/// @brief 画像をリサイズします。
		/// @param width 新しい画像の幅（ピクセル）
		/// @param height 新しい画像の高さ（ピクセル）
		/// @param color 新しい画像の初期色
		void resize(int32 width, int32 height, const RGB& color = Palette::White)
		{
			m_pixels.assign(width * height, color);
			m_size.set(width, height);
		}

		/// @brief 画像をリサイズします。
		/// @param size 新しい画像の幅と高さ（ピクセル）
		/// @param color 新しい画像の初期色
		void resize(const Size& size, const RGB& color = Palette::White)
		{
			resize(size.x, size.y, color);
		}

		/// @brief 画像を指定した色で塗りつぶします。
		/// @param color 塗りつぶしの色
		void fill(const RGB& color) noexcept;

		/// @brief 2 つの画像をスワップします。
		/// @param other もう一方の画像
		void swap(Image& other) noexcept
		{
			m_pixels.swap(other.m_pixels);
			std::ranges::swap(m_size, other.m_size);
		}

		/// @brief ピクセル配列の先頭位置を指すイテレータを返します。
		/// @return ピクセル配列の先頭位置を指すイテレータ
		[[nodiscard]]
		iterator begin() noexcept MINI_LIFETIMEBOUND
		{
			return m_pixels.begin();
		}

		/// @brief ピクセル配列の終端位置を指すイテレータを返します。
		/// @return ピクセル配列の終端位置を指すイテレータ
		[[nodiscard]]
		iterator end() noexcept MINI_LIFETIMEBOUND
		{
			return m_pixels.end();
		}

		/// @brief ピクセル配列の先頭位置を指すイテレータを返します。
		/// @return ピクセル配列の先頭位置を指すイテレータ
		[[nodiscard]]
		const_iterator begin() const noexcept MINI_LIFETIMEBOUND
		{
			return m_pixels.begin();
		}

		/// @brief ピクセル配列の終端位置を指すイテレータを返します。
		/// @return ピクセル配列の終端位置を指すイテレータ
		[[nodiscard]]
		const_iterator end() const noexcept MINI_LIFETIMEBOUND
		{
			return m_pixels.end();
		}

		/// @brief 画像をファイルに保存します。
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(std::string_view path) const;

		/// @brief 2 つの画像をスワップします。
		/// @param lhs 一方の画像
		/// @param rhs もう一方の画像
		friend void swap(Image& lhs, Image& rhs) noexcept
		{
			lhs.swap(rhs);
		}

	private:

		container_type m_pixels;

		Size m_size{ 0, 0 };
	};
}
