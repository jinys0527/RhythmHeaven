#include "Note.h"
#include "Anim.h"
#include <iostream>

namespace note
{
	Note notes_Player[18] = { {12245, 13380, noteType::Chorus_Do, 0}, {19919, 20453, noteType::Chorus_Do, 0}, {20720, 21421, noteType::Chorus_Do, 0},
								{27618, 28018, noteType::Chorus_Fa, 0}, {28698, 29319, noteType::Chorus_Fa, 0}, {33400, 34734, noteType::Chorus_Do, 0}, 
								{35635, 36369, noteType::Shout, 0},	{43143, 45045, noteType::Chorus_Fa, 0}, {45945, 46679, noteType::Shout, 0}, 
								{58758, 60660, noteType::Chorus_Do, 0},	{66266, 68168, noteType::Chorus_Fa, 0}, {69302, 70036, noteType::Shout, 0}, 
								{75208, 75875, noteType::Chorus_Do, 0},	{76076, 76476, noteType::Chorus_Do, 0}, {80847, 81514, noteType::Chorus_Fa, 0},
								{81714, 82115, noteType::Chorus_Fa, 0}, {87220, 88221, noteType::Chorus_Do, 0},	{89189, 89923, noteType::Shout, 0} };

	Note notes_Chorus1[18] = { {8508, 9642, noteType::Chorus, 0}, {16116, 16649, noteType::Chorus, 0}, {16916, 17617, noteType::Chorus, 0},
							{23823, 24224, noteType::Chorus, 0}, {24904, 25525, noteType::Chorus, 0}, {31598, 34734, noteType::Chorus, 0},
							{35635, 36369, noteType::Shout, 0}, {39339, 41241, noteType::Chorus, 0}, {45945, 46679, noteType::Shout, 0}, 
							{54954, 56856, noteType::Chorus, 0}, {62462, 64364, noteType::Chorus, 0}, {69302, 70036, noteType::Shout, 0}, 
							{72405, 73071, noteType::Chorus, 0}, {73273, 73673, noteType::Chorus, 0}, {78044, 78711, noteType::Chorus, 0}, 
							{78912, 79312, noteType::Chorus, 0}, {85885, 88221, noteType::Chorus, 0}, {89189, 89923, noteType::Shout, 0} };

	Note notes_Chorus2[18] = { {10377, 11511, noteType::Chorus, 0}, {18018, 18551, noteType::Chorus, 0}, {18818, 19519, noteType::Chorus, 0},
							{25721, 26121, noteType::Chorus, 0}, {26801, 27422, noteType::Chorus, 0}, {32499, 34734, noteType::Chorus, 0}, 
							{35635, 36369, noteType::Shout, 0},	{41241, 43143, noteType::Chorus, 0}, {45945, 46679, noteType::Shout, 0}, 
							{56856, 58758, noteType::Chorus, 0}, {64364, 66266, noteType::Chorus, 0}, {69302, 70036, noteType::Shout, 0}, 
							{73807, 74474, noteType::Chorus, 0}, {74674, 75075, noteType::Chorus, 0}, {79446, 80113, noteType::Chorus, 0}, 
							{80313, 80713, noteType::Chorus, 0}, {86553, 88221, noteType::Chorus, 0}, {89189, 89923, noteType::Shout, 0} };

	Note* Note_Player = notes_Player;
	Note* Note_Chorus1 = notes_Chorus1;
	Note* Note_Chorus2 = notes_Chorus2;

	Note tutorial_Notes_Player[6] = { {12554, 13888, noteType::Chorus, 0}, {22581, 23916, noteType::Chorus, 0}, {33829, 35164, noteType::Chorus, 0},
									{43839, 45174, noteType::Chorus, 0}, {56180, 56931, noteType::Shout, 0 }, {62187, 62937, noteType::Shout, 0} };
	Note tutorial_Notes_Chorus1[6] = { {9884, 11219, noteType::Chorus, 0}, {19912, 21246, noteType::Chorus, 0}, {31160, 35164, noteType::Chorus, 0}, 
									{41170, 45174, noteType::Chorus, 0}, {56180, 56931, noteType::Shout, 0 }, {62187, 62937, noteType::Shout, 0} };
	Note tutorial_Notes_Chorus2[6] = { {11219, 12554, noteType::Chorus, 0}, {21246, 22581, noteType::Chorus, 0}, {32494, 35164, noteType::Chorus, 0}, 
									{42504, 45174, noteType::Chorus, 0}, {56180, 56931, noteType::Shout, 0 }, {62187, 62937, noteType::Shout, 0} };

	Note* Tutorial_Note_Player = tutorial_Notes_Player;
	Note* Tutorial_Note_Chorus1 = tutorial_Notes_Chorus1;
	Note* Tutorial_Note_Chorus2 = tutorial_Notes_Chorus2;

	int playerNoteIndex = 0;
	int chorusNoteIndex1 = 0;
	int chorusNoteIndex2 = 0;

	int tutorialPlayerNoteIndex = 0;
	int tutorialChorusNoteIndex1 = 0;
	int tutorialChorusNoteIndex2 = 0;

	void InitNote() //ms단위 노트 초기화
	{
		CalcDuration(Note_Player, 18);
		CalcDuration(Note_Chorus1, 18);
		CalcDuration(Note_Chorus2, 18);
	}

	void InitTutorialNote()
	{
		CalcDuration(Tutorial_Note_Player, 6);
		CalcDuration(Tutorial_Note_Chorus1, 6);
		CalcDuration(Tutorial_Note_Chorus2, 6);
	}

	void CalcDuration(Note*& note, int size)
	{
		for (int i = 0; i < size; i++)
		{
			note[i].duration = note[i].endTime - note[i].startTime;
		}
	}

	Note*& GetNotes(anim::Character*& character)
	{
		switch (character->characterType)
		{
		case anim::CharacterType::PLAYER:
			return Note_Player;
		case anim::CharacterType::CHORUS1:
			return Note_Chorus1;
		case anim::CharacterType::CHORUS2:
			return Note_Chorus2;
		}
	}

	Note*& GetTutorialNotes(anim::Character*& character)
	{
		switch (character->characterType)
		{
		case anim::CharacterType::PLAYER:
			return Tutorial_Note_Player;
		case anim::CharacterType::CHORUS1:
			return Tutorial_Note_Chorus1;
		case anim::CharacterType::CHORUS2:
			return Tutorial_Note_Chorus2;
		}
	}

	int& GetIndex(anim::Character*& character) {
		switch (character->characterType)
		{
		case anim::CharacterType::PLAYER:
			return playerNoteIndex;
		case anim::CharacterType::CHORUS1:
			return chorusNoteIndex1;
		case anim::CharacterType::CHORUS2:
			return chorusNoteIndex2;
		}
	}

	int& GetTutorialIndex(anim::Character*& character) {
		switch (character->characterType)
		{
		case anim::CharacterType::PLAYER:
			return tutorialPlayerNoteIndex;
		case anim::CharacterType::CHORUS1:
			return tutorialChorusNoteIndex1;
		case anim::CharacterType::CHORUS2:
			return tutorialChorusNoteIndex2;
		}
	}
}

