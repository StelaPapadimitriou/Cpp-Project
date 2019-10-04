#ifndef BASE_F
#define BASE_F

#include "Vec3.h"
#include "Image.h"
using namespace math;
using namespace imaging;

class BaseFilter {
public:
	virtual bool filter(Image & image) = 0;

	virtual ~BaseFilter(){}
};


#endif