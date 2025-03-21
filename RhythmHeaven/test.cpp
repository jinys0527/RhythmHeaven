#include <iostream>
using namespace std;

int main()
{
	FILE* fp;
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	fopen_s(&fp, "Character/Conductor.txt", "rb");
	fopen_s(&fp1, "Character/Chorus_boys_shame.txt", "rb");
	fopen_s(&fp2, "Character/Chorus_boy_slience.txt", "rb");
	fopen_s(&fp3, "Character/Chorus_boy_default.txt", "rb");
	fopen_s(&fp4, "Character/Chorus_boy_enter0.txt", "rb");

	//
	// 장효제 테스트
	//
	char* Word = new char[88];

	if (fp == NULL)
	{
		return 0;
	}

	while (fgets(Word, 88, fp) != nullptr)
	{
		cout << Word;
	}
	cout << endl;
	while (fgets(Word, 88, fp1) != nullptr)
	{
		cout << Word;
	}
	cout << endl;
	while (fgets(Word, 88, fp2) != nullptr)
	{
		cout << Word;
	}
	cout << endl;
	while (fgets(Word, 88, fp3) != nullptr)
	{
		cout << Word;
	}
	cout << endl;
	while (fgets(Word, 88, fp4) != nullptr)
	{
		cout << Word;
	}
	cout << endl;
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);

	return 0;
}