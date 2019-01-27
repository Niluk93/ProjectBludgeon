# ProjectBludgeon

This project is intended to demonstrate the SAGE engine, written in collaboration by me (Nilesh Krishnan) and https://www.github.com/jvap (Jithin Peeter) in 2014.

The engine is built using SFML graphics library.

Currently, it supports the following features-

2D sprites-
    There are two kinds of 2D sprites-
    
    Sprite Sheets- This is self-explanatory, as this is the basic type of sprite animations that most developers are already comfortable with.
    Spine 2D - We also support 2D skeletal mesh animations made by using the Spine 2D software (http://esotericsoftware.com/).
    
    
Particle system-
    Particle system support is pretty basic. You can render up to 10,000 particles pretty smoothly. The system allows particles that burst or continuous emission types of particles.
    
    
Resource Manager-
    Custom implementation of a reference counted pointer that is used by all asset types internally. Automatically unloads memory when no references are left.
    
    
Scene Manager-
    Is responsible for loading and unloading a level. Levels must implement the IScene interface. This also hooks in to the resource manager to make sure any assets loaded as part of the level loading are accounted for.
    

Tiled Map Editor-
    2D maps made in the Tiled Map Editor can be loaded into the level.
