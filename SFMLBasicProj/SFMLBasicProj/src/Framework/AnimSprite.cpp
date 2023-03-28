#include "AnimSprite.h"
#include <iostream>

/*
==================================================
File tite:		Sprite Animation management
File Name:		AnimSprite.cpp
Purpose:		Setup sprite animations.
==================================================
*/

namespace sf
{
	/*
	/////////////////////////////////////////////////////////
	Name:		Animation Sequence CONSTRUCTOR
	Purpose:	Construct the anim seq object.
	*/
	AnimSeq::AnimSeq() : spriteTexture_m(nullptr)
	{

	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Add Frame
	Purpose:	Add an animation rectangle to the frame list container.

	Arguments:	sf::IntRect rect_p
				Stores left, top, width & height rectangle parameters.
	*/
	void AnimSeq::addFrame(sf::IntRect rect_p)
	{
		this->listFrames_m.push_back(rect_p);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Sprite Sheet
	Purpose:	Set the sprite sheet texture used in the animation.

	Arguments:	sf::Texture& sprSheet_p
				Stores the texture's data such as it's size.
	*/
	void AnimSeq::setSpriteSheet(const sf::Texture& sprSheet_p)
	{
		this->spriteTexture_m = &sprSheet_p;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Sprite Sheet
	Purpose:	Get a pointer to the sprite sheet texture that's
				used for the animation.
	*/
	const sf::Texture* AnimSeq::getSpriteSheet() const
	{
		return this->spriteTexture_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Frame Count
	Purpose:	Get the number of frames in the animation sequence.
	*/
	int AnimSeq::getFrameCount() const
	{
		return this->listFrames_m.size();
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Frame
	Purpose:	Get the rectangle representing the given frame's
				location in the sprite sheet.

	Arguments:	int frameNum_p
				Used for indexing the vector container.
	*/
	const sf::IntRect& AnimSeq::getFrame(int frameNum_p) const
	{
		return this->listFrames_m[frameNum_p];
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Animation Sprite CONSTRUCTOR
	Purpose:	Construct the anim sprite object.

	Arguments:	sf::Time duration_p
				How long each frame lasts for.

				bool paused_p
				Paused at the current animation frame.

				bool looping_p
				Whether to repeat all animation frames or not.
	*/
	AnimSprite::AnimSprite(sf::Time duration_p, bool paused_p, bool looping_p) :
		animSeq_m(),
		timeDuration_m(duration_p),
		frameNum_m(0),
		paused_m(paused_p),
		looping_m(looping_p),
		spriteTexture_m(nullptr)
	{

	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Create
	Purpose:	Set the duration, paused state and looping
				state of the sprite.

	Arguments:	sf::Time duration_p
				Duration of each animation frame.

				bool paused_p
				To pause at a frame or not.

				bool looping_p
				Whether to repeat all frames or not.
	*/
	void AnimSprite::create(sf::Time duration_p, bool paused_p, bool looping_p)
	{
		this->timeDuration_m = duration_p;
		this->paused_m = paused_p;
		this->looping_m = looping_p;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Looping
	Purpose:	Set the state of the sprite to looping the animation.

	Arguments:	bool looping_p
				Repeat all frames.
	
	*/
	void AnimSprite::setLooping(bool looping_p)
	{
		this->looping_m = looping_p;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Color
	Purpose:	Set the colour of the sprite

	Arguments:	sf::Color colour_p
				Which colour to set all verts.
	*/
	void AnimSprite::setColor(sf::Color colour_p)
	{
		//Set the Blend Colour for all four corners.
		this->vertices_m[0].color = colour_p;
		this->vertices_m[1].color = colour_p;
		this->vertices_m[2].color = colour_p;
		this->vertices_m[3].color = colour_p;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Frame
	Purpose:	Set the animation to the given frame.

	Arguments:	int frameNum_p
				The current animated frame.

				bool resetTime_p
				Dictates whether to set current anim frame to zero or not.
	*/
	void AnimSprite::setFrame(int frameNum_p, bool resetTime_p)
	{
		if (this->animSeq_m.getSpriteSheet() != nullptr)
		{
			//calculate new vertex positions and texture coordiantes
			sf::IntRect rect_t = this->animSeq_m.getFrame(frameNum_p);

			//Set the Four Corners of the Sprite
			this->vertices_m[0].position = sf::Vector2f(0.f, 0.f);
			this->vertices_m[1].position = sf::Vector2f(0.f, static_cast<float>(rect_t.height));
			this->vertices_m[2].position = sf::Vector2f(static_cast<float>(rect_t.width), static_cast<float>(rect_t.height));
			this->vertices_m[3].position = sf::Vector2f(static_cast<float>(rect_t.width), 0.f);

			//Set the Coordinates of the Sprite to those of the current frame 
			float left_t = static_cast<float>(rect_t.left) + 0.0001f;
			float right_t = left_t + static_cast<float>(rect_t.width);
			float top_t = static_cast<float>(rect_t.top);
			float tbottom = top_t + static_cast<float>(rect_t.height);
			this->vertices_m[0].texCoords = sf::Vector2f(left_t, top_t);
			this->vertices_m[1].texCoords = sf::Vector2f(left_t, tbottom);
			this->vertices_m[2].texCoords = sf::Vector2f(right_t, tbottom);
			this->vertices_m[3].texCoords = sf::Vector2f(right_t, top_t);
		}

		if (resetTime_p)
			this->currAnimTime_m = sf::Time::Zero;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Animation
	Purpose:	Set the animation sequence to use with this sprite.

	Arguments:	AnimSeq anim_p
				Data structure for holding sprite animated frames.
	*/
	void AnimSprite::setAnimation(AnimSeq anim_p)
	{
		//Set the Animation Sequence
		this->animSeq_m = anim_p;
		this->spriteTexture_m = this->animSeq_m.getSpriteSheet();
		this->frameNum_m = 0;
		this->setFrame(this->frameNum_m);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Frame Time
	Purpose:	Set the duration that each frame should run for.

	Arguments:	sf::Time duration_p
				Duration of each frame.
	*/
	void AnimSprite::setFrameTime(sf::Time duration_p)
	{
		this->timeDuration_m = duration_p;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Animation
	Purpose:	Get the animation sequence used with this sprite.
	*/
	AnimSeq AnimSprite::getAnimation()
	{
		return this->animSeq_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Local Bounds
	Purpose:	Get the local bounds of the current frame of this sprite.
	*/
	sf::FloatRect AnimSprite::getLocalBounds()
	{
		sf::IntRect rect_t = this->animSeq_m.getFrame(this->frameNum_m);

		float width_t = static_cast<float>(std::abs(rect_t.width));
		float height_t = static_cast<float>(std::abs(rect_t.height));

		return sf::FloatRect(0.f, 0.f, width_t, height_t);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Global Bounds
	Purpose:	Get the transformed bounds of the current frame of this sprite.
	*/
	sf::FloatRect AnimSprite::getGlobalBounds()
	{
		return this->getTransform().transformRect(this->getLocalBounds());
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Frame Time
	Purpose:	Get the duration each frame runs for.
	*/
	sf::Time AnimSprite::getFrameTime()
	{
		return this->timeDuration_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Is Looping
	Purpose:	Return true if this animation is looping.
	*/
	bool AnimSprite::isLooping()
	{
		return this->looping_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Is Playing
	Purpose:	Return true if this animation is playing.
	*/
	bool AnimSprite::isPlaying()
	{
		return !this->paused_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Play
	Purpose:	Start the animation.
	*/
	void AnimSprite::play()
	{
		this->paused_m = false;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Play New 
	Purpose:	Replace the current animation with the given animation and start it.

	Arguments:	AnimSeq anim_p
				Data structure of sprite frames to set  & play animation.
	*/
	void AnimSprite::playNew(AnimSeq anim_p)
	{
		this->setAnimation(anim_p);
		this->play();
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Pause
	Purpose:	Pause the animation.
	*/
	void AnimSprite::pause()
	{
		this->paused_m = true;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Stop
	Purpose:	Stop this animation playing and reset it back to the first frame.
	*/
	void AnimSprite::stop()
	{
		this->paused_m = true;
		this->frameNum_m = 0;
		this->setFrame(this->frameNum_m);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Frame Number
	Purpose:	Get the frame number.
	*/
	int AnimSprite::getFrameNo()
	{
		return this->frameNum_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Get Current Frame Time
	Purpose:	Get the current frame time.
	*/
	sf::Time AnimSprite::getCurrentFrameTime()
	{
		return this->currAnimTime_m;
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Set Frame
	Purpose:	Set the frame time and the frame number.

	Arguments:	sf::Time time_p
				Used to set current animation time.

				int frameNum_p
				Dictates which frame to set.
	*/
	void AnimSprite::setFrame(sf::Time time_p, int frameNum_p)
	{
		this->frameNum_m = frameNum_p;
		this->currAnimTime_m = time_p;
		this->setFrame(this->frameNum_m, false);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Increment Frame
	Purpose:	Increment the animation frame.

	Arguments:	sf::Time time_p
				Set the frame's time.

				bool loop_p
				Dictates which frame to set.
	*/
	void AnimSprite::incrementFrame(sf::Time time_p, bool loop_p)
	{
		int frameCount_t = this->animSeq_m.getFrameCount();
		int frameNum_t = this->frameNum_m;
		frameNum_t += 1;
		if (loop_p)
			frameNum_t = frameNum_t % frameCount_t;
		else
			frameNum_t = std::min<int>(frameNum_t, frameCount_t - 1);
		this->setFrame(time_p, frameNum_t);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Decrement Frame
	Purpose:	Decrement the animation frame.

	Arguments:	sf::Time time_p
				Set the frame's time.

				bool loop_p
				Dictates which frame to set.
	*/
	void AnimSprite::decrementFrame(sf::Time time_p, bool loop_p)
	{
		int frameCount_t = this->animSeq_m.getFrameCount();
		int frameNum_t = this->frameNum_m;
		frameNum_t -= 1;
		if (loop_p)
			frameNum_t = frameNum_t % frameCount_t;
		else
			frameNum_t = std::max<int>(frameNum_t, 0);
		this->setFrame(time_p, frameNum_t);
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Update
	Purpose:	Update the animated sprite.

	Arguments:	sf::Time tpf_p
				Used for setting delta time.
	*/
	void AnimSprite::update(sf::Time tpf_p)
	{
		// if not paused and we have a valid animation
		if (!this->paused_m && this->animSeq_m.getFrameCount() != 0)
		{
			// add delta time
			this->currAnimTime_m += tpf_p;

			// if current time is bigger then the frame time advance one frame
			if (this->currAnimTime_m >= this->timeDuration_m)
			{
				// reset time, but keep the remainder
				this->currAnimTime_m = sf::microseconds(this->currAnimTime_m.asMicroseconds() % this->timeDuration_m.asMicroseconds());

				// get next Frame index
				if (this->frameNum_m + 1 < this->animSeq_m.getFrameCount())
					this->frameNum_m++;
				else
				{
					// animation has ended
					this->frameNum_m = 0; // reset to start

					//If we are not looping and at the end then pause the animation
					if (!this->looping_m)
					{
						this->paused_m = true;
					}
				}

				// set the current frame, not reseting the time
				this->setFrame(this->frameNum_m, false);
			}
		}
	}

	/*
	/////////////////////////////////////////////////////////
	Name:		Draw
	Purpose:	Draw the animated sprite.

	Arguments:	sf::RenderTarget& target_p
				Data structure that represent's the sprite to be drawn.

				sf::RenderStates states_p
				Data structure that represent's the sprite's transformation & texture details.
	*/
	void AnimSprite::draw(sf::RenderTarget& target_p, sf::RenderStates states_p) const
	{
		if (this->animSeq_m.getFrameCount() != 0 && this->spriteTexture_m != nullptr)
		{
			//Set the States to the Current Transform of the Sprite (Rotation,Translation,Scale - World Matrix)
			states_p.transform *= this->getTransform();
			//Set the Texture to use the Sprite Sheet
			states_p.texture = this->spriteTexture_m;
			//Draw the Quadrilateral representing the sprite.
			target_p.draw(this->vertices_m, 4, sf::Quads, states_p);
		}
	}
}