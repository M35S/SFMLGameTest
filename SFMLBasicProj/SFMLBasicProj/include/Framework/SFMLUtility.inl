namespace sf	
{
	template <typename Resource, typename Identifier>
	void ResourceHelper<Resource, Identifier>::load(Identifier id, const std::string& fileName)
	{
		// Create and load resource
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(fileName))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);

		// If loading successful, insert resource to map
		this->insertResource(id, std::move(resource));
	}

	template <typename Resource, typename Identifier>
	template <typename Parameter>
	void ResourceHelper<Resource, Identifier>::load(Identifier id, const std::string& fileName, const Parameter& secParam)
	{
		// Create and load resource
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(fileName, secParam))
			throw std::runtime_error("Resource::load - Failed to load " + fileName);

		// If loading successful, insert resource to map
		this->insertResource(id, std::move(resource));
	}

	template <typename Resource, typename Identifier>
	Resource& ResourceHelper<Resource, Identifier>::get(Identifier id)
	{
		auto found = this->c_resMap.find(id);
		return *found->second;
	}

	template <typename Resource, typename Identifier>
	const Resource& ResourceHelper<Resource, Identifier>::get(Identifier id) const
	{
		auto found = this->c_resMap.find(id);
		return found->second;
	}

	template <typename Resource, typename Identifier>
	void ResourceHelper<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
	{
		// Insert and check success
		auto inserted = this->c_resMap.insert(std::make_pair(id, std::move(resource)));
	}

	// ----------------- Utility Functions --------------------------------------------
	inline std::string getContextInfo(sf::RenderWindow& window)
	{
		// Get the OpenGL Context and the Screen Resolution
		sf::ContextSettings toggleSet = window.getSettings();
		sf::Vector2u screenRes = window.getSize();

		std::ostringstream ss;
		ss << "***************OUTPUT SETTINGS*****************************************" << std::endl;
		ss << " Depth Buffer (Bits):    " << toggleSet.depthBits << std::endl;
		ss << " Stencil Buffer (Bits):  " << toggleSet.stencilBits << std::endl;
		ss << " MSAA Level:             " << toggleSet.antialiasingLevel << std::endl;
		ss << " Open GL Version:        " << toggleSet.majorVersion << "." << toggleSet.minorVersion << std::endl;
		ss << " Resolution:             " << screenRes.x << ", " << screenRes.y << std::endl;
		ss << "***********************************************************************" << std::endl;
		return ss.str();
	}

	inline std::string getSpriteState(sf::Sprite& sprite)
	{
		Vector2f pos = sprite.getPosition();
		Vector2u size = sprite.getTexture()->getSize();
		Vector2f scale = sprite.getScale();
		float length = sqrtf(pos.x * pos.x + pos.y * pos.y);
		float angle = length > 0 ? atan2f(pos.y, pos.x) : 0.0f;

		Vector2f dir;
		if (length > 0)
			dir = pos / length;

		String info;
		info += "Current Position:  " + std::to_string(pos.x) + " : " + std::to_string(pos.y) + "\n";
		info += "Magnitude/Length:  " + std::to_string(length) + "\n";
		info += "Polar Angle:       " + std::to_string(angle) + "\n";
		info += "Vector Direction:  " + std::to_string(dir.x) + " : " + std::to_string(dir.y) + "\n";
		info += "Sprite Dimensions: " + std::to_string(size.x) + " : " + std::to_string(size.y) + "\n";
		info += "Sprite Rotation:   " + std::to_string(sprite.getRotation()) + "\n";
		std::string scaletext(std::to_string(scale.x));
		scaletext += " : ";
		scaletext += std::to_string(scale.y) + "\n";
		info += "Sprite Scale:      " + scaletext;
		return info;
	}

	inline std::string getFPS(sf::Time tpf)
	{
		return std::to_string(1.0f / tpf.asSeconds());
	}

	inline void setOriginCentre(sf::Sprite& sprite)
	{
		sf::Vector2i frame;
		frame.x = static_cast<int>(sprite.getLocalBounds().width);
		frame.y = static_cast<int>(sprite.getLocalBounds().height);
		sf::Vector2f origin(frame);
		origin *= 0.5f;
		sprite.setOrigin(origin);
	}

	inline void setOriginCentre(sf::AnimSprite& sprite)
	{
		sf::Vector2i frame;
		frame.x = static_cast<int>(sprite.getLocalBounds().width);
		frame.y = static_cast<int>(sprite.getLocalBounds().height);
		sf::Vector2f origin(frame);
		origin *= 0.5f;
		sprite.setOrigin(origin);
	}
}