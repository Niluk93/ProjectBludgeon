#ifndef _GE_SPINE_SPRITE_
#define _GE_SPINE_SPRITE_
#define DEBUG
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "spine\spine-sfml.h"

using namespace std;
using namespace spine;

namespace sage
{
	class SpineSprite
	{
	private:
		Atlas*					m_Atlas;
		SkeletonData*			m_SkeletonData;
		SkeletonBounds*			m_SkeletonBounds;
		AnimationStateData*		m_AnimationStateData;
		SkeletonDrawable*		m_SkeletonDrawable;
		Skeleton*				m_Skeleton;
		vector<Skin*>			m_SkinList;
		int						m_SkinCount;
		vector<Animation*>		m_AnimationList;
		int						m_AnimationCount;
		sf::Vector2f			m_Position;
		sf::Vector2f			m_Scale;
		float					m_Rotation;
		sf::Color				m_Color;
		sf::FloatRect			m_TextureRectangle;

	private:
		void(*m_AnimationStateCallback)(AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount);

	public:
		/**Create a new Sprite Instance.
		*Requires Spine Atlas path with filename without extension.*/
		SpineSprite(string _FilePath, sf::Vector2f _startPosition = sf::Vector2f(0, 0), float _Rotation = 0.0f, float _startScale = 1.0f);
		~SpineSprite();
		void draw(sf::RenderWindow* _RenderWindow, float _DeltaTime);

		void setPosition(float _PosX, float _PosY);
		void setPosition(sf::Vector2f _Pos);
		void setScale(float _Scale);
		void setScale(float _ScaleX, float _ScaleY);
		void setScale(sf::Vector2f _Scale);
		void setRotation(float _Rotation);
		sf::Vector2f getPosition();
		sf::Vector2f getScale();
		float getRotation();
		void move(float _OffsetX, float _OffsetY);
		void move(sf::Vector2f _Offset);
		void rotate(float _Angle);
		void scale(float _Factor);
		void scale(float _FactorX, float _FactorY);
		void scale(sf::Vector2f _Factor);

		void setAnimation(spAnimation* _Animation, bool loop = true);
		void setAnimation(string _AnimationName, bool loop = true);
		spAnimation getAnimation();

		void setSkin(spSkin* _Skin);
		void setSkin(string _SkinName);
		spSkin getSkin();

		void setAttachment(string _SlotName, string _AttachmentName);

		void setColor(int r, int g, int b, int a);
		void setColor(sf::Color _Color);
		void updateTextureRect();
		sf::Color getColor();
		sf::FloatRect getTextureRect();

		void setAnimationCallback(void(*_Callback)(AnimationState*, int, EventType, Event*, int) = NULL);
	};
}

void animationCallback(AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount);

#endif