#pragma once
#include "inc/fmod.hpp"
#include <iostream>

using namespace FMOD;

namespace fmod
{
	void SoundSetUp();
	void Playsound(int soundNum);
	void Pausesound();
	void Releasesound();

	unsigned int GetPlayPosition();
	unsigned int GetLength(int num);
}