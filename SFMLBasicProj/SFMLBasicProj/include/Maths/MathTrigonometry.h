#ifndef __TRIG_H_
#define __TRIG_H_

#include <cmath>

/////////////////////////////////
//-----TRIGONOMETRY-------------
// Is the study of triangles; their angles, lengths etc.
// It helps us find angles and distances.
////////////////////////////////

// In Trigonometry, we may have to convert radians to degrees and vice versa.
// Degree = (180 / pi) * Radian
// Radian = (pi / 180) * Degree

/*
  .
  |'.
  |x '. c
a |    '.
  |______'.
     b
*/

// We have Trigonometric Functions used for Deg to Rad conversion: 
// sin(x) = b/c
// cos(x) = a/c
// tan(x) = b/a

// And Inverse Trigonometric Functions used for Rad to Deg conversion:
// arcSin(b/c) = x
// arcCos(a/c) = x
// arcTan(b/a) = x		// Note that angle = arcTan(y/x)

namespace sf
{

	template <typename T>
	struct Trig
	{
	};

	template <typename T>
	T toDegree(T radian_p)
	{
		return Trig<T>::radToDeg(radian_p);
	}

	template <typename T>
	T toRadian(T degree_p)
	{
		return Trig<T>::degToRad(degree_p);
	}

}
#include "MathTrigonometry.inl"

#endif 
