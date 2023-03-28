namespace sf
{

	template <typename T>
	Polar2<T>::Polar2()
		: r(), phi()
	{
	}

	template <typename T>
	Polar2<T>::Polar2(T radius_p, T angle_p)
		: r(radius_p), phi(angle_p)
	{
	}

	template <typename T>
	Polar2<T>::Polar2(const sf::Vector2<T>& vector_p)
		: r(length(vector_p)), phi(vector_p == sf::Vector2<T>() ? 0.f : polarAngle(vector_p))
	{
	}

	template <typename T>
	Polar2<T>::operator sf::Vector2<T>() const
	{
		return sf::Vector2<T>(r * Trig<T>::cos(phi), r * Trig<T>::sin(phi));
	}

	template <typename T>
	T length(const Polar2<T>& vector_p)
	{
		return vector_p.r;
	}

	template <typename T>
	T polarAngle(const Polar2<T>& vector_p)
	{
		return vector_p.phi;
	}

}