#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "ScoreSystem.h"
#include "Fmod.h"
#include "Note.h"
#include "Anim.h"
#include "GameManager.h"
#include "RenderSystem.h"


namespace score
{
    // 전역 인스턴스 (내부에서만 접근)
    static Judgepoint g_judges;
    static ScoreData g_ScoreData = { 0, {0, 0, 0} };
    static FontData g_FontData = {
        // 숫자 0-9 ASCII 아트
        {
            {
                {"   ## ##    "},
                {"  ##   ##   "},
                {"  ##   ##   "},
                {"  ##   ##   "},
                {"  ##   ##   "},
                {"  ##   ##   "},
                {"   ## ##    "}
            },
            {
                {"    ##      "},
                {"   ###      "},
                {"    ##      "},
                {"    ##      "},
                {"    ##      "},
                {"    ##      "},
                {"   ####     "}
            },
            {
                {"   ## ##    "},
                {"   ##  ##   "},
                {"      ##    "},
                {"     ##     "},
                {"    ##      "},
                {"   #   ##   "},
                {"  ######    "}
            },
            {
                {"   ## ##    "},
                {"  ##   ##   "},
                {"      ##    "},
                {"    ###     "},
                {"      ##    "},
                {"  ##   ##   "},
                {"   ## ##    "}
            },
            {
                {"     ##    "},
                {"    # ##   "},
                {"   ## ##   "},
                {"  ##  ##   "},
                {"  ### ###  "},
                {"      ##   "},
                {"      ##   "}
            },
            {
                {"  ######   "},
                {"  ##       "},
                {"  ## ##    "},
                {"      ##   "},
                {"  ##  ##   "},
                {"  ##  ##   "},
                {"    ###    "}
            },
            {
                {"   #####   "},
                {"  ##   ##  "},
                {"  ##       "},
                {"  ## ###   "},
                {"  ##   ##  "},
                {"  ##   ##  "},
                {"   ## ##   "}
            },
            {
                {"  ######   "},
                {"  ##   #   "},
                {"     ##    "},
                {"    ##     "},
                {"    ##     "},
                {"    ##     "},
                {"    ##     "}
            },
            {
                {"   ## ##   "},
                {"  ##   ##  "},
                {"  ##   ##  "},
                {"   ## ##   "},
                {"  ##   ##  "},
                {"  ##   ##  "},
                {"   ## ##   "}
            },
            {
                {"   ## ##   "},
                {"  #    ##  "},
                {"  ##   ##  "},
                {"   ## ###  "},
                {"       ##  "},
                {"  ##   ##  "},
                {"    ## ##  "}
            }
        },

        // "SCORE" 텍스트 ASCII 아트
        {
            {" _____  _____  _____ ______  _____"},
            {"/  ___|/  __ l|  _  || ___ l|  ___|"},
            {"l `--. | /  l/| | | || |_/ /| |__  "},
            {" `--. l| |    | | | ||    / |  __| "},
            {"/l__/ /| l__/ll l_/ /| |l l | |___ "},
            {"l____/  l____/ l___/ l_| l_|l____/ "},
        },

        // "HIGH SCORE" 텍스트 ASCII 아트
        {
            {" _   _  _____  _____  _   _   _____  _____  _____ ______  _____"},
            {"| | | ||_   _||  __ l| | | | /  ___|/  __ l|  _  || ___ l|  ___|"},
            {"| |_| |  | |  | |  l/| |_| | l `--. | /  l/| | | || |_/ /| |__  "},
            {"|  _  |  | |  | | __ |  _  |  `--. l| |    | | | ||    / |  __| "},
            {"| | | | _| |_ | |_l l| | | | /l__/ /| l__/ll l_/ /| |l l | |___ "},
            {"l_| |_/ l___/  l____/l_| |_/ l____/  l____/ l___/ l_| l_|l____/ "},
        },

        // 알파벳 A-Z ASCII 아트
        {
            {
                {"  ,---.   "},
                {" /  O  l  "},
                {"|  .-.  | "},
                {"|  | |  | "},
                {"`--' `--' "},
            },
            {
                {",-----.   "},
                {"|  |) /_  "},
                {"|  .-.  l "},
                {"|  '--' / "},
                {"`------'  "},
            },
            {
                {" ,-----. "},
                {"'  .--./ "},
                {"|  |     "},
                {"'  '--'l "},
                {" `-----' "},
            },
            {
                {",------.   "},
                {"|  .-.  l  "},
                {"|  |  l  : "},
                {"|  '--'  / "},
                {"`-------'  "},
            },
            {
                {",------. "},
                {"|  .---' "},
                {"|  `--,  "},
                {"|  `---. "},
                {"`------' "},
            },
            {
                {",------. "},
                {"|  .---' "},
                {"|  `--,  "},
                {"|  |`    "},
                {"`--'     "},
            },
            {
                {" ,----.    "},
                {"'  .-./    "},
                {"|  | .---. "},
                {"'  '--'  | "},
                {" `------'  "},
            },
            {
                {",--.  ,--. "},
                {"|  '--'  | "},
                {"|  .--.  | "},
                {"|  |  |  | "},
                {"`--'  `--' "},
            },
            {
                {",--. "},
                {"|  | "},
                {"|  | "},
                {"|  | "},
                {"`--' "},
            },
            {
                {"     ,--."},
                {"     |  |"},
                {",--. |  |"},
                {"|  '-'  /"},
                {" `-----' "},
            },
            {
                {",--. ,--. "},
                {"|  .'   / "},
                {"|  .   '  "},
                {"|  |l   l "},
                {"`--' '--' "},
            },
            {
                {",--.    "},
                {"|  |    "},
                {"|  |    "},
                {"|  '--. "},
                {"`-----' "},
            },
            {
                {",--.  ,--. "},
                {"|  ,'.|  | "},
                {"|  |' '  | "},
                {"|  | `   | "},
                {"`--'  `--' "},
            },
            {
                {",--.   ,--. "},
                {"|   `.'   | "},
                {"|  |'.'|  | "},
                {"|  |   |  | "},
                {"`--'   `--' "},
            },
            {
                {" ,-----.  "},
                {"'  .-.  ' "},
                {"|  | |  | "},
                {"'  '-'  ' "},
                {" `-----'  "},
            },
            {
                {",------.  "},
                {"|  .--. ' "},
                {"|  '--' | "},
                {"|  | --'  "},
                {"`--'      "},
            },
            {
                {" ,-----.   "},
                {"'  .-.  '  "},
                {"|  | |  |  "},
                {"'  '-'  '-."},
                {" `-----'--'"},
            },
            {
                {",------.  "},
                {"|  .--. ' "},
                {"|  '--'.' "},
                {"|  |l  l  "},
                {"`--' '--' "},
            },
            {
                {" ,---.   "},
                {"'   .-'  "},
                {"`.  `-.  "},
                {".-'    | "},
                {"`-----'  "},
            },
            {
                {",--------. "},
                {"'--.  .--' "},
                {"   |  |    "},
                {"   |  |    "},
                {"   `--'    "},
            },
            {
                {",--. ,--. "},
                {"|  | |  | "},
                {"|  | |  | "},
                {"'  '-'  ' "},
                {" `-----'  "},
            },
            {
                {",--.   ,--. "},
                {" l  `.'  /  "},
                {"  l     /   "},
                {"   l   /    "},
                {"    `-'     "},
            },
            {
                {",--.   ,--. "},
                {"|  |   |  | "},
                {"|  |.'.|  | "},
                {"|   ,'.   | "},
                {"'--'   '--' "},
            },
            {
                {",--.   ,--. "},
                {" l  `.'  /  "},
                {"  .'    l   "},
                {" /  .'.  l  "},
                {"'--'   '--' "},
            },
            {
                {",--.   ,--. "},
                {" l  `.'  /  "},
                {"  '.    /   "},
                {"    |  |    "},
                {"    `--'    "},
            },
            {
                {",-------. "},
                {"`--.   /  "},
                {"  /   /   "},
                {" /   `--. "},
                {"`-------' "},
            }
        }
    };

