#ifndef NEIGH_F
#define NEIGH_F


#include <iostream>
#include <vector>
#include "Image.h"
#include "BaseFilter.h"
#include "Vec3.h"
using std::vector;
using namespace math;
using namespace imaging;

class Blur :public BaseFilter {
	public:
		bool filter(Image & image);
};

class Median :public BaseFilter {
public:
	bool filter(Image & image);
	float getMedian(const vector<float> & data);
};

class Diff :public BaseFilter {
public:
	bool filter(Image & image);
};

#endif