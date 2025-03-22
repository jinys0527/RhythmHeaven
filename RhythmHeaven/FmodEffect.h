#pragma once
#include <iostream>
#include "inc/fmod.hpp"

using namespace FMOD;

namespace fmodeffect
{
	void EffectSoundSetUp();
	void EffectPlaySound(int soundNum, Channel* gEffectChannel);
	void ReleaseEffectSound();
}