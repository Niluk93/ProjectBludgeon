#include <iostream>
#include <string.h>
#include <spine/spine-sfml.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "GESpineSprite.h"
using namespace std;
using namespace spine;
#include <stdio.h>

void callback (AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount) {
	TrackEntry* entry = AnimationState_getCurrent(state, trackIndex);
	const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;

	switch (type) {
	case ANIMATION_START:
		printf("%d start: %s\n", trackIndex, animationName);
		break;
	case ANIMATION_END:
		printf("%d end: %s\n", trackIndex, animationName);
		break;
	case ANIMATION_COMPLETE:
		printf("%d complete: %s, %d\n", trackIndex, animationName, loopCount);
		break;
	case ANIMATION_EVENT:
		printf("%d event: %s, %s: %d, %f, %s\n", trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
				event->stringValue);
		break;
	}
	fflush(stdout);
}

void spineboy () {
	// Load atlas, skeleton, and animations.
	Atlas* atlas = Atlas_createFromFile("data/spineboy.atlas", 0);
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = 1.0f;
	SkeletonData *skeletonData = SkeletonJson_readSkeletonDataFile(json, "data/spineboy.json");
	if (!skeletonData) {
		printf("%s\n", json->error);
		exit(0);
	}
	SkeletonJson_dispose(json);
	SkeletonBounds* bounds = SkeletonBounds_create();

	// Configure mixing.
	AnimationStateData* stateData = AnimationStateData_create(skeletonData);
	AnimationStateData_setMixByName(stateData, "walk", "jump", 0.2f);
	AnimationStateData_setMixByName(stateData, "jump", "run", 0.2f);

	SkeletonDrawable* drawable = new SkeletonDrawable(skeletonData, stateData);
	drawable->timeScale = 1;

	Skeleton* skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	Skeleton_setToSetupPose(skeleton);
	skeleton->x = 320;
	skeleton->y = 460;
	Skeleton_updateWorldTransform(skeleton);
	Slot* headSlot = Skeleton_findSlot(skeleton, "head");

	drawable->state->listener = callback;
	if (false) {
		AnimationState_setAnimationByName(drawable->state, 0, "test", true);
	} else {
		AnimationState_setAnimationByName(drawable->state, 0, "walk", true);
		AnimationState_addAnimationByName(drawable->state, 0, "jump", false, 3);
		AnimationState_addAnimationByName(drawable->state, 0, "run", true, 0);
	}

	sf::RenderWindow window(sf::VideoMode(640, 480), "Spine SFML");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock deltaClock;
	while (window.isOpen()) {
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();

		float delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		SkeletonBounds_update(bounds, skeleton, true);
		sf::Vector2i position = sf::Mouse::getPosition(window);
		if (SkeletonBounds_containsPoint(bounds, position.x, position.y)) {
			headSlot->g = 0;
			headSlot->b = 0;
		} else {
			headSlot->g = 1;
			headSlot->b = 1;
		}

		drawable->update(delta);

		window.clear();
		window.draw(*drawable);
		window.display();
	}

	SkeletonData_dispose(skeletonData);
	SkeletonBounds_dispose(bounds);
	Atlas_dispose(atlas);
}

void goblins () {
	// Load atlas, skeleton, and animations.
	Atlas* atlas = Atlas_createFromFile("data/goblins-ffd.atlas", 0);
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = 1.4f;
	SkeletonData *skeletonData = SkeletonJson_readSkeletonDataFile(json, "data/goblins-ffd.json");
	if (!skeletonData) {
		printf("Error: %s\n", json->error);
		exit(0);
	}
	Animation* walkAnimation = SkeletonData_findAnimation(skeletonData, "walk");
	SkeletonJson_dispose(json);

	SkeletonDrawable* drawable = new SkeletonDrawable(skeletonData);
	drawable->timeScale = 1;

	Skeleton* skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	Skeleton_setSkinByName(skeleton, "goblin");
	Skeleton_setSlotsToSetupPose(skeleton);
	//Skeleton_setAttachment(skeleton, "left hand item", "dagger");

	skeleton->x = 320;
	skeleton->y = 590;
	Skeleton_updateWorldTransform(skeleton);

	AnimationState_setAnimation(drawable->state, 0, walkAnimation, true);

	sf::RenderWindow window(sf::VideoMode(640, 640), "Spine SFML");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock deltaClock;
	while (window.isOpen()) {
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();

		float delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		drawable->update(delta);

		window.clear();
		window.draw(*drawable);
		window.display();
	}

	SkeletonData_dispose(skeletonData);
	Atlas_dispose(atlas);
}

int main () {
	//spineboy();
	//goblins();
	GESpineSprite* testSpineBoy = new GESpineSprite("data/goblins-ffd", sf::Vector2f(300, 300), 0.0f, 1.0f);
	testSpineBoy->setAnimation("walk");
	testSpineBoy->setSkin("goblingirl");
	testSpineBoy->setAttachment("left hand item", "spear");
	testSpineBoy->setAnimationCallback(callback);
	//testSpineBoy->setColor(100, 100, 100, 255);
	sf::RenderWindow window(sf::VideoMode(800, 600), "Spine SFML");
	sf::View viewport;
	viewport.setCenter(sf::Vector2f(0,0));
	viewport.zoom(2);
	window.setView(viewport);
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock deltaClock;
	while (window.isOpen()) 
	{
		while (window.pollEvent(event))
		if (event.type == sf::Event::Closed) window.close();

		float delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		window.clear();
		testSpineBoy->draw(&window, delta);
		window.display();
	}
}
