// Anim.h 수정
#pragma once
#define MAX_CHARACTER_SIZE 256

namespace anim
{
    enum AnimState {
        NONE,
        CHANT,        // case 1: silence -> sp3 -> sp2 -> sp1 -> sp0 -> default
        MUTE_CHANT,   // case 2: default -> sp0 -> sp1 -> sp2 -> sp3 -> silence
        SHOUT,        // case 3: silence -> enter3 -> enter2 -> enter1 -> enter0
        MUTE_SHOUT,   // case 4: enter0 -> enter1 -> enter2 -> enter3 -> silence
        SHAME         // case 4: any -> shame -> silence
    };

    struct Character {
        int x, y;                     // 위치
        const char* currentFrame;     // 현재 프레임
        AnimState currentState;       // 현재 애니메이션 상태
        int frameIndex;               // 현재 프레임 인덱스
        bool isAnimating;             // 애니메이션 중인지 여부
    };

    void InitCharacter(Character* character, int x, int y, 
                    const char* currentFrame, AnimState currentState, 
                    int frameIndex, bool isAnimating); //초기화 함수

    void StartGame();
    void DrawScreen();
    void DrawCharacter(int x, int y, const char* filename);
    void UpdateAnimation();
    void ResetState(Character* character, bool isAnimating, AnimState currentState);
    void StartAnimation(int characterIndex, AnimState state);
    bool IsAnimating();
}