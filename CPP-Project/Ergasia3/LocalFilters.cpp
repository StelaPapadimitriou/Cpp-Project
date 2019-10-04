#include <iostream>
#include "Image.h"
#include "BaseFilter.h"
#include "LocalFilters.h"
#include "Vec3.h"

using namespace math;
using namespace imaging;

Vec3<float> color;
Vec3<float> c;

bool Gray::filter(Image & image) {	
	float m;
	
	for (int i = 0; i < image.getWidth(); i++) {
		for (int j = 0; j < image.getHeight(); j++) {
			//get a pixel from image
			color = image.getPixel(i, j);
			m = (color.r+color.g+color.b)/3.0;

			color.r = m;
			color.g = m;
			color.b = m;
			//set new rgb values
			image.setPixel(i,j,color);
		}
	}
	return true;
}

bool Color::filter(Image & image) {

	for (int i = 0; i < image.getWidth(); i++) {
		for (int j = 0; j < image.getHeight(); j++) {
			color = image.getPixel(i, j);

			color.r *= c.r;
			color.g *= c.g;
			color.b *= c.b;
			image.setPixel(i, j, color);
		}
	}return true;
}

	void Color::setColor(Vec3<float> c) {
		this->c = c;
	}
