#pragma once

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
		unsigned long long startTime; //ms단위
		unsigned long long endTime;   //ms단위
		noteType curNoteType;
	};

	Note* Note_Player;
	Note* Note_Chorus1;
	Note* Note_Chorus2;

	void InitNote();
	Note*& GetNotes(int num);
}