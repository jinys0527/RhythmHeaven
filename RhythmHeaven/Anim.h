#pragma once
#include <Windows.h>
#define MAX_CHARACTER_SIZE 256

namespace note
{
    struct Note;
}

namespace anim
{
    enum AnimState {
        NONE,
        CHANT,              // case 1: silence -> sp3 -> sp2 -> sp1 -> sp0 -> default
        MUTE_CHANT,         // case 2: default -> sp0 -> sp1 -> sp2 -> sp3 -> silence
        FAST_CHANT,         // case 3: silence -> sp2 -> default
        FAST_MUTE_CHANT,    // case 4: default -> sp2 -> silence
        SHOUT,              // case 5: silence -> enter3 -> enter2 -> enter1 -> enter0
        MUTE_SHOUT,         // case 6: enter0 -> enter1 -> enter2 -> enter3 -> silence
        PLAYER_SHOUT,       // case 7: silence -> enter3 -> enter2 -> enter1 -> enter0 -> enter0 -> enter1 -> enter2 -> enter3 -> silence
        FAST_SHOUT,         // case 8: silence -> enter2 -> enter0
        FAST_MUTE_SHOUT,    // case 9: enter0 -> enter2 -> silence
        SHAME,              // case 10: any -> shame
        TOGGLE_CHANT        // case 11: toggle silence <-> default
    };

    enum CharacterType {
        PLAYER,
        CHORUS1,
        CHORUS2,
        CONDUCTOR
    };

    struct Character {
        int x, y;                     // 위치
        const char* currentFrame;     // 현재 프레임
        AnimState currentState;       // 현재 애니메이션 상태
        int frameIndex;               // 현재 프레임 인덱스
        bool isAnimating;             // 애니메이션 중인지 여부
        ULONGLONG lastAnimTick;       // 각 캐릭터별 애니메이션 타이머 추가
        ULONGLONG lastPlayPos;        // 노트 시작 시간
        CharacterType characterType;  // 캐릭터 타입
    };

    void InitCharacter(Character* character, int x, int y, 
                    const char* currentFrame, AnimState currentState, 
                    int frameIndex, bool isAnimating, CharacterType charactertype); //초기화 함수

    void StartGame();
    void DrawScreen();
    void DrawCharacter(int x, int y, const char* filename);
    void UpdateAnimation();
    void UpdateAnimation(Character*& character);
    void ResetState(Character*& character, bool isAnimating, AnimState currentState);
    void StartAnimation(Character*& character, AnimState state);
    bool IsShoutAnimating();

    void AssignState(Character*& character, note::Note*& note);

    Character*& GetCharacter(int num);

    void UpdateAIAnimation(Character*& character, note::Note*& note, int noteSize);
    bool AIAnimEnd(Character*& character, double duration);
    void Shame();
}