#include "Note.h"
#include <iostream>
namespace note
{
	Note notes_Player[22] = { {12070, 13110, noteType::Chorus_Do, 0}, {19270, 20130, noteType::Chorus_Do, 0}, {20210, 21120, noteType::Chorus_Do, 0},
								{27040, 27160, noteType::Chorus_Fa, 0}, {27180, 27220, noteType::Chorus_Fa, 0}, {27240, 27280, noteType::Chorus_Fa, 0},
								{28000, 28080, noteType::Chorus_Fa, 0}, {33110, 34210, noteType::Chorus_Do, 0}, {35180, 36100, noteType::Shout, 0},
								{43030, 45000, noteType::Chorus_Fa, 0}, {45270, 46190, noteType::Shout, 0}, {58210, 60200, noteType::Chorus_Do, 0},
								{66080, 68050, noteType::Chorus_Fa, 0}, {69090, 70010, noteType::Shout, 0}, {75060, 75100, noteType::Chorus_Do, 0},
								{75140, 75260, noteType::Chorus_Do, 0}, {76020, 76140, noteType::Chorus_Do, 0}, {80250, 80290, noteType::Chorus_Fa, 0},
								{81030, 81150, noteType::Chorus_Fa, 0}, {81210, 82030, noteType::Chorus_Fa, 0}, {87060, 88060, noteType::Chorus_Do, 0},
								{89050, 89270, noteType::Shout, 0} };

	Note notes_Chorus1[22] = { {8150, 9190, noteType::Chorus, 0}, {16030, 16190, noteType::Chorus, 0}, {16270, 17180, noteType::Chorus, 0},
							{23240, 24060, noteType::Chorus, 0}, {24080, 24120, noteType::Chorus, 0}, {24140, 24180, noteType::Chorus, 0},
							{24200, 24280, noteType::Chorus, 0}, {31170, 34210, noteType::Chorus, 0}, {35180, 36100, noteType::Shout, 0},
							{39090, 41060, noteType::Chorus, 0}, {45270, 46190, noteType::Shout, 0}, {54270, 56240, noteType::Chorus, 0},
							{62140, 64110, noteType::Chorus, 0}, {69090, 70010, noteType::Shout, 0}, {72120, 72160, noteType::Chorus, 0},
							{72200, 73020, noteType::Chorus, 0}, {73080, 73200, noteType::Chorus, 0}, {78010, 78050, noteType::Chorus, 0},
							{78090, 78210, noteType::Chorus, 0}, {78270, 79090, noteType::Chorus, 0}, {85260, 88060, noteType::Chorus, 0},
							{89050, 89270, noteType::Shout, 0} };

	Note notes_Chorus2[22] = { {10110, 11150, noteType::Chorus, 0}, {18000, 18160, noteType::Chorus, 0}, {18240, 19150, noteType::Chorus, 0},
							{25140, 25260, noteType::Chorus, 0}, {25280, 26020, noteType::Chorus, 0}, {26040, 26080, noteType::Chorus, 0},
							{26100, 26180, noteType::Chorus, 0}, {32140, 34210, noteType::Chorus, 0}, {35180, 36100, noteType::Shout, 0},
							{41060, 43030, noteType::Chorus, 0}, {45270, 46190, noteType::Shout, 0}, {56240, 58210, noteType::Chorus, 0},
							{64110, 66080, noteType::Chorus, 0}, {69090, 70010, noteType::Shout, 0}, {73240, 73280, noteType::Chorus, 0},
							{74020, 74140, noteType::Chorus, 0}, {74020, 75020, noteType::Chorus, 0}, {79130, 79170, noteType::Chorus, 0},
							{79210, 80030, noteType::Chorus, 0}, {80090, 80210, noteType::Chorus, 0}, {86160, 88060, noteType::Chorus, 0},
							{89050, 89270, noteType::Shout, 0} };

	Note* Note_Player = notes_Player;
	Note* Note_Chorus1 = notes_Chorus1;
	Note* Note_Chorus2 = notes_Chorus2;

	void InitNote() //ms단위 노트 초기화
	{
		CalcDuration(Note_Player, 22);
		CalcDuration(Note_Chorus1, 22);
		CalcDuration(Note_Chorus2, 22);
	}

	void CalcDuration(Note*& note, int size)
	{
		for (int i = 0; i < size; i++)
		{
			note[i].duration = note[i].endTime - note[i].startTime;
		}
	}

	Note*& GetNotes(int num)
	{
		switch (num)
		{
		case 0:
			return Note_Player;
		case 1:
			return Note_Chorus1;
		case 2:
			return Note_Chorus2;
		}
	}
}

