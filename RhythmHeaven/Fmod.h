#pragma once
#include "inc/fmod.hpp"
#include <iostream>

using namespace FMOD;

namespace sound
{
	void SoundSetUp();
	void Playsound(int soundNum, Channel*& gChannel);
	void Stopsound(Channel*& gChannel);
	void Releasesound();
	Channel*& GetChannel(int num);

	unsigned int GetPlayPosition(Channel*& gChannel);
}