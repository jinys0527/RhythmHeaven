#include "GameManager.h"

int main()
{   
    static LARGE_INTEGER start, end; // QPC

    loop:

    game::SetUp();

    game::ShowTitle();
    
    game::StartTutorial(start, end);

    game::StartGame(start, end);

    game::ShowEnding();
   
    game::ShowRanking();

    game::EndGame();
    
    goto loop;

    return 0;
}