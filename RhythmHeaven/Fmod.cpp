#include "Fmod.h"

namespace fmod
{
	enum Sounds
	{
		SD_GleeClub = 0,
		SD_Size
	};

	System* gSystem;
	Sound* gSound[SD_Size];
	Channel* gChannel;
	FMOD_RESULT result;

	void SoundSetUp()
	{
		result = System_Create(&gSystem);
		result = gSystem->init(1, FMOD_INIT_NORMAL, 0);

		char str[128];
		for (int i = 0; i < SD_Size; i++)
		{
			sprintf_s(str, "Media/GleeClub.mp3");
			gSystem->createSound(str, FMOD_LOOP_OFF, 0, &gSound[i]);
		}
	}

	void Playsound(int soundNum)
	{
		gSystem->playSound(gSound[soundNum], 0, false, &gChannel);
	}

	void Pausesound()
	{
		gChannel->setPaused(true);
	}

	void Releasesound()
	{
		gSystem->release();
	}

	unsigned int GetPlayPosition()
	{
		unsigned int playPosition = 0;
		gChannel->getPosition(&playPosition, FMOD_TIMEUNIT_MS);
		return playPosition;
	}

	unsigned int GetLength(int num)
	{
		unsigned int length;
		gSound[num]->getLength(&length, FMOD_TIMEUNIT_MS);
		return length;
	}
}