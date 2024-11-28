#include <algorithm> // std::ranges::fill
#include "Image.hpp"
#include "BMP.hpp"

namespace mini
{
	Image::Image(const std::string_view path)
	{
		*this = LoadBMP(path);
	}

	void Image::fill(const RGB& color) noexcept
	{
		std::ranges::fill(m_pixels, color);
	}

	bool Image::save(const std::string_view path) const
	{
		return SaveBMP(*this, path);
	}
}
