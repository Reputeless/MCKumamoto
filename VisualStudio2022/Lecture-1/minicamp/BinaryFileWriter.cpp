﻿#include <fstream> // std::ofstream
#include <filesystem> // std::filesystem::absolute
#include "BinaryFileWriter.hpp"

namespace mini
{
	class BinaryFileWriter::Impl
	{
	public:

		Impl() = default;

		~Impl()
		{
			close();
		}

		[[nodiscard]]
		bool isOpen() const noexcept
		{
			return m_file.is_open();
		}

		bool open(const std::string_view path)
		{
			if (m_file.is_open())
			{
				close();
			}

			m_file.open(std::string{ path }, std::ios::binary);

			if (m_file.is_open())
			{
				m_fullPath = std::filesystem::absolute(path).string();

				return true;
			}
			else
			{
				return false;
			}
		}

		void close()
		{
			m_file.close();

			m_fullPath.clear();
		}

		void write(const void* data, const size_t size)
		{
			m_file.write(static_cast<const char*>(data), size);
		}

		[[nodiscard]]
		const std::string& fullPath() const noexcept
		{
			return m_fullPath;
		}

	private:

		std::ofstream m_file;

		std::string m_fullPath;
	};

	BinaryFileWriter::BinaryFileWriter()
		: m_pImpl{ std::make_shared<Impl>() } {}

	BinaryFileWriter::BinaryFileWriter(const std::string_view path)
		: BinaryFileWriter{} // 移譲コンストラクタ
	{
		m_pImpl->open(path);
	}

	bool BinaryFileWriter::isOpen() const noexcept
	{
		return m_pImpl->isOpen();
	}

	BinaryFileWriter::operator bool() const noexcept
	{
		return m_pImpl->isOpen();
	}

	bool BinaryFileWriter::open(const std::string_view path)
	{
		return m_pImpl->open(path);
	}

	void BinaryFileWriter::close()
	{
		m_pImpl->close();
	}

	const std::string& BinaryFileWriter::fullPath() const noexcept
	{
		return m_pImpl->fullPath();
	}

	void BinaryFileWriter::write(const void* data, const size_t size)
	{
		m_pImpl->write(data, size);
	}
}
