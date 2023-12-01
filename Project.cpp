#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
/*Notes: Currently have a fixed number of snake objects/no collision*/
//Move changes into player class//
GameMechs* pGameMechs = NULL;
Player* pPlayer = NULL;//Localize?
Food* pFood = NULL;
//objPosArrayList* snakeList = NULL;

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

    pFood = new Food();

    pPlayer = new Player(pGameMechs, pFood);

    

    objPosArrayList* snakeList;
    //pPlayer->getPlayerPos(snakeList);
    

    objPos tempPos;//Make into a class for above and beyond

    snakeList = (pPlayer->getPlayerPos());

    (*snakeList).getHeadElement(tempPos);
    pFood->generateFood(snakeList);
    
    //snakeList.insertHead(tempPos);

    objPos tempPos2(tempPos.x, tempPos.y-1, tempPos.symbol);
    (*snakeList).insertTail(tempPos2);

    objPos tempPos3(tempPos2.x, tempPos2.y-1, tempPos2.symbol);
    (*snakeList).insertTail(tempPos3);
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

    //objPosArrayList snakeList;//Make into a class for above and beyond
    //objPos tempPos;
    //pPlayer->getPlayerPos(snakeList);
        

   /* snakeList.insertHead(tempPos);
    snakeList->removeTail();*/
    
}
void DrawScreen(void)
{
    objPos tempPos;
    objPosArrayList* snakeList;
    snakeList = (pPlayer->getPlayerPos());

    objPos foodPos;
    int i,j;
    pFood->getFoodPos(foodPos);
    bool body = false;

    objPos TPos;
    (*snakeList).getHeadElement(TPos);

    objPos bodyPos;
    MacUILib_clearScreen();
        for (i = 0; i < pGameMechs->getBoardSizeY(); i++) {
            for (j = 0; j < pGameMechs->getBoardSizeX(); j++) {
                
                body = false;
                
                if ((i == 0) || (i == pGameMechs->getBoardSizeY() - 1)) {//Game board
                    cout << "#";
                }
                else if ((j == 0) || (j == pGameMechs->getBoardSizeX() - 1)){//Game board - move to fix border issue
                    cout << "#";
                }
        

                else if ((i == foodPos.y) && (j == foodPos.x)) {//Insert Food
                    MacUILib_printf("%c", foodPos.symbol);
                }

                else if ((i == TPos.y) && (j == TPos.x)) {//Insert Food
                    MacUILib_printf("%c", TPos.symbol);
                }

                else {//If nothing else should be added
                    for (int l = 0; l < (*snakeList).getSize(); l++){
                        (*snakeList).getElement(bodyPos, l);
                        if ((i == bodyPos.y) && (j == bodyPos.x)) {
                            MacUILib_printf("%c", bodyPos.symbol);

                            body = true;//Caused an issue with the border
                            //l = snakeList.getSize();
                        }
                    }
                    if (body == false) {
                        cout << " ";
                    }
                    
                }

                }
            
        
            cout << endl;
    
    }
    cout << "Score: " << (snakeList->getSize() - 1) << endl; 
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    
    MacUILib_clearScreen();    
    MacUILib_uninit();

    delete[] pPlayer;
    delete[] pGameMechs; //delete list
    delete[] pFood;
}
/*
Potential additions for i1 (may be later iterations instead):
-Different end messages
-displaying coordinates
*/
