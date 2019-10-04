#include "Image.h"
#include "Array.h"
#include "ppm_format.h"
#include <iostream>
using namespace math;
using namespace std;

namespace imaging {
	/*! Reads the contents of an object from the specified file.
	*
	*  The operator can be used for the implementation of "de-serialization".
	*
	*  \param filename is the name of the file to use for loading the data.
	*
	*  \return true if the operation was successful, false otherwise.
	*/
	bool Image::operator << (std::string filename){

		Image *img;
		img = imaging::ReadPPM(filename.c_str());

		if (img == nullptr) {
			return false;
		}
		else {
			*this = *img;
			delete img;
			return true;
			
		}

	}
	/*! Writes the contents of an object to the specified file.
	*
	*  The operator can be used for the implementation of "serialization".
	*
	*  \param filename is the name of the file to use for saving the data.
	*
	*  \return true if the operation was successful, false otherwise.
	*/
	bool Image::operator >> (std::string filename){

		bool result = WritePPM(*this, filename.c_str());

		return result;
	}
	//Image's method getPixel using Array's operator()
	Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const {
		Vec3<float> c;
		c = operator()(x, y);
		return c;
	}
	//Image's method setPixel using Array's operator() const
	void Image::setPixel(unsigned int x, unsigned int y, Vec3<float> & value) {
		Vec3<float> & c = operator()(x, y);
		c = value;
	}
	//Image's method setData
	void Image::setData(const Vec3<float> * & data_ptr) {
		if (width == 0 & height == 0 && buffer == nullptr)
			return;
		else{
			for (int i = 0; i < width*height; i++) {
				buffer[i] = data_ptr[i];
			}

		}
	}
	//Default constructor
	Image::Image() :Array(0, 0) {
		buffer = nullptr;
	}
	//Image Constructor
	Image::Image(unsigned int width, unsigned int height) : Array(width, height) {}
	//Constructor with data initialization
	Image::Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr) : Array(width, height) {
		for (int i = 0; i < width*height; i++) {
			buffer[i] = data_ptr[i];
		}
	}
	//Copy constructor
	Image::Image(const Image & src) : Array(src) {}

}//namespace