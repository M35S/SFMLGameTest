#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include <sstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "AnimSprite.h"

namespace sf
{
	// ---------------------Utility Resource Holder Class----------------------------
	template<typename Resource, typename Identifier>
	class ResourceHelper
	{
	public:
		/////////////////////////////////
		// Function Members
		void load(Identifier id, const std::string& fileName);
		template <typename Parameter>
		void load(Identifier id, const std::string& fileName, const Parameter& secParam);

		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;
		
	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource);

		/////////////////////////////// 
		// Data Members
		std::map<Identifier, std::unique_ptr<Resource>> c_resMap;
	};

	/////////////////////////
	// Global functions

	//-------------------String Helper Methods
	inline std::string getContextInfo(sf::RenderWindow& window);
	inline std::string getSpriteState(sf::Sprite& sprite);
	inline std::string getFPS(sf::Time tpf);
}

#include "SFMLUtility.inl"