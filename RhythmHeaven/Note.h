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
		unsigned long long startTime; //ms����
		unsigned long long endTime;   //ms����
		noteType curNoteType;
	};

	Note* Note_Player;
	Note* Note_Chorus1;
	Note* Note_Chorus2;

	void InitNote();
	Note*& GetNotes(int num);
}