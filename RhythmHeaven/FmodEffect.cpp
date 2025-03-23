#include "FmodEffect.h"
#include "inc/fmod_errors.h"

namespace effectsound
{
	enum EffectSounds
	{
		SD_Ah = 0,     // 코러스 : e_1.wav
		SD_AhPlayer,   // 코러스 player 버전 : e_1.wav
		SD_Shout,      // 샤우트 : e_2.wav
		SD_Close,      // 입 닫는 소리 : e_3.wav
		SD_Together,   // Together : e_4.wav
		SD_EffectSize
	};

	System* gEffectSystem;
	Sound* gEffectSound[SD_EffectSize];
	FMOD_RESULT resultEffect;

	Channel* gEffectChannel1; //chorus1
	Channel* gEffectChannel2; //chorus2
	Channel* gEffectChannel3; //player
	Channel* gEffectChannel4; //conductor

	void EffectSoundSetUp()
	{
		resultEffect = System_Create(&gEffectSystem);
		resultEffect = gEffectSystem->init(4, FMOD_INIT_NORMAL, 0);

		char str[128];
		for (int i = 0; i < SD_EffectSize; i++)
		{
			if (i != 0)
			{
				sprintf_s(str, "Media/e%d.mp3", i);
				gEffectSystem->createSound(str, FMOD_LOOP_NORMAL, 0, &gEffectSound[i]);
			}
			else
			{
				sprintf_s(str, "Media/e%d.mp3", i + 1);
				gEffectSystem->createSound(str, FMOD_LOOP_OFF, 0, &gEffectSound[i]);
			}
		}
	}

	void EffectPlaySound(int soundNum)
	{
		switch (soundNum)
		{
		case 0:
			gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel1);
			gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel2);
			gEffectChannel1->setVolume(0.3f);
			gEffectChannel2->setVolume(0.3f);
			break;
		case 1:
			gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel3);
			gEffectChannel3->setVolume(0.3f);
			break;
		case 2:
			gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel1);
			gEffectChannel1->setVolume(0.3f);
			break;
		}
	}

	void ReleaseEffectSound()
	{
		gEffectSystem->release();
	}
	void Update()
	{
		gEffectSystem->update();
	}
}