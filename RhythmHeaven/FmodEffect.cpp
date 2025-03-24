#include "FmodEffect.h"
#include "inc/fmod_errors.h"

namespace effectsound
{
	enum EffectSounds
	{
		SD_Ah = 0,     // 코러스 : e1.mp3
		SD_AhPlayer,   // 코러스 Player 버전 : e1.mp3
		SD_Shout,      // 샤우트 : e2.mp3
		SD_Close,      // 입 닫는 소리 : e3.mp3
		SD_Together,   // Together : e4.mp3
		SD_EffectSize
	};

	System* gEffectSystem;
	Sound* gEffectSound[SD_EffectSize];
	FMOD_RESULT resultEffect;
	
	Channel* gEffectChannel1; //chorus1
	Channel* gEffectChannel2; //chorus2
	Channel* gEffectChannel3; //player
	Channel* gEffectChannel4; //player(close)
	Channel* gEffectChannel5; //player(shout)
	Channel* gEffectChannel6; //conductor

	Channel*& GetChannel(int num)
	{
		switch (num)
		{
		case 1:
			return gEffectChannel1;
		case 2:
			return gEffectChannel2;
		case 3:
			return gEffectChannel3;
		case 4:
			return gEffectChannel4;
		case 5:
			return gEffectChannel5;
		case 6:
			return gEffectChannel6;
		}
	}

	void EffectSoundSetUp()
	{
		resultEffect = System_Create(&gEffectSystem);
		resultEffect = gEffectSystem->init(4, FMOD_INIT_NORMAL, 0);

		char str[128];
		for (int i = 0; i < SD_EffectSize; i++)
		{
			if (i == 0)
			{
				sprintf_s(str, "Media/e%d.mp3", i + 1);
				gEffectSystem->createSound(str, FMOD_LOOP_OFF, 0, &gEffectSound[i]);
			}
			else if (i != 1)
			{
				sprintf_s(str, "Media/e%d.mp3", i);
				gEffectSystem->createSound(str, FMOD_LOOP_OFF, 0, &gEffectSound[i]);
			}
			else
			{
				sprintf_s(str, "Media/e%d.mp3", i);
				gEffectSystem->createSound(str, FMOD_LOOP_NORMAL, 0, &gEffectSound[i]);
				gEffectSound[i]->setMusicSpeed(0.15f);
				gEffectSound[i]->setLoopPoints(50, FMOD_TIMEUNIT_MS, 550, FMOD_TIMEUNIT_MS);
			}
		}
	}

	void EffectPlaySound(int soundNum, Channel*& gEffectChannel)
	{
		gEffectSystem->playSound(gEffectSound[soundNum], 0, false, &gEffectChannel);
		gEffectChannel->setVolume(0.3f);
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