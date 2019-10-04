#include <iostream>
#include <vector>
#include <algorithm>
#include "Image.h"
#include "BaseFilter.h"
#include "NeighborhoodFilters.h"

using namespace imaging;

bool Blur::filter(Image & image) {
	Image original = image; // copy constructor
	Vec3<float> c;

	for (int i = 0; i < image.getWidth(); i++) {
		for (int j = 0; j < image.getHeight(); j++) {
			int V;
			int sum = 0;
			float mr = 0;
			float mg = 0;
			float mb = 0;

			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					c = original.getPixel(i + m, j + n);
					//Out-of-bounds checking.
					if ((m + i) > 0 && (m + i) < (image.getWidth() - 1) && (j + n) > 0 && (j + n) < (image.getHeight()-1))
						V = 1;
					else
						V = 0;
					//sum of the neighbouring pixels
					sum += V;
					//Finding new rgb values
					if (V == 1) {
						mr += c.r;
						mg += c.g;
						mb += c.b;
					}
				}
			}
			float mor = mr/sum;
			float mog = mg / sum;
			float mob = mb / sum;

			c.r = mor;
			c.g = mog;
			c.b = mob;
			image.setPixel(i,j,c);
		}
	}return true;
}

bool Median::filter(Image & image) {
	Image original = image; // copy constructor
	Vec3<float> c;

	vector <float> red;
	vector <float> green;
	vector <float> blue;
	unsigned int w = image.getWidth();
	unsigned int h = image.getHeight();

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			int V;
			int sum = 0;
			//Using vectors to store rgb values
			red.clear();
			green.clear();
			blue.clear();

			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					c = original.getPixel(i + m, j + n);
					if ((m + i) > 0 && (m + i) < (w - 1) && (j + n) > 0 && (j + n) < (h - 1))
						V = 1;
					else
						V = 0;
					sum += V;
					if (V == 1) {
						red.push_back( c.r );
						green.push_back(c.g);
						blue.push_back(c.b);
					}
				}
			}
			//sorting vectors
			sort(red.begin(), red.end());
			sort(green.begin(), green.end());
			sort(blue.begin(), blue.end());

			//Get the median value
			c.r = getMedian(red);
			c.g = getMedian(green);
			c.b = getMedian(blue);
			image.setPixel(i, j, c);
		}
	}
	
	return true;

}

float Median::getMedian(const vector<float> & data) {
	return data[data.size()/2];
}

bool Diff::filter(Image & image) {
	Image original = image; // copy constructor
	Vec3<float> c;

	vector <float> red;
	vector <float> green;
	vector <float> blue;
	unsigned int w = image.getWidth();
	unsigned int h = image.getHeight();

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < image.getHeight(); j++) {
			int V;
			int sum = 0;
			red.clear();
			green.clear();
			blue.clear();

			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					c = original.getPixel(i + m, j + n);
					if ((m + i) > 0 && (m + i) < (w - 1) && (j + n) > 0 && (j + n) < (h - 1))
						V = 1;
					else
						V = 0;
					sum += V;
					if (V == 1) {
						red.push_back(c.r);
						green.push_back(c.g);
						blue.push_back(c.b);
					}
				}
			}

			sort(red.begin(), red.end());
			sort(green.begin(), green.end());
			sort(blue.begin(), blue.end());

			c.r = red[red.size() - 1] - red[0];
			c.g = green[green.size() - 1] - green[0];
			c.b = blue[blue.size() - 1] - blue[0];
			image.setPixel(i, j, c);
		}
	}return true;
}
		


