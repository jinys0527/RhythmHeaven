#include "Fmod.h"

namespace sound
{
	enum Sounds
	{
		SD_TitleMusic = 0,
		SD_TutorialMusic,
		SD_GleeClub,
		SD_EndingMusic_Bad,
		SD_EndingMusic_Normal,
		SD_EndingMusic_True,
		SD_RankingMusic,
		SD_Size
	};

	System* gSystem;
	Sound* gSound[SD_Size];
	Channel* gChannel0;		//TitleMusic		Loop
	Channel* gChannel1;		//TutorialMusic		
	Channel* gChannel2;		//GleeClub
	Channel* gChannel3;		//BadEndingSound
	Channel* gChannel4;		//NormalEndingSound
	Channel* gChannel5;		//TrueEndingSound
	Channel* gChannel6;		//RankingMusic		Loop
	FMOD_RESULT result;

	void SoundSetUp()
	{
		result = System_Create(&gSystem);
		result = gSystem->init(7, FMOD_INIT_NORMAL, 0);

		gSystem->createSound("Media/TitleSound.mp3", FMOD_LOOP_NORMAL, 0, &gSound[0]);
		gSystem->createSound("Media/TutorialSound.mp3", FMOD_LOOP_OFF, 0, &gSound[1]);
		gSystem->createSound("Media/GleeClub.mp3", FMOD_LOOP_OFF, 0, &gSound[2]);
		gSystem->createSound("Media/BadEndingSound.mp3", FMOD_LOOP_OFF, 0, &gSound[3]);
		gSystem->createSound("Media/NormalEndingSound.mp3", FMOD_LOOP_OFF, 0, &gSound[4]);
		gSystem->createSound("Media/TrueEndingSound.mp3", FMOD_LOOP_OFF, 0, &gSound[5]);
		gSystem->createSound("Media/RankingMusic.wav", FMOD_LOOP_NORMAL, 0, &gSound[6]);
	}

	void Playsound(int soundNum, Channel*& gChannel)
	{
		gSystem->playSound(gSound[soundNum], 0, false, &gChannel);
	}

	void Stopsound(Channel*& gChannel)
	{
		gChannel->stop();
	}

	void Releasesound()
	{
		gSystem->release();
	}

	Channel*& GetChannel(int num)
	{
		switch (num)
		{
		case 0:
			return gChannel0;
		case 1:
			return gChannel1;
		case 2:
			return gChannel2;
		case 3:
			return gChannel3;
		case 4:
			return gChannel4;
		case 5:
			return gChannel5;
		case 6:
			return gChannel6;
		}
	}

	unsigned int GetPlayPosition(Channel*& gChannel)
	{
		unsigned int playPosition = 0;
		gChannel->getPosition(&playPosition, FMOD_TIMEUNIT_MS);
		return playPosition;
	}
}