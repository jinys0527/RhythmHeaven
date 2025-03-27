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
		long long startTime; //ms단위
		long long endTime;   //ms단위
		noteType curNoteType;
		long long duration;  //ms단위
	};

	void InitNote();
	void CalcDuration(Note*& note, int size);
	Note*& GetNotes(int num);
}