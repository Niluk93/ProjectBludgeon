#include <Sage\ParticleSystems.h>

using namespace sage;
ParticleSystems::ParticleSystems(unsigned int count) : m_Particles(count), m_Vertices(sf::Quads, count*4), m_Lifetime(sf::seconds(1)), m_Emitter(0,0), m_Burst(false)
{

}

void ParticleSystems::setEmitter(sf::Vector2f position)
{
	m_Emitter = position;
}

sf::Vector2f ParticleSystems::getEmitter()
{
	return m_Emitter;
}

void ParticleSystems::destroyEmitter()
{
	m_Emitter = sf::Vector2f(10000,10000);
}

void ParticleSystems::setBurst(bool burst)
{
	if(!m_Burst)
	{
		m_Vertices.resize(m_Vertices.getVertexCount() + (1000 * 4));
		m_Particles.resize(m_Particles.size() + 1000);
	}

	m_Burst = burst;
}

void ParticleSystems::update(float deltaTime, float angle)
{
	thread updateThread(&ParticleSystems::updateParticles, this, deltaTime, angle);
	updateThread.join();
}

void ParticleSystems::updateParticles(float deltaTime, float angle)
{
	sf::Time elapsed = sf::seconds(deltaTime);
	for(size_t i=0; i < m_Particles.size(); i++)
	{
		sf::Vertex* quad = &m_Vertices[i*4];

		Particle& p = m_Particles[i];
		p.lifetime -= elapsed;

		if(p.lifetime <= sf::Time::Zero)
		{
			if(m_Burst)
			{
				burstParticle(i);
			}
			else
				resetParticle(i, angle);
		}

		quad[0].position.x += p.velocity.x * elapsed.asSeconds();
		quad[0].position.y += p.velocity.y * elapsed.asSeconds();
			
		quad[1].position.x = quad[0].position.x + p.velocity.x * elapsed.asSeconds() + rand()%4;
		quad[1].position.y = quad[0].position.y + p.velocity.y * elapsed.asSeconds();
			
		quad[2].position.x = quad[0].position.x + p.velocity.x * elapsed.asSeconds() + rand()%4;
		quad[2].position.y = quad[0].position.y + p.velocity.y * elapsed.asSeconds() + rand()%4;
			
		quad[3].position.x = quad[0].position.x + p.velocity.x * elapsed.asSeconds();
		quad[3].position.y = quad[0].position.y + p.velocity.y * elapsed.asSeconds() + rand()%4;

		float ratio = p.lifetime.asSeconds()/m_Lifetime.asSeconds();
		quad[0].color.r = static_cast<sf::Uint8>(ratio*255);
		quad[1].color.r = static_cast<sf::Uint8>(ratio*255);
		quad[2].color.r = static_cast<sf::Uint8>(ratio*255);
		quad[3].color.r = static_cast<sf::Uint8>(ratio*255);

		quad[0].color.b = 0;
		quad[1].color.b = 0;
		quad[2].color.b = 0;
		quad[3].color.b = 0;

		quad[0].color.g = 0;
		quad[1].color.g = 0;
		quad[2].color.g = 0;
		quad[3].color.g = 0;

		quad[0].color.a = static_cast<sf::Uint8>(ratio*255);
		quad[1].color.a = static_cast<sf::Uint8>(ratio*255);
		quad[2].color.a = static_cast<sf::Uint8>(ratio*255);
		quad[3].color.a = static_cast<sf::Uint8>(ratio*255);
	}
}

void ParticleSystems::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;

	target.draw(m_Vertices, states);
}

void ParticleSystems::resetParticle(size_t index, float angle)
{
	if(&m_Emitter != NULL)
	{
		sf::Vertex* quad = &m_Vertices[index*4];

		float particleAngle;
		if(rand()%2 == 0)
			particleAngle = angle + ((rand() % 10) * 3.14f/180.0f);
		else
			particleAngle = angle - ((rand() % 10) * 3.14f/180.0f);
		float speed = -((rand() % 50));

		m_Particles[index].velocity = sf::Vector2f(cos(particleAngle) * speed, sin(particleAngle) *speed);
		m_Particles[index].lifetime = sf::milliseconds((rand() % 2000));

		quad[0].position.x = m_Emitter.x;
		quad[0].position.y = m_Emitter.y;
		
		quad[1].position.x = m_Emitter.x + rand()%4;
		quad[1].position.y = m_Emitter.y;
		
		quad[2].position.x = m_Emitter.x + rand()%4;
		quad[2].position.y = m_Emitter.y + rand()%4;
		
		quad[3].position.x = m_Emitter.x;
		quad[3].position.y = m_Emitter.y + rand()%4;
	}
}

void ParticleSystems::burstParticle(size_t index)
{
	sf::Vertex* quad = &m_Vertices[index*4];

	float particleAngle = ((rand() % 360) * 3.14f/180.0f);
	float speed = -((rand() % 50));

	m_Particles[index].velocity = sf::Vector2f(cos(particleAngle) * speed, sin(particleAngle) *speed);
	m_Particles[index].lifetime = sf::milliseconds((rand() % 2000));

	quad[0].position.x = m_Emitter.x;
	quad[0].position.y = m_Emitter.y;
		
	quad[1].position.x = m_Emitter.x + rand()%4;
	quad[1].position.y = m_Emitter.y;
		
	quad[2].position.x = m_Emitter.x + rand()%4;
	quad[2].position.y = m_Emitter.y + rand()%4;
		
	quad[3].position.x = m_Emitter.x;
	quad[3].position.y = m_Emitter.y + rand()%4;
}