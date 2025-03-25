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
		unsigned long long duration;  //ms단위
	};

	void InitNote();
	void CalcDuration(Note*& note, int size);
	Note*& GetNotes(int num);
}