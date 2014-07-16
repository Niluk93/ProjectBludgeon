#include <Sage\SpineSprite.h>

using namespace sage;

SpineSprite::SpineSprite(string _FilePath, sf::Vector2f _startPosition, float _startRotation , float _startScale)
{
	string atlasPath = _FilePath;
	atlasPath.append(".atlas");
	m_Atlas = Atlas_createFromFile(atlasPath.c_str(), 0);

	SkeletonJson* skeletonJson = SkeletonJson_create(m_Atlas);
	skeletonJson->scale = 1.0f;

	string jsonPath = _FilePath;
	jsonPath.append(".json");
	m_SkeletonData = SkeletonJson_readSkeletonDataFile(skeletonJson, jsonPath.c_str());
	if (!m_SkeletonData)
	{
		cout << "Error Loading Skeleton Data : " << skeletonJson->error << endl;
		exit(0);
	}

	SkeletonJson_dispose(skeletonJson);
	m_SkeletonBounds = SkeletonBounds_create();

	m_AnimationStateData = AnimationStateData_create(m_SkeletonData);
	m_AnimationCount = m_SkeletonData->animationCount;
	for (int iAnimation = 0; iAnimation < m_AnimationCount; ++iAnimation)
	{
		m_AnimationList.push_back(m_SkeletonData->animations[iAnimation]);
	}

	m_SkeletonDrawable = new SkeletonDrawable(m_SkeletonData, m_AnimationStateData);
	m_SkeletonDrawable->timeScale = 1.0f;

	m_Skeleton = m_SkeletonDrawable->skeleton;
	m_Skeleton->flipX = false;
	m_Skeleton->flipY = false;

	m_SkinCount = m_SkeletonData->skinCount;
	for (int iSkin = 0; iSkin < m_SkinCount; iSkin++)
	{
		m_SkinList.push_back(m_SkeletonData->skins[iSkin]);
	}

	for (int iBone = 0; iBone < m_Skeleton->boneCount; ++iBone)
	{
		m_Skeleton->bones[iBone]->data->inheritRotation = true;
		m_Skeleton->bones[iBone]->data->inheritScale = true;
	}
	m_Scale = sf::Vector2f(_startScale, _startScale);
	m_Rotation = _startRotation;

	m_Skeleton->root->data->scaleX = m_Scale.x;
	m_Skeleton->root->data->scaleY = m_Scale.y;

	m_Skeleton->root->data->rotation = m_Rotation;

	m_Position = _startPosition;
	m_Skeleton->root->data->x = m_Position.x;
	m_Skeleton->root->data->y = m_Position.y;
	Skeleton_setToSetupPose(m_Skeleton);
	Skeleton_updateWorldTransform(m_Skeleton);

	m_Color = sf::Color::White;
	m_Skeleton->r = ((float)m_Color.r) / 255.0f;
	m_Skeleton->g = ((float)m_Color.g) / 255.0f;
	m_Skeleton->b = ((float)m_Color.b) / 255.0f;
	m_Skeleton->a = ((float)m_Color.a) / 255.0f;

	m_AnimationStateCallback = animationCallback;
	m_SkeletonDrawable->state->listener = m_AnimationStateCallback;
}

SpineSprite::~SpineSprite()
{
	SkeletonData_dispose(m_SkeletonData);
	SkeletonBounds_dispose(m_SkeletonBounds);
	Atlas_dispose(m_Atlas);
}

void SpineSprite::draw(sf::RenderWindow* _RenderWindow, float _DeltaTime)
{
	SkeletonBounds_update(m_SkeletonBounds, m_Skeleton, true);
	m_SkeletonDrawable->update(_DeltaTime);
	updateTextureRect();

	m_SkeletonDrawable->draw(*_RenderWindow, sf::RenderStates::Default);
	
#ifdef DEBUG
	sf::RectangleShape collisionRect;
	collisionRect.setSize(sf::Vector2f(m_TextureRectangle.width, m_TextureRectangle.height));
	collisionRect.setPosition(m_TextureRectangle.left, m_TextureRectangle.top);
	collisionRect.setFillColor(sf::Color::Transparent);
	collisionRect.setOutlineThickness(3);
	_RenderWindow->draw(collisionRect);
#endif
}

#pragma region REGION_TRANSFORMS
void SpineSprite::setPosition(float _PosX, float _PosY)
{
	m_Position.x = _PosX;
	m_Position.y = _PosY;

	m_Skeleton->root->data->x = m_Position.x;
	m_Skeleton->root->data->y = m_Position.y;
	Skeleton_setToSetupPose(m_Skeleton);
	Skeleton_updateWorldTransform(m_Skeleton);
}

void SpineSprite::setPosition(sf::Vector2f _Pos)
{
	setPosition(_Pos.x, _Pos.y);
}


void SpineSprite::setScale(float _ScaleX, float _ScaleY)
{
	m_Scale.x = _ScaleX;
	m_Scale.y = _ScaleY;

	m_Skeleton->root->data->scaleX = m_Scale.x;
	m_Skeleton->root->data->scaleY = m_Scale.y;

	Skeleton_setToSetupPose(m_Skeleton);
}

void SpineSprite::setScale(float _Scale)
{
	sf::Sprite sprite;
	setScale(_Scale, _Scale);
}

