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

    // 점수 관련 구조체
    struct ScoreData {
        int currentScore;    // 현재 점수
        int nickname[3];     // 닉네임 (알파벳 인덱스 3개)
    };

    // 폰트와 그래픽 관련 구조체
    struct FontData {
        char number[10][7][13];       // 숫자 0-9 ASCII 아트
        char scoreText[7][36];        // "SCORE" 텍스트 ASCII 아트
        char highScoreText[6][69];    // "HIGH SCORE" 텍스트 ASCII 아트
        const char* alphabet[26][5];  // 알파벳 A-Z ASCII 아트
    };

    // 초기화 함수
    void Initialize(ScoreData* scoreData);
    FontData* GetFontData();

    // 유틸리티 함수: 색깔과 함께 커서 위치 설정
    // 원래 쓰던 걸로
    void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0);

    // 점수 관련 함수
    void PrintNumber(ScoreData* scoreData, int x, int y, int Num);  // 점수를 업데이트하고 출력
    void ShowNumber(int x, int y, int Num);                         // 점수를 업데이트하지 않고 표시
    int LoadScore(ScoreData* scoreData);                            // 파일에서 최고 점수 불러오기
    void SaveScore(ScoreData* scoreData);                           // 파일에 최고 점수 저장
    void ShowScore(ScoreData* scoreData);                           // 최종 점수 표시 및 닉네임 입력 처리

    void JudgeStartTime(anim::Character*& character, note::Note*& note);
    void JudgeEndTime(anim::Character*& character, note::Note*& note);
    void JudgeScore();
    void JudgeShout();

    // 텍스트 표시 함수
    void PrintScoreTEXT(int x, int y);                             // "SCORE" 텍스트 표시
    void PrintHighScoreTEXT(int x, int y);                         // "HIGH SCORE" 텍스트 표시
    void PrintNickName(int x, int y, const int* name);             // 닉네임 표시 (알파벳 3글자)
    void PrintChar(int x, int y, int _char);                       // 단일 문자 표시
}