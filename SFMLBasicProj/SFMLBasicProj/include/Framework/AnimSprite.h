#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

namespace sf
{
	class AnimSeq
	{
	public:
		///////////////////////
		// Constructor 
		AnimSeq(void);

		//////////////////////
		// Destructor
		~AnimSeq(void){};

	public:
		//////////////////////
		// Function Members
		const sf::Texture*		getSpriteSheet() const;		
		int						getFrameCount() const;		
		const sf::IntRect&		getFrame(int num_p) const;	

		void					addFrame(sf::IntRect rect_p);	
		void					setSpriteSheet(const sf::Texture& spriteSheet_p);

	private:
		///////////////////////
		// Data Members
		std::vector<sf::IntRect>	listFrames_m;	
		const sf::Texture*			spriteTexture_m;
	};





	class AnimSprite : public sf::Drawable, public sf::Transformable
	{
	public:
		/////////////////////////
		// Constructor
		AnimSprite(sf::Time duration_p = sf::seconds(0.2f), bool paused_p = false, bool looping_p = true);	
		
		/////////////////////////
		// Destructor
		~AnimSprite(void){};		

	public:
		//////////////////////
		// Function Members
		void				update(sf::Time tpf_p);	
		void				play();					
		void				playNew(AnimSeq anim_p);
		void				pause();				
		void				stop();					
		void                create(sf::Time duration_p = sf::seconds(0.2f), bool paused_p = false, bool looping_p = true);

		//-----------GETTERS/SETTERS----------------------------------------
		AnimSeq  			getAnimation();		
		sf::FloatRect		getLocalBounds();	
		sf::FloatRect		getGlobalBounds();	
		bool				isLooping();		
		bool				isPlaying();		
		sf::Time			getFrameTime();		
		void				setFrame(int frameNum_p, bool resetTime_p = true);
		void                setAnimation(AnimSeq anim_p);						
		void				setFrameTime(sf::Time time_p);						
		void				setLooping(bool looping_p);							
		void				setColor(sf::Color colour_p);						

		int				    getFrameNo();			
		sf::Time            getCurrentFrameTime();	
		void				setFrame(sf::Time time_p, int frameNum_p);		
		void                incrementFrame(sf::Time time_p, bool loop_p = false);
		void                decrementFrame(sf::Time time_p, bool loop_p = false);

	private:
		//------------METHOD OVERRIDES---------------------------------------------------
		virtual void draw(sf::RenderTarget& target_p, sf::RenderStates states_p) const;

	private:
		//////////////////////
		// Data Members
		AnimSeq				animSeq_m;		
		sf::Time			timeDuration_m;	
		sf::Time			currAnimTime_m;	
		int			        frameNum_m;		
		bool				paused_m;		
		bool				looping_m;		
		const sf::Texture*	spriteTexture_m;
		sf::Vertex			vertices_m[4];	
	};
}

