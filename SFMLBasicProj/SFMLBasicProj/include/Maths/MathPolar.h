#ifndef __POLARVECTOR_H_
#define __POLARVECTOR_H_

#include <SFML/System/Vector2.hpp>


///////////////////////////////////////////////////
//------POLAR COORDINATES--------------------------
// A method to pinpoint where you are on a map
// by how far away and at what angle the point is.
//////////////////////////////////////////////////

/*
Y          // This is the length (i.e. radius)
^        *
|      .'
|    .' ^
|  .'   |    // This is the angle
|.'     V
|------------------>X

|Note that:
r = radius
phi = angle
*/

// To convert from Polar Coordinates (r, angle) to Cartesian Coordinates (x, y)
// x = r * cos(angle),		y = r * sin(angle)
namespace sf
{

	template <typename T>
	struct Polar2
	{
		T	r;
		T	phi;
		Polar2();
		Polar2(T radius_p, T angle_p);
		Polar2(const sf::Vector2<T>& vector_p);
		operator sf::Vector2<T>() const;
	};

	typedef Polar2<float> Polar2f;

	template <typename T>
	T length(const Polar2<T>& vector_p);

	template <typename T>
	T polarAngle(const Polar2<T>& vector_p);
}

#include "MathPolar.inl"
#endif 
