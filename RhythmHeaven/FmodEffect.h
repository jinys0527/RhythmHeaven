#pragma once
#include <iostream>
#include "inc/fmod.hpp"

using namespace FMOD;

namespace effectsound
{
	void EffectSoundSetUp();
	void EffectPlaySound(int soundNum, Channel* gEffectChannel);
	void ReleaseEffectSound();
}