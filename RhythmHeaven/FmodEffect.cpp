#include "FmodEffect.h"

namespace effectsound
{
	enum EffectSounds
	{
		SD_Ah = 0,     // �ڷ��� : e_1.wav
		SD_AhPlayer,   // �ڷ��� player ���� : e_1.wav
		SD_Shout,      // ����Ʈ : e_2.wav
		SD_Close,      // �� �ݴ� �Ҹ� : e_3.wav
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
			if (i == 1)
			{
				sprintf_s(str, "Media/e_%d.wav", i);
				gEffectSystem->createSound(str, FMOD_LOOP_NORMAL, 0, &gEffectSound[i]);
			}
			else
			{
				sprintf_s(str, "Media/e_%d.wav", i + 1);
				gEffectSystem->createSound(str, FMOD_LOOP_OFF, 0, &gEffectSound[i]);
			}
		}
	}

	void EffectPlaySound(int soundNum, Channel* gEffectChannel)
	{
		gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel);
	}

	void ReleaseEffectSound()
	{
		gEffectSystem->release();
	}
}