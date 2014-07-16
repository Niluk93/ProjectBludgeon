#ifndef PARTICLE_SYSTEMS_H
#define PARTICLE_SYSTEMS_H

#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <vector>
#include <thread>

using namespace std;

namespace sage
{
	class ParticleSystems : public sf::Drawable, public sf::Transformable
	{
	private:
		struct Particle
		{
			sf::Vector2f velocity;
			sf::Time lifetime;
		};

		vector<Particle> m_Particles;
		sf::VertexArray m_Vertices;
		sf::Time m_Lifetime;
		sf::Vector2f m_Emitter;

		bool m_Burst;
		void updateParticles(float deltaTime, float angle);
	
	public:
		ParticleSystems(unsigned int count);
		void setEmitter(sf::Vector2f position);
		sf::Vector2f getEmitter();
		void destroyEmitter();
		void setBurst(bool burst = true);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void resetParticle(size_t index, float angle = 0.0f);
		void burstParticle(size_t index);
		void update(float deltaTime, float angle = 0.0f);
	};
}

#endif