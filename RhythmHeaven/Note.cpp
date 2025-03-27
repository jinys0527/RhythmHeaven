#include "Note.h"
#include <iostream>
namespace note
{
	Note notes_Player[22] = { {12245, 13380, noteType::Chorus_Do, 0}, {19919, 20453, noteType::Chorus_Do, 0}, {20720, 21421, noteType::Chorus_Do, 0},
								{27160, 27560, noteType::Chorus_Fa, 0}, {27627, 27761, noteType::Chorus_Fa, 0}, {27827, 27961, noteType::Chorus_Fa, 0},
								{28028, 28294, noteType::Chorus_Fa, 0}, {33400, 34734, noteType::Chorus_Do, 0}, {35635, 36369, noteType::Shout, 0},
								{43143, 45045, noteType::Chorus_Fa, 0}, {45945, 46679, noteType::Shout, 0}, {58758, 60660, noteType::Chorus_Do, 0},
								{66266, 68168, noteType::Chorus_Fa, 0}, {69302, 70036, noteType::Shout, 0}, {75208, 75341, noteType::Chorus_Do, 0},
								{75475, 75875, noteType::Chorus_Do, 0}, {76076, 76476, noteType::Chorus_Do, 0}, {80847, 80980, noteType::Chorus_Fa, 0},
								{81114, 81514, noteType::Chorus_Fa, 0}, {81714, 82115, noteType::Chorus_Fa, 0}, {87220, 88221, noteType::Chorus_Do, 0},
								{89189, 89923, noteType::Shout, 0} };

	Note notes_Chorus1[22] = { {8508, 9642, noteType::Chorus, 0}, {16116, 16649, noteType::Chorus, 0}, {16916, 17617, noteType::Chorus, 0},
							{23823, 24224, noteType::Chorus, 0}, {24290, 24424, noteType::Chorus, 0}, {24491, 24624, noteType::Chorus, 0},
							{24691, 24958, noteType::Chorus, 0}, {31598, 34734, noteType::Chorus, 0}, {35635, 36369, noteType::Shout, 0},
							{39339, 41241, noteType::Chorus, 0}, {45945, 46679, noteType::Shout, 0}, {54954, 56856, noteType::Chorus, 0},
							{62462, 64364, noteType::Chorus, 0}, {69302, 70036, noteType::Shout, 0}, {72405, 72539, noteType::Chorus, 0},
							{72672, 73073, noteType::Chorus, 0}, {73273, 73673, noteType::Chorus, 0}, {78044, 78178, noteType::Chorus, 0},
							{78311, 78711, noteType::Chorus, 0}, {78912, 79312, noteType::Chorus, 0}, {85885, 88221, noteType::Chorus, 0},
							{89189, 89923, noteType::Shout, 0} };

	Note notes_Chorus2[22] = { {10377, 11511, noteType::Chorus, 0}, {18018, 18551, noteType::Chorus, 0}, {18818, 19519, noteType::Chorus, 0},
							{25492, 25892, noteType::Chorus, 0}, {25959, 26092, noteType::Chorus, 0}, {26159, 26292, noteType::Chorus, 0},
							{26359, 26626, noteType::Chorus, 0}, {32499, 34734, noteType::Chorus, 0}, {35635, 36369, noteType::Shout, 0},
							{41241, 43143, noteType::Chorus, 0}, {45945, 46679, noteType::Shout, 0}, {56856, 58758, noteType::Chorus, 0},
							{64364, 66266, noteType::Chorus, 0}, {69302, 70036, noteType::Shout, 0}, {73807, 73940, noteType::Chorus, 0},
							{74074, 74474, noteType::Chorus, 0}, {74674, 75075, noteType::Chorus, 0}, {79446, 79579, noteType::Chorus, 0},
							{79712, 80113, noteType::Chorus, 0}, {80313, 80713, noteType::Chorus, 0}, {86553, 88221, noteType::Chorus, 0},
							{89189, 89923, noteType::Shout, 0} };

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

