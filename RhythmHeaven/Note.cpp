#include "Note.h"

namespace note
{
	void InitNote() //ms단위 노트 초기화
	{
		Note Notes_Player[22] = { {12070, 13110, Chorus_Do}, {19270, 20130, Chorus_Do}, {20210, 21120, Chorus_Do},
								{27040, 27160, Chorus_Fa}, {27180, 27220, Chorus_Fa}, {27240, 27280, Chorus_Fa},
								{28000, 28080, Chorus_Fa}, {33110, 34210, Chorus_Do}, {35180, 36100, Shout},
								{43030, 45000, Chorus_Fa}, {45270, 46190, Shout}, {58210, 60200, Chorus_Do},
								{66080, 68050, Chorus_Fa}, {69090, 70010, Shout}, {75060, 75100, Chorus_Do},
								{75140, 75260, Chorus_Do}, {76020, 76140, Chorus_Do}, {80250, 80290, Chorus_Fa},
								{81030, 81150, Chorus_Fa}, {81210, 82030, Chorus_Fa}, {87060, 88060, Chorus_Do},
								{89050, 89270, Shout} };

		Note Notes_Chorus1[22] = { {8150, 9190, Chorus}, {16030, 16190, Chorus}, {16270, 17180, Chorus},
								{23240, 24060, Chorus}, {24080, 24120, Chorus}, {24140, 24180, Chorus},
								{24200, 24280, Chorus}, {31170, 34210, Chorus}, {35180, 36100, Shout},
								{39090, 41060, Chorus}, {45270, 46190, Shout}, {54270, 56240, Chorus},
								{62140, 64110, Chorus}, {69090, 70010, Shout}, {72120, 72160, Chorus},
								{72200, 73020, Chorus}, {73080, 73200, Chorus}, {78010, 78050, Chorus},
								{78090, 78210, Chorus}, {78270, 79090, Chorus}, {85260, 88060, Chorus},
								{89050, 89270, Shout} };

		Note Notes_Chorus2[22] = { {10110, 11150, Chorus}, {18000, 18160, Chorus}, {18240, 19150, Chorus},
								{25140, 25260, Chorus}, {25280, 26020, Chorus}, {26040, 26080, Chorus},
								{26100, 26180, Chorus}, {32140, 34210, Chorus}, {35180, 36100, Shout},
								{41060, 43030, Chorus}, {45270, 46190, Shout}, {56240, 58210, Chorus},
								{64110, 66080, Chorus}, {69090, 70010, Shout}, {73240, 73280, Chorus},
								{74020, 74140, Chorus}, {74020, 75020, Chorus}, {79130, 79170, Chorus},
								{79210, 80030, Chorus}, {80090, 80210, Chorus}, {86160, 88060, Chorus},
								{89050, 89270, Shout} };

		Note_Player = Notes_Player;
		Note_Chorus1 = Notes_Chorus1;
		Note_Chorus2 = Notes_Chorus2;
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

