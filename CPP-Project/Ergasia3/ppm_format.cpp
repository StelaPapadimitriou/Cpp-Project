#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Array.h"
#include "Serializable.h"
#include "Image.h"
#include "ppm_format.h"

using namespace math;
using namespace std;

namespace imaging
{
	/*! Reads a PPM image file and returns a pointer to a newly allocated Image object containing the image.
	*
	*  \param filename is the null-terminated string of the name of the file to open.
	*
	*  \return a pointer to a new Image object, if the read operation was successful, nullptr otherwise.
	*/
	Image *ReadPPM(const char * filename) {
		Image * image = nullptr;
		string header;
		ifstream file;
		unsigned int width = 0, height = 0, rgb_palette = 0;
		unsigned char cR = ' ', cG = ' ', cB = ' ';

		file.open(filename, ios::binary);
		if (file.fail()) {
			cerr << "\t- Error opening file or this file does not exist\n";
			return 0;
		}
		//Read from file
		if (file.is_open()) {
			file >> header;
			if (header != "P6") {
				cerr << "- Error opening file or wrong file format\n";
				return 0;
			}
			file >> width;
			file >> height;
			file >> rgb_palette;
			if (rgb_palette != 255) {
				cerr << "- Error opening file or wrong file format\n";
				return 0;
			}
			image = new Image(width, height);

			if (image == nullptr) {
				cerr << "- No image data\t";
				return 0;
			}

			Vec3<float> *buffer = new Vec3<float>[width*height];

			file.get();//read the character "\n"

			for (unsigned int i = 0; i < width*height; i = i + 1) {

				file.read((char *)&cR, 1);
				file.read((char *)&cG, 1);
				file.read((char *)&cB, 1);


				buffer[i].r = cR / 255.0f;
				buffer[i].g = cG / 255.0f;
				buffer[i].b = cB / 255.0f;
			}

			file.close();

			const Vec3<float> *cbuffer = buffer;
			image->setData(cbuffer);

			delete[]buffer;
		}
		else {
			cerr << "Could not open this file, or this file does not exit!";
			return 0;
		}

		return image;
	}


	/*! Writes an existing image as a PPM file.
	*
	*  \param image is the Image object to save to a file in the PPM format.
	*  \param filename is the null-terminated string of the name of the file to create.
	*
	*  \return true if the image save operation was successful, false otherwise.
	*/
	bool WritePPM(Image & image, const char * filename) {

		ofstream file;
		file.open(filename, ios::binary);

		if (file.fail()) {
			cout << "- Error opening file\n"; return false;
		}
		else {
			//Write to file
			file << "P6\n";
			file << image.getWidth() << "\n";
			file << image.getHeight() << "\n";
			file << "255\n";

			const Vec3<float>  * buffer = (Vec3<float>*) image.getRawDataPtr();

			for (int i = 0; i < image.getWidth()*image.getHeight(); i++) {
				unsigned char color;
				color = buffer[i].r * 255;
				file.write((char*) & color,sizeof(char));

				color = buffer[i].g * 255;
				file.write((char*)& color, sizeof(char));

				color = buffer[i].b * 255;
				file.write((char*)& color, sizeof(char));
			}
			file.close();
			return true;
		}
	}

} //namespace imaging

