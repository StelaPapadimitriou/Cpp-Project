#ifndef LOCAL_F
#define LOCAL_F


#include "Vec3.h"
#include "Image.h"
#include "BaseFilter.h"
using namespace math;
using namespace imaging;

class Gray :public BaseFilter {
public:
	bool filter(Image & image);
};

class Color :public BaseFilter {
public:
	bool filter(Image & image);
	void setColor(Vec3<float> c);
private:
	Vec3<float> c;
	
};

#endif