    bool syncStart = false;
    bool syncEnd = false;

    // 데이터 접근 함수
    void Initialize(ScoreData* scoreData) {
        if (scoreData) {
            scoreData->currentScore = 0;
            scoreData->nickname[0] = 0;
            scoreData->nickname[1] = 0;
            scoreData->nickname[2] = 0;
        }
    }

    FontData* GetFontData() {
        return &g_FontData;
    }

    // 유틸리티 함수: 색깔과 함께 커서 위치 설정
    void Gotoxy(int x, int y, unsigned short text_Color, unsigned short back_Color) {
        COORD pos = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_Color | (back_Color << 4));
    }

    // 점수를 업데이트하고 출력하는 함수
    void PrintNumber(ScoreData* scoreData, int x, int y, int Num) {
        if (!scoreData) {
            scoreData = &g_ScoreData;
        }

        scoreData->currentScore += Num;
        Num = scoreData->currentScore;

        // 각 단위로 분할하여 큰 수 출력을 처리
        int digit;
        int position = 0;
        int divisor = 1;

        // 가장 큰 자릿수 찾기
        int temp = Num;
        while (temp >= 10) {
            temp /= 10;
            divisor *= 10;
        }

        // 각 자리를 출력
        while (divisor > 0) {
            digit = Num / divisor;
            Num %= divisor;

            // 이 자릿수에 해당하는 ASCII 아트 그리기
            for (int i = 0; i < 7; i++) {
				render::GotoXY(x + 18 + position * 12, y + i);// 18은 3자리 숫자를 표시하기 위한 간격
                for (int j = 0; j < 13; j++) {
                    printf("%c", g_FontData.number[digit][i][j]);
                }
            }

            position++;
            divisor /= 10;
        }
    }

    // 점수를 업데이트하지 않고 표시하는 함수
    void ShowNumber(int x, int y, int Num) {
        // 0인 경우 별도 처리
        if (Num == 0) {
            for (int i = 0; i < 7; i++) {
                render::GotoXY(x, y + i);
                for (int j = 0; j < 13; j++) {
                    printf("%c", g_FontData.number[0][i][j]);
                }
            }
            return;
        }

        // 큰 숫자 표시 처리
        int digits[3] = { 0 }; // 최대 3자리 지원 (0~100)
        int numDigits = 0;

        // 숫자를 개별 자릿수로 분해
        while (Num > 0 && numDigits < 3) {
            digits[numDigits++] = Num % 10;
            Num /= 10;
        }

        // 자릿수를 역순으로 표시 (가장 큰 자릿수부터)
        for (int pos = numDigits - 1; pos >= 0; pos--) {
            int displayPos = numDigits - 1 - pos;
            for (int i = 0; i < 7; i++) {
                render::GotoXY(x + displayPos * 12, y + i);
                for (int j = 0; j < 13; j++) {
                    printf("%c", g_FontData.number[digits[pos]][i][j]);
                }
            }
        }
    }

    // "SCORE" 텍스트 표시
    void PrintScoreTEXT(int x, int y) {
        for (int i = 0; i < 7; i++) {
            render::GotoXY(x, y + i);
            for (int j = 0; j < 36; j++) {
                printf("%c", g_FontData.scoreText[i][j]);
            }
        }
    }

    // "HIGH SCORE" 텍스트 표시
    void PrintHighScoreTEXT(int x, int y) {
        for (int i = 0; i < 6; i++) {
            render::GotoXY(x, y + i);
            for (int j = 0; j < 69; j++) {
                printf("%c", g_FontData.highScoreText[i][j]);
            }
        }
    }

    // 파일에서 최고 점수 불러오기
    int LoadScore(ScoreData* scoreData) {
        if (!scoreData) {
            scoreData = &g_ScoreData;
        }

        FILE* fp;
        int score = 0;

        fopen_s(&fp, "Score.txt", "r");
        if (fp != NULL) {
            fscanf_s(fp, "%d %d %d %d", &score, &scoreData->nickname[0], &scoreData->nickname[1], &scoreData->nickname[2]);
            fclose(fp);
        }

        return score;
    }

    // 파일에 최고 점수 저장
    void SaveScore(ScoreData* scoreData) {
        if (!scoreData) {
            scoreData = &g_ScoreData;
        }

        FILE* fp;
        fopen_s(&fp, "Score.txt", "w");

        if (fp != NULL) {
            fprintf(fp, "%d %d %d %d\n", scoreData->currentScore, scoreData->nickname[0], scoreData->nickname[1], scoreData->nickname[2]);
            fclose(fp);
        }
    }

    void JudgeStartTime(anim::Character*& character, note::Note*& note) {
        if (game::GetState() == game::State::Game)
        {
            int& j_index = note::GetIndex(character);

            unsigned int playPos = sound::GetPlayPosition(sound::GetChannel(2));
            const int tolerance = 1000; //오차 범위
            long long low = note[j_index].startTime - tolerance;
            long long high = note[j_index].startTime + tolerance;
     
            if (low > playPos)
            {
                return;
            }

            if (low <= playPos && playPos <= high) {
                syncStart = true;
            }
            else
            {
                syncStart = false;
            }

            if (character->currentState == anim::AnimState::SHOUT)
            {
                JudgeShout();
            }
        }

        else if (game::GetState() == game::State::Tutorial)
        {
            int& j_index = note::GetTutorialIndex(character);

            unsigned int playPos = sound::GetPlayPosition(sound::GetChannel(1));
            const int tolerance = 1000; //오차 범위
            long long low = note[j_index].startTime - tolerance;
            long long high = note[j_index].startTime + tolerance;
           
            if (low > playPos)
            {
                return;
            }

            if (low <= playPos && playPos <= high) {
                syncStart = true;
            }
            else
            {
                syncStart = false;
            }

            if (character->currentState == anim::AnimState::SHOUT)
            {
                JudgeShout();
            }
        }       
    }

    void JudgeEndTime(anim::Character*& character, note::Note*& note) {
        if (game::GetState() == game::State::Game)
        {
            int& j_index = note::GetIndex(character);
            unsigned int playPos = sound::GetPlayPosition(sound::GetChannel(2));
            const int tolerance = 1000; //오차 범위
            long long low = note[j_index].endTime - tolerance;
            long long high = note[j_index].endTime + tolerance;

            if (low > playPos)
            {
                return;
            }

            if (low <= playPos && playPos <= high) {
                syncEnd = true;
            }
            else
            {
                syncEnd = false;
            }

            if (playPos > note[j_index].endTime && playPos <= note[j_index + 1].startTime)
            {
                JudgeScore();
                j_index++;
            }
        }
        else if (game::GetState() == game::State::Tutorial)
        {
            int& j_index = note::GetTutorialIndex(character);
            unsigned int playPos = sound::GetPlayPosition(sound::GetChannel(1));
            const int tolerance = 1000; //오차 범위
            long long low = note[j_index].endTime - tolerance;
            long long high = note[j_index].endTime + tolerance;

            if (low > playPos)
            {
                return;
            }

            if (low <= playPos && playPos <= high) {
                syncEnd = true; 
            }
            else
            {
                syncEnd = false;
            }

            if (playPos > note[j_index].endTime && playPos <= note[j_index + 1].startTime)
            {
                JudgeScore();
                j_index++;
            }
        }
    }

    // 닉네임 표시 (알파벳 3글자)
    void PrintNickName(int x, int y, const int* name) {
        for (int i = 0; i < 3; i++) {
            int charIndex = name[i];
            if (charIndex >= 0 && charIndex < 26) {
                for (int j = 0; j < 5; j++) {
                    render::GotoXY(x + i * 12, y + j);
                    printf("%s", g_FontData.alphabet[charIndex][j]);
                }
            }
        }
    }

    // 단일 문자 표시
    void PrintChar(int x, int y, int _char) {
        // 먼저 영역 지우기
        for (int i = 0; i < 5; i++) {
            render::GotoXY(x, y + i);
            printf("              ");
        }

        // 문자 인덱스 유효성 검사
        if (_char >= 0 && _char < 26) {
            for (int i = 0; i < 5; i++) {
                render::GotoXY(x, y + i);
                printf("%s", g_FontData.alphabet[_char][i]);
            }
        }
    }

    // 최종 점수 표시 및 닉네임 입력 처리
    void ShowScore(ScoreData* scoreData) {
        sound::Playsound(6, sound::GetChannel(6));
        
        if (!scoreData) {
            scoreData = &g_ScoreData;
        }

        const int highScoreX = 67;
        const int highScoreY = 3;
        const int myScoreX = 65;
        const int myScoreY = 40;
        const int nickX = 29;
        const int nickY = 10;

        // 현재 점수 표시
        PrintScoreTEXT(myScoreX + 18, myScoreY - 9);
        PrintNumber(scoreData, myScoreX, myScoreY, 0);

        // 최고 점수 표시
        int highScore = LoadScore(scoreData);
        PrintHighScoreTEXT(highScoreX, highScoreY);
		ShowNumber(highScoreX + 26, highScoreY + 7, highScore); // 16은 3자리 숫자를 표시하기 위한 간격
        PrintNickName(highScoreX + 16, highScoreY + 17, scoreData->nickname);

        // 닉네임 입력 처리
        int selectedChar = 0;
        int charPosition = 0;

        // 초기 문자 및 밑줄 그리기
        PrintChar(myScoreX + charPosition * nickX, myScoreY + nickY, selectedChar);
        for (int j = 0; j < 3; j++) {
            render::GotoXY(myScoreX - 2 + j * nickX, myScoreY + nickY + 6);
            printf("_____________");
        }

        ULONGLONG nowTick = GetTickCount64();
        ULONGLONG prevTick = nowTick;
        ULONGLONG animTick = nowTick;

        // 닉네임 입력 받기
        while (charPosition < 3) {

            nowTick = GetTickCount64();
            if (nowTick - animTick >= 33)
            {
                if (GetAsyncKeyState(VK_UP) & 1 && selectedChar < 25) {
                    selectedChar++;
                    PrintChar(myScoreX + charPosition * nickX, myScoreY + nickY, selectedChar);
                }
                else if (GetAsyncKeyState(VK_DOWN) & 1 && selectedChar > 0) {
                    selectedChar--;
                    PrintChar(myScoreX + charPosition * nickX, myScoreY + nickY, selectedChar);
                }
                else if (GetAsyncKeyState(VK_RETURN) & 1) {
                    scoreData->nickname[charPosition] = selectedChar;
                    charPosition++;

                    if (charPosition < 3) {
                        selectedChar = 0;
                        PrintChar(myScoreX + charPosition * nickX, myScoreY + nickY, selectedChar);
                    }
                }
                animTick = nowTick;

            }

        }

        // 최고 점수인 경우 저장
        if (highScore < scoreData->currentScore) {
            SaveScore(scoreData);
        }

        system("cls");
    }

    void JudgeScore()
    {
        if (syncStart && syncEnd)
        {
            a_ScoreData.currentScore += 1;
        }
        else
        {
            anim::Shame();
        }
    }

    void JudgeShout()
    {
        if (syncStart)
        {
            a_ScoreData.currentScore += 1;
        }
        else
        {
            anim::Shame();
        }
    }

    int GetScore()
    {
        return a_ScoreData.currentScore;
    }

    void callShowScore() {
        ScoreData scoreData;
        Initialize(&scoreData);
        scoreData.currentScore = a_ScoreData.currentScore;
        score::ShowScore(&scoreData);
    }
}