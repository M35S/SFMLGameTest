#ifndef VECTORMATH_H_
#define VECTORMATH_H_

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "MathTrigonometry.h"
#include <cassert>

/*
====================================================
Vector Maths / Operations
====================================================

*/

// Dot Product, Uint Vector, Polar Angle
// Rotate (cos and sin)
// Perpendicular Vector
// Signed Angle (arcTAN, cross product, dot product)
// cwise product
// cwise quotient
// projected vector (dot product, squared length)
// tof, tou, toi

namespace sf
{

	template <typename T>
	T vectorLength(const sf::Vector2<T>& vector_p);

	template <typename T>
	T squaredVectLength(const sf::Vector2<T>& vector_p);

	template <typename T>
	void setVectLength(sf::Vector2<T>& vector_p, T newLength_p);

	template <typename T>
	sf::Vector2<T> unitVector(const sf::Vector2<T>& vector_p);

	template <typename T>
	T polarAngle(const sf::Vector2<T>& vector_p);

	template <typename T>
	void setPolarAngle(sf::Vector2<T>& vector_p, T newAngle_p);

	template <typename T>
	void rotateVectors(sf::Vector2<T>& vector_p, T angle_p);

	template <typename T>
	sf::Vector2<T> rotatedVector(const sf::Vector2<T>& vector_p, T angle_p);

	template <typename T>
	sf::Vector2<T> perpendicularVector(const sf::Vector2<T>& vector_p);

	template <typename T>
	T signedAngle(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p);

	template <typename T>
	T dotProduct(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p);

	template <typename T>
	sf::Vector2<T> cwiseProduct(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p);

	template <typename T>
	sf::Vector2<T> cwiseQuotient(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p);

	template <typename T>
	sf::Vector2<T> projectedVector(const sf::Vector2<T>& vector_p, const sf::Vector2<T>& axis_p);

	//-----------VECTOR TYPE CONVERSION FUNCTIONS-------------------------------------------------------

	inline sf::Vector2f toFloat(sf::Vector2u uInt_p);

	inline sf::Vector2f toFloat(sf::Vector2i int_p);

	inline sf::Vector2u toUnsignedInt(sf::Vector2f float_p);

	inline sf::Vector2u toUnsignedInt(sf::Vector2i int_p);

	inline sf::Vector2i toInt(sf::Vector2f float_p);

	inline sf::Vector2i toInt(sf::Vector2u uInt_p);

	//-----------RECTANGLE - VECTOR CONVERSION FUNCTIONS------------------------------------------------

	inline sf::Vector2f topLeftRect(sf::FloatRect rect_p);

	inline sf::Vector2f topRightRect(sf::FloatRect rect_p);

	inline sf::Vector2f btmLeftRect(sf::FloatRect rect_p);

	inline sf::Vector2f btmRightRect(sf::FloatRect rect_p);

	inline int floatToIntRnding(float float_p);

	inline sf::Vector2f toRectDimFloat(sf::FloatRect rect_p);

	inline sf::Vector2i toRectDimInt(sf::FloatRect rect_p);

	inline sf::Vector2f topLeftRect(sf::IntRect rect_p);

	inline sf::Vector2f topRightRect(sf::IntRect rect_p);

	inline sf::Vector2f btmLeftRect(sf::IntRect rect_p);

	inline sf::Vector2f btmRightRect(sf::IntRect rect_p);

	inline sf::Vector2f toRectDimFloat(sf::IntRect rect_p);

	inline sf::Vector2i toRectDimInt(sf::IntRect rect_p);

	//-----------RECTANGLE TYPE CONVERSION FUNCTIONS------------------------------------------------

	inline sf::IntRect  toInt(sf::FloatRect rect_p);

	inline sf::FloatRect toFloat(sf::IntRect rect_p);

	//-----------VECTOR - RECTANGLE CONVERSION FUNCTIONS--------------------------------------------

	inline sf::IntRect fromRectDimInt(sf::Vector2f dimension_p);

	inline sf::IntRect fromRectDimInt(sf::Vector2i dimension_p);

	inline sf::FloatRect fromRectDimFloat(sf::Vector2f dimension_p);

	inline sf::FloatRect fromRectDimFloat(sf::Vector2i dimension_p);

}

#include "MathVector.inl"
#endif 
