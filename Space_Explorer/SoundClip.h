#ifndef SOUNDCLIP_H
#define SOUNDCCLIP_H

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

//sound clip class, inherits from Sound (allows audio clips & buffer to be stored as contained object)
class SoundClip :
    public sf::Sound
{
private:
    //stores sound buffer (like a texture but for audio)
    sf::SoundBuffer m_buffer;

public:
    //default constructor
    SoundClip();
    //constructor that takes audio clip name as param (used to load soundBuffer)
    SoundClip(const std::string & audioFileName);

    //desctructor
    ~SoundClip();
};

#endif //SOUNDCLUP_H