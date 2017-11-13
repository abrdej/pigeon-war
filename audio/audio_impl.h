#ifndef AUDIO_IMPL_H
#define AUDIO_IMPL_H

#include <SFML/Audio.hpp>

namespace audio
{
	void shoot_sound()
	{
		static sf::SoundBuffer buffer;
		buffer.loadFromFile("gunshot.wav");
		static sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
	}

}

#endif