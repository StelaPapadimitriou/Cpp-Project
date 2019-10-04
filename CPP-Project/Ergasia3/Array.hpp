//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include "Array.h"

namespace math
{
		/*! Obtains a constant pointer to the internal data.
		*
		*  This is NOT a copy of the internal array data, but rather a pointer
		*  to the internally allocated space.
		*/

		template <typename T>
		void * const Array<T>::getRawDataPtr() {
			return buffer;
		}

		/*! Returns a reference to the element at the zero-based position (column x, row y).
		*
		* \param x is the zero-based column index of the array.
		* \param y is the zero-based row index of the array.
		*
		* \return a reference to the element at position (x,y)
		*/

		template <typename T>
		T & Array<T>::operator () (int x, int y)
		{
			if (x < width && y < height) {
				return buffer[y*width + x];
			}
			else {
				return buffer[0];
			}
		}

		/*! Returns a constant reference to the element at the zero-based position (column x, row y).
		*
		* \param x is the zero-based column index of the array.
		* \param y is the zero-based row index of the array.
		*
		* \return a reference to the element at position (x,y)
		*/
		template <typename T>
		const T & Array<T>::operator () (int x, int y) const
		{
			if (x < width && y < height) {
				return buffer[y*width + x];
			}
			else {
				return buffer[0];
			}
		}

		/*! Constructor with array size.
		*
		* No default constructor is provided as it makes no sense.
		*
		* \param w is the width (columns) of the array
		* \param h is the height (rows) of the array
		*/
		template <typename T>
		Array<T>::Array(unsigned int w, unsigned int h) {
			width = w;
			height = h;
			buffer = new T[w*h];
		}

		/*! Copy constructor.
		*
		* No default constructor is provided as it makes no sense.
		*
		* \param source is the array to replicate.
		*/
		template <typename T>
		Array<T>::Array(const Array<T> & source) :Array(source.width, source.height) {
			width = source.width;
			height = source.height;
			buffer = new T[height * width];
			for (unsigned int i = 0; i < (height*width); i++) {
				buffer[i] = source.buffer[i];
			}
		}

		/*! Copy assignment operator
		*
		* \param source is the array to replicate.
		*/
		template <typename T>
		Array<T> & Array<T>::operator = (const Array<T> & source) {
			if (this != &source) {
				width = source.width;
				height = source.height;
				delete[]buffer;
				buffer = new T[height * width];
				for (unsigned int i = 0; i < (height*width); i++) {
					buffer[i] = source.buffer[i];
				}
			}
			return *this;
		}

		/*! Equality operator.
		*
		*  \param right is the array to compare the current object to.
		*
		*  \return true if the current array and the source have the same dimensions AND
		*  one by one their elements of type T are the same.
		*/
		template <typename T>
		bool Array<T>::operator == (const Array<T> & source) const
		{
			if (width == right.width && height == right.height) {
				for (int = 0; i < width*height; i++) {
					if (buffer[i] != right.buffer[i]) {
						return false;
					}
				}return true;
			}return false;
		}


		/*! Changes the internal array data storage size.
		*
		* If the one or both of the given dimensions are smaller, the array should be clipped
		* by discarding the remaining elements in the rows and/or columns outside the margins.
		* If the new dimensions are larger, pad the old elements with default values of type T.
		* If the array is not yet allocated (zero width and height), allocate the internal buffer and
		* set the array size according to the given dimensions.
		*
		* \param new_width is the user-provided width to resize the array to.
		* \param new_height is the user-provided height to resize the array to.
		*/
		template <typename T>
		void Array<T>::resize(unsigned int new_width, unsigned int new_height) {
			T * temp_buffer = new T[new_width*new_height];

			for (unsigned int i = 0; i < new_width; i++) {

				for (unsigned int j = 0; j < new_height; j++) {

					unsigned int oldpos, newpos;

					oldpos = j * width + i;
					newpos = j * new_width + i;

					if (i < width && j < height) {

						temp_buffer[newpos + 0] = buffer[oldpos + 0];
						temp_buffer[newpos + 1] = buffer[oldpos + 1];
						temp_buffer[newpos + 2] = buffer[oldpos + 2];
					}
					else {
						temp_buffer[newpos + 0] = 0.0;
						temp_buffer[newpos + 1] = 0.0;
						temp_buffer[newpos + 2] = 0.0;
					}
				}
			}
		}

		/*! Virtual destructor.
		*/
		template <typename T>
		Array<T>::~Array() {
			delete[] buffer;
		}

	} // namespace math


#endif