#include "SoundClip.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

//sound class, compacted (contains sound and sound buffer)
SoundClip::SoundClip()
	:sf::Sound()
{
	//attempts to load sound from default file
	if (m_buffer.loadFromFile("Death.wav"))
	{
		//error message oofie
	}

	//assigns buffer to Sound
	setBuffer(m_buffer);
}

SoundClip::SoundClip(const std::string & audioFileName)
	:sf::Sound( )
{
	//attempts to load sound from file specified
	if (m_buffer.loadFromFile(audioFileName))
	{
		//error message oofie
	}
	//assigns buffer to Sound
	setBuffer(m_buffer);

}

//destructor
SoundClip::~SoundClip()
{
}
