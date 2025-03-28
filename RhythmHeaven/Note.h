#pragma once

namespace anim
{
	struct Character;
}

namespace note
{
	enum noteType
	{
		Chorus = 0,
		Chorus_Do,
		Chorus_Fa,
		Shout
	};

	struct Note
	{
		long long startTime; //ms����
		long long endTime;   //ms����
		noteType curNoteType;
		long long duration;  //ms����
	};

	int& GetIndex(anim::Character*& character);
	void InitNote();
	void InitTutorialNote();
	void CalcDuration(Note*& note, int size);
	Note*& GetNotes(anim::Character*& character);
	Note*& GetTutorialNotes(anim::Character*& character);
	int& GetTutorialIndex(anim::Character*& character);
}