#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000


GameMechs* pGameMechs = NULL;
Player* pPlayer = NULL;//Localize?

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(pGameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    pGameMechs = new GameMechs(30, 15);


    pPlayer = new Player(pGameMechs);

    
    
}

void GetInput(void)
{
   
    //Empty
   
}

void RunLogic(void)
{
    

    pPlayer->updatePlayerDir();
    pGameMechs->clearInput();//Nulls current input
    

    pPlayer->movePlayer();
    
}

void DrawScreen(void)
{
    objPos tempPos;
    pPlayer->getPlayerPos(tempPos);

    int i,j;

    MacUILib_clearScreen();
        for (i = 0; i < pGameMechs->getBoardSizeY(); i++) {
            for (j = 0; j < pGameMechs->getBoardSizeX(); j++) {
                if ((i == 0) || (i == pGameMechs->getBoardSizeY() - 1)) {//Game board
                    cout << "#";
                }
                else if ((j == 0) || (j == pGameMechs->getBoardSizeX() - 1)){//Game board
                    cout << "#";
                }
                else if ((i == tempPos.y) && (j == tempPos.x)) {//Insert Player
                    MacUILib_printf("%c", tempPos.symbol);
                }// Don't have player position yet

                else {//If nothing else should be added
                    cout << " ";
                }

                }
            
        
            cout << endl;
    
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete[] pPlayer;
    delete[] pGameMechs; 
    MacUILib_uninit();
}
/*
Potential additions for i1 (may be later iterations instead):
-Different end messages
-displaying coordinates
*/
