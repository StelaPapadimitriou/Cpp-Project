#ifndef _IMAGE
#define _IMAGE

#include "Vec3.h"
#include "Array.h"
#include "Serializable.h"

using namespace math;

namespace imaging {

	class Image : public Array <Vec3<float>>, public Serializable {
	public:

		bool operator << (std::string filename);

		bool operator >> (std::string filename);

		Vec3<float> getPixel(unsigned int x, unsigned int y) const;
		
		void setPixel(unsigned int x, unsigned int y, Vec3<float> & value);

		void setData(const Vec3<float> * & data_ptr);

		Image();

		Image(unsigned int width, unsigned int height);

		Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr);

		Image(const Image & src);

	};

}//namespace

#endif // !_IMAGE