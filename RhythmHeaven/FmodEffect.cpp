#include "FmodEffect.h"
#include "inc/fmod_errors.h"

namespace effectsound
{
	enum EffectSounds
	{
		SD_AhPlayer,   // 코러스 Player 버전 : e0.mp3
		SD_Shout,      // 샤우트 : e1.mp3
		SD_EffectSize
	};

	System* gEffectSystem;
	Sound* gEffectSound[SD_EffectSize];
	FMOD_RESULT resultEffect;
	
	Channel* gEffectChannel0; //player		  //e0
	Channel* gEffectChannel1; //player(shout) //e1

	Channel*& GetChannel(int num)
	{
		switch (num)
		{
		case 0:
			return gEffectChannel0;
		case 1:
			return gEffectChannel1;
		}
	}

	void EffectSoundSetUp()
	{
		resultEffect = System_Create(&gEffectSystem);
		resultEffect = gEffectSystem->init(7, FMOD_INIT_NORMAL, 0);

		char str[128];
		for (int i = 0; i < SD_EffectSize; i++)
		{
			sprintf_s(str, "Media/e%d.mp3", i);
			gEffectSystem->createSound(str, FMOD_LOOP_OFF, 0, &gEffectSound[i]);
		}
	}

	void EffectPlaySound(int soundNum, Channel*& gEffectChannel)
	{
		gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel);
	}

	void ReleaseEffectSound()
	{
		gEffectSystem->release();
	}

	void Update()
	{
		gEffectSystem->update();
	}

	void PauseChannel(Channel*& gEffectChannel)
	{
		gEffectChannel->setPaused(true);		
	}
	void UnpauseChannel(Channel*& gEffectChannel)
	{
		gEffectChannel->setPaused(false);
	}
}