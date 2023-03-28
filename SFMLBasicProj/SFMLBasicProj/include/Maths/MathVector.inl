namespace sf
{

	template <typename T>
	T vectorLength(const sf::Vector2<T>& vector_p)
	{
		return Trig<T>::sqrt(squaredVectLength(vector_p));
	}

	template <typename T>
	T squaredVectLength(const sf::Vector2<T>& vector_p)
	{
		return dotProduct(vector_p, vector_p);
	}

	template <typename T>
	void setVectLength(sf::Vector2<T>& vector_p, T newLength_p)
	{
		assert(vector_p != sf::Vector2<T>());
		vector_p *= newLength_p / vectorLength(vector_p);
	}

	template <typename T>
	sf::Vector2<T> unitVector(const sf::Vector2<T>& vector_p)
	{
		//assert(vector != sf::Vector2<T>());
		return vector_p / vectorLength(vector_p);
	}

	template <typename T>
	T polarAngle(const sf::Vector2<T>& vector_p)
	{
		assert(vector_p != sf::Vector2<T>());
		return Trig<T>::arcTan2(vector_p.y, vector_p.x);
	}

	template <typename T>
	void setPolarAngle(sf::Vector2<T>& vector_p, T newAngle_p)
	{
		T vecLength = vectorLength(vector_p);
		vector_p.x = vecLength * Trig<T>::cos(newAngle_p);
		vector_p.y = vecLength * Trig<T>::sin(newAngle_p);
	}

	template <typename T>
	void rotateVectors(sf::Vector2<T>& vector_p, T angle_p)
	{
		T cos = Trig<T>::cos(angle_p);
		T sin = Trig<T>::sin(angle_p);
		vector_p = sf::Vector2<T>(cos * vector_p.x - sin * vector_p.y, sin * vector_p.x + cos * vector_p.y);
	}

	template <typename T>
	sf::Vector2<T> rotatedVector(const sf::Vector2<T>& vector_p, T angle_p)
	{
		sf::Vector2<T> copy_t = vector_p;
		rotateVectors(copy_t, angle_p);
		return copy_t;
	}

	template <typename T>
	sf::Vector2<T> perpendicularVector(const sf::Vector2<T>& vector_p)
	{
		return sf::Vector2<T>(-vector_p.y, vector_p.x);
	}

	// ---------------------------------------------------------------------------------------------------------------------------

	template <typename T>
	T signedAngle(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p)
	{
		assert(leftHandSide_p != sf::Vector2<T>() && rightHandSide_p != sf::Vector2<T>());
		return Trig<T>::arcTan2(crossProduct(leftHandSide_p, rightHandSide_p).z, dotProduct(leftHandSide_p, rightHandSide_p));
	}

	template <typename T>
	T dotProduct(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p)
	{
		return leftHandSide_p.x * rightHandSide_p.x + leftHandSide_p.y * rightHandSide_p.y;
	}

	template <typename T>
	sf::Vector2<T> cwiseProduct(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p)
	{
		return sf::Vector2<T>(leftHandSide_p.x * rightHandSide_p.x, leftHandSide_p.y * rightHandSide_p.y);
	}

	template <typename T>
	sf::Vector2<T> cwiseQuotient(const sf::Vector2<T>& leftHandSide_p, const sf::Vector2<T>& rightHandSide_p)
	{
		assert(rightHandSide_p.x != 0 && rightHandSide_p.y != 0);
		return sf::Vector2<T>(leftHandSide_p.x / rightHandSide_p.x, leftHandSide_p.y / rightHandSide_p.y);
	}

	template <typename T>
	sf::Vector2<T> projectedVector(const sf::Vector2<T>& vector_p, const sf::Vector2<T>& axis_p)
	{
		assert(axis_p != sf::Vector2<T>());
		return dotProduct(vector_p, axis_p) / squaredVectLength(axis_p) * axis_p;
	}

	int floatToIntRnding(float float_p)
	{
		return static_cast<int>(float_p + 0.5f);
	}

	sf::Vector2f toFloat(sf::Vector2u uInt_p)
	{
		return sf::Vector2f(uInt_p);
	}

	sf::Vector2f toFloat(sf::Vector2i int_p)
	{
		return sf::Vector2f(int_p);
	}

	sf::Vector2u toUnsignedInt(sf::Vector2f float_p)
	{
		return sf::Vector2u(float_p);
	}

	sf::Vector2u toUnsignedInt(sf::Vector2i int_p)
	{
		return sf::Vector2u(int_p);
	}

	sf::Vector2i toInt(sf::Vector2f float_p)
	{
		return sf::Vector2i(float_p);
	}

	sf::Vector2i toInt(sf::Vector2u uInt_p)
	{
		return sf::Vector2i(uInt_p);
	}

	sf::Vector2f topLeftRect(sf::FloatRect rect_p)
	{
		return sf::Vector2f(rect_p.left, rect_p.top);
	}

	sf::Vector2f topRightRect(sf::FloatRect rect_p)
	{
		return sf::Vector2f(rect_p.left + rect_p.width, rect_p.top);
	}

	sf::Vector2f btmLeftRect(sf::FloatRect rect_p)
	{
		return sf::Vector2f(rect_p.left, rect_p.top + rect_p.height);
	}

	sf::Vector2f btmRightRect(sf::FloatRect rect_p)
	{
		return sf::Vector2f(rect_p.left + rect_p.width, rect_p.top + rect_p.height);
	}

	sf::Vector2f toRectDimFloat(sf::FloatRect rect_p)
	{
		return sf::Vector2f(rect_p.width, rect_p.height);
	}

	sf::Vector2i toRectDimInt(sf::FloatRect rect_p)
	{
		return toInt(toRectDimFloat(rect_p));
	}

	sf::Vector2f topLeftRect(sf::IntRect rect_p)
	{
		return sf::Vector2f(static_cast<float>(rect_p.left), static_cast<float>(rect_p.top));
	}

	sf::Vector2f topRightRect(sf::IntRect rect_p)
	{
		return sf::Vector2f(static_cast<float>(rect_p.left + rect_p.width), static_cast<float>(rect_p.top));
	}

	sf::Vector2f btmLeftRect(sf::IntRect rect_p)
	{
		return sf::Vector2f(static_cast<float>(rect_p.left), static_cast<float>(rect_p.top + rect_p.height));
	}

	sf::Vector2f btmRightRect(sf::IntRect rect_p)
	{
		return sf::Vector2f(static_cast<float>(rect_p.left + rect_p.width), static_cast<float>(rect_p.top + rect_p.height));
	}

	sf::Vector2f toRectDimFloat(sf::IntRect rect_p)
	{
		return sf::Vector2f(static_cast<float>(rect_p.width), static_cast<float>(rect_p.height));
	}

	sf::Vector2i toRectDimInt(sf::IntRect rect_p)
	{
		return toInt(toRectDimFloat(rect_p));
	}

	sf::IntRect  toInt(sf::FloatRect rect_p)
	{
		sf::IntRect rect_t;
		rect_t.left = floatToIntRnding(rect_p.left);
		rect_t.top = floatToIntRnding(rect_p.top);
		rect_t.width = floatToIntRnding(rect_p.width);
		rect_t.height = floatToIntRnding(rect_p.height);
		return rect_t;
	}

	sf::FloatRect toFloat(sf::IntRect rect_p)
	{
		sf::FloatRect rect_t;
		rect_t.left = static_cast<float>(rect_p.left);
		rect_t.top = static_cast<float>(rect_p.top);
		rect_t.width = static_cast<float>(rect_p.width);
		rect_t.height = static_cast<float>(rect_p.height);
		return rect_t;
	}

	sf::IntRect fromRectDimInt(sf::Vector2f dimension_p)
	{
		return sf::IntRect(sf::Vector2i(0, 0), toInt(dimension_p));
	}

	sf::IntRect fromRectDimInt(sf::Vector2i dimension_p)
	{
		return sf::IntRect(sf::Vector2i(0, 0), dimension_p);
	}

	sf::FloatRect fromRectDimFloat(sf::Vector2f dimension_p)
	{
		return sf::FloatRect(sf::Vector2f(0, 0), dimension_p);
	}

	sf::FloatRect fromRectDimFloat(sf::Vector2i dimension_p)
	{
		return sf::FloatRect(sf::Vector2f(0, 0), toFloat(dimension_p));
	}

}