void SpineSprite::setScale(sf::Vector2f _Scale)
{
	setScale(_Scale.x, _Scale.y);
}

void SpineSprite::setRotation(float _Rotation)
{
	m_Rotation = _Rotation;

	m_Skeleton->root->data->rotation = m_Rotation;

	Skeleton_setToSetupPose(m_Skeleton);
}

sf::Vector2f SpineSprite::getPosition()
{
	return m_Position;
}

sf::Vector2f SpineSprite::getScale()
{
	return m_Scale;
}

float SpineSprite::getRotation()
{
	return m_Rotation;
}

void SpineSprite::move(float _OffsetX, float _OffsetY)
{
	m_Position.x += _OffsetX;
	m_Position.y += _OffsetY;

	setPosition(m_Position);
}

void SpineSprite::move(sf::Vector2f _Offset)
{
	m_Position.x += _Offset.x;
	m_Position.y += _Offset.y;

	setPosition(m_Position);
}

void SpineSprite::rotate(float _Angle)
{
	m_Rotation += _Angle;

	setRotation(m_Rotation);
}

void SpineSprite::scale(float _Factor)
{
	m_Scale.x *= _Factor;
	m_Scale.y *= _Factor;

	setScale(m_Scale);
}

void SpineSprite::scale(float _FactorX, float _FactorY)
{
	m_Scale.x *= _FactorX;
	m_Scale.y *= _FactorY;

	setScale(m_Scale);
}

void SpineSprite::scale(sf::Vector2f _Factor)
{
	m_Scale.x *= _Factor.x;
	m_Scale.y *= _Factor.y;

	setScale(m_Scale);
}
#pragma endregion REGION_TRANSFORMS


#pragma region REGION_ANIMATION
void SpineSprite::setAnimation(spAnimation* _Animation, bool loop)
{
	AnimationState_setAnimation(m_SkeletonDrawable->state, 0, _Animation, loop);
}

void SpineSprite::setAnimation(string _AnimationName, bool loop)
{
	for (vector<spAnimation*>::iterator itrAnimation = m_AnimationList.begin(); itrAnimation != m_AnimationList.end(); itrAnimation++)
	{
		if ((*itrAnimation)->name == _AnimationName)
		{
			AnimationState_setAnimation(m_SkeletonDrawable->state, 0, *itrAnimation, loop);
		}
	}
}
#pragma endregion REGION_ANIMATION

#pragma region REGION_SKINS
void SpineSprite::setSkin(spSkin* _Skin)
{
	Skeleton_setSkin(m_Skeleton, _Skin);
	Skeleton_setSlotsToSetupPose(m_Skeleton);
}

void SpineSprite::setSkin(string _SkinName)
{
	for (vector<spSkin*>::iterator itrSkin = m_SkinList.begin(); itrSkin != m_SkinList.end(); itrSkin++)
	{
		if ((*itrSkin)->name == _SkinName)
		{
			setSkin(*itrSkin);
		}
	}
}

spSkin SpineSprite::getSkin()
{
	return *(m_Skeleton->skin);
}
#pragma endregion REGION_SKINS

#pragma region REGION_ATTACHMENTS
void SpineSprite::setAttachment(string _SlotName, string _AttachmentName)
{
	Skeleton_setAttachment(m_Skeleton, _SlotName.c_str(), _AttachmentName.c_str());
}
#pragma endregion REGION_ATTACHMENTS

#pragma region REGION_MISCELLENOUS
void SpineSprite::setColor(int r, int g, int b, int a)
{
	m_Color = sf::Color(r, g, b, a);

	m_Skeleton->r = ((float)m_Color.r) / 255;
	m_Skeleton->g = ((float)m_Color.g) / 255;
	m_Skeleton->b = ((float)m_Color.b) / 255;
	m_Skeleton->a = ((float)m_Color.a) / 255;
}

void SpineSprite::setColor(sf::Color _Color)
{
	setColor(_Color.r, _Color.g, _Color.b, _Color.a);
}

void SpineSprite::updateTextureRect()
{
	m_TextureRectangle = m_SkeletonDrawable->vertexArray->getBounds();
}

sf::Color SpineSprite::getColor()
{
	return m_Color;
}

sf::FloatRect SpineSprite::getTextureRect()
{
	return m_TextureRectangle;
}

void SpineSprite::setAnimationCallback(void(*_Callback)(AnimationState*, int, EventType, Event*, int))
{
	m_AnimationStateCallback = _Callback;

	m_SkeletonDrawable->state->listener = m_AnimationStateCallback;
}
#pragma endregion REGION_MISCELLENOUS

void animationCallback(AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount)
{
	TrackEntry* entry = AnimationState_getCurrent(state, trackIndex);
	const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;

	switch (type) {
	case ANIMATION_START:
		//printf("%d default start: %s\n", trackIndex, animationName);
		break;
	case ANIMATION_END:
		//printf("%d default end: %s\n", trackIndex, animationName);
		break;
	case ANIMATION_COMPLETE:
		//printf("%d default complete: %s, %d\n", trackIndex, animationName, loopCount);
		break;
	case ANIMATION_EVENT:
		//printf("%d default event: %s, %s: %d, %f, %s\n", trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
		//event->stringValue);
		break;
	}
	fflush(stdout);
}