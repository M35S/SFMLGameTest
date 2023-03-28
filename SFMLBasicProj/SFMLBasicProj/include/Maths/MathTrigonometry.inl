namespace sf
{
	template <>
	struct Trig < float >
	{
		typedef float Type;
		static Type sin(Type degrees_p)						{ return std::sin(degToRad(degrees_p)); }
		static Type cos(Type degrees_p)						{ return std::cos(degToRad(degrees_p)); }
		static Type tan(Type degrees_p)						{ return std::tan(degToRad(degrees_p)); }
		static Type arcSin(Type value_p)					{ return radToDeg(std::asin(value_p)); }
		static Type arcCos(Type value_p)					{ return radToDeg(std::acos(value_p)); }
		static Type arcTan2(Type valueY_p, Type valueX_p)	{ return radToDeg(std::atan2(valueY_p, valueX_p)); }
		static Type sqrt(Type value_p)						{ return std::sqrt(value_p); }

		static Type pi()									{ return 3.141592653589793238462643383f; }
		static Type radToDeg(Type radians_p)				{ return 180 / pi() * radians_p; }
		static Type degToRad(Type degrees_p)				{ return pi() / 180 * degrees_p; }
	};

	template <>
	struct Trig < double >
	{
		typedef double Type;
		static Type sin(Type degrees_p)						{ return std::sin(degToRad(degrees_p)); }
		static Type cos(Type degrees_p)						{ return std::cos(degToRad(degrees_p)); }
		static Type tan(Type degrees_p)						{ return std::tan(degToRad(degrees_p)); }
		static Type arcSin(Type value_p)					{ return radToDeg(std::asin(value_p)); }
		static Type arcCos(Type value_p)					{ return radToDeg(std::acos(value_p)); }
		static Type arcTan2(Type valueY_p, Type valueX_p)	{ return radToDeg(std::atan2(valueY_p, valueX_p)); }
		static Type sqrt(Type value_p)						{ return std::sqrt(value_p); }

		static Type pi()									{ return 3.141592653589793238462643383; }
		static Type radToDeg(Type radians_p)				{ return 180 / pi() * radians_p; }
		static Type degToRad(Type degrees_p)				{ return pi() / 180 * degrees_p; }
	};
}