#include <print>
#include "Common.hpp"
#include "Point.hpp"
#include "BinaryFileWriter.hpp"
#include "BinaryFileReader.hpp"
#include "RGB.hpp"
#include "Image.hpp"
#include "BMP.hpp"

int main()
{
	auto it = mini::Image{256,256}.begin();
	
	it->r = 34;
	
	std::println("Hello, minicamp!");
}
