#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//Global Pointer Declarations
GameMechs* pGameMechs = NULL;
Player* pPlayer = NULL;
Food* pFood = NULL;


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
    
    //Game Mechanics Creation
    pGameMechs = new GameMechs(30, 15);

    //Food Creation
    pFood = new Food(pGameMechs);

    //Player Creation
    pPlayer = new Player(pGameMechs, pFood);
    objPosArrayList* snakeList;
    snakeList = (pPlayer->getPlayerPos());
    

    //Food Generation
    pFood->generateFood(snakeList);
   
}

void GetInput(void)
{
   
    //Inside of GameMechs.cpp
   
}

void RunLogic(void)
{

    //Movement
    pPlayer->updatePlayerDir();
    pGameMechs->clearInput();//Nulls current input - No double processing
    pPlayer->movePlayer();


    //Check for player collision
    if(pPlayer->checkSelfCollision()){
    pGameMechs->setExitTrue();
    }
   
    
}
void DrawScreen(void)
{
    //Player Body List
    objPosArrayList* snakeList;
    snakeList = (pPlayer->getPlayerPos());

    //Food Piece List
    objPosArrayList* foodList;
    foodList = (pFood->getFoodPos());

    //Temp Player and Food positions
    objPos foodPos;
    objPos bodyPos;
    
    bool piece_placed = false;

   
    MacUILib_clearScreen();
        for (int i = 0; i < pGameMechs->getBoardSizeY(); i++) {//Y-axis
            for (int j = 0; j < pGameMechs->getBoardSizeX(); j++) {//X-axis

                piece_placed = false;
                
                //Border display
                if ((i == 0) || (i == pGameMechs->getBoardSizeY() - 1)) {
                    MacUILib_printf("#");
                }
                else if ((j == 0) || (j == pGameMechs->getBoardSizeX() - 1)){
                    MacUILib_printf("#");
                }

                //Special character
                else {

                    //Iterate through player list
                    for (int l = 0; l < (*snakeList).getSize(); l++){
                        (*snakeList).getElement(bodyPos, l);
                        if ((i == bodyPos.y) && (j == bodyPos.x)) {
                            MacUILib_printf("%c", bodyPos.symbol);

                            piece_placed = true;//Don't place space and don't check food
                            break;
                        }
                    }

                    if (piece_placed == false) {//If a player character hasn't been placed
                    
                    //Iterate through food list
                    for (int l = 0; l < 5; l++){
                        (*foodList).getElement(foodPos, l);
                        if ((i == foodPos.y) && (j == foodPos.x)) {
                            MacUILib_printf("%c", foodPos.symbol);

                            piece_placed = true;//Don't place space
                            break;
                        }
                    }
                    }

                    if (piece_placed == false) {//Add space
                        MacUILib_printf(" ");
                    }
                    
                }

                }
            
        
            cout << endl;
    
    }

    //Game info
    cout << "Score: " << (pPlayer->getScore()) << endl; 
    cout << endl << "Controls: [w] -> Up, [s] -> Down, [a] -> Left, [d] ->Right" << endl;
    cout << "Food Guide:" << endl << "$ -> Score + 1, Body Length + 1" << endl << "2 -> Score + 4, Body Length + 2" << endl << "- -> Score + 1, Body Length - 1 " << endl;
    cout << "Press [esc] to exit. Try not to run into yourself!" << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    
    MacUILib_clearScreen(); 

    //Ending messages
    if(pPlayer->checkSelfCollision()){//Player died
        cout << "Game Over! :(" << endl;
        cout << "Final score: " << pPlayer->getScore() << endl;

        //Acheivement messsages
        if(pPlayer->getScore() <= 10) {
        cout << "Maybe practice a bit more... or a lot more!" << endl;
        }
        else if(pPlayer->getScore() <= 50) {
            cout << "You're getting the hang of it!" << endl;
        }
        else{
            cout << "What a pro!" << endl;
        }

    }
    else {//Player hit escape key
        cout << "Game ending..." << endl;
        cout << "Final score: " << pPlayer->getScore() << endl;
        cout << "Thanks for playing!" << endl;
    }
    
    
    MacUILib_uninit();

    //Free all variables on heap
    delete[] pPlayer;
    delete[] pGameMechs; 
    delete[] pFood;
}

