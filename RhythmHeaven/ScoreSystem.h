#pragma once
#include <Windows.h>
#include "Fmod.h"

namespace anim
{
    struct Character;
}

namespace note
{
    struct Note;
}

namespace score
{
    struct Judgepoint {
        int bad; // 0
        int perfect; // 1
    };

    // ���� ���� ����ü
    struct ScoreData {
        int currentScore;    // ���� ����
        int nickname[3];     // �г��� (���ĺ� �ε��� 3��)
    };

    // ��Ʈ�� �׷��� ���� ����ü
    struct FontData {
        char number[10][7][13];       // ���� 0-9 ASCII ��Ʈ
        char scoreText[7][36];        // "SCORE" �ؽ�Ʈ ASCII ��Ʈ
        char highScoreText[6][69];    // "HIGH SCORE" �ؽ�Ʈ ASCII ��Ʈ
        const char* alphabet[26][5];  // ���ĺ� A-Z ASCII ��Ʈ
    };

    // �ʱ�ȭ �Լ�
    void Initialize(ScoreData* scoreData);
    FontData* GetFontData();

    // ��ƿ��Ƽ �Լ�: ����� �Բ� Ŀ�� ��ġ ����
    // ���� ���� �ɷ�
    void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0);

    // ���� ���� �Լ�
    void PrintNumber(ScoreData* scoreData, int x, int y, int Num);  // ������ ������Ʈ�ϰ� ���
    void ShowNumber(int x, int y, int Num);                         // ������ ������Ʈ���� �ʰ� ǥ��
    int LoadScore(ScoreData* scoreData);                            // ���Ͽ��� �ְ� ���� �ҷ�����
    void SaveScore(ScoreData* scoreData);                           // ���Ͽ� �ְ� ���� ����
    void ShowScore(ScoreData* scoreData);                           // ���� ���� ǥ�� �� �г��� �Է� ó��

    void JudgeStartTime(anim::Character*& character, note::Note*& note);
    void JudgeEndTime(anim::Character*& character, note::Note*& note);
    void JudgeScore();
    void JudgeShout();

    // �ؽ�Ʈ ǥ�� �Լ�
    void PrintScoreTEXT(int x, int y);                             // "SCORE" �ؽ�Ʈ ǥ��
    void PrintHighScoreTEXT(int x, int y);                         // "HIGH SCORE" �ؽ�Ʈ ǥ��
    void PrintNickName(int x, int y, const int* name);             // �г��� ǥ�� (���ĺ� 3����)
    void PrintChar(int x, int y, int _char);                       // ���� ���� ǥ��
}