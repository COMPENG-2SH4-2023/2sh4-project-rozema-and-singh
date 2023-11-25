#include "GameMechs.h"
#include "MacUILib.h"
#include "Player.h"


GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    objPos food;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    
    boardSizeX = boardX;
    boardSizeY = boardY;

    objPos food;

}

// do you need a destructor?, Not now



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() == 1) {
        input = MacUILib_getChar();
   }
   return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::generateFood(objPos blockOff)
{
    int alreadyChosen, candidateX, candidateY;

    
        alreadyChosen = 1;
        while(alreadyChosen)
        {
            alreadyChosen = 0;


            candidateX = (rand() % (getBoardSizeX() - 3)) + 1; // generates a random position for x & y that are in a valid range
            candidateY = (rand() % (getBoardSizeY() -3)) + 1;


            if((candidateX == blockOff.x) && (candidateY == blockOff.y)) //checks if chosen position is on the character
            {
                alreadyChosen = 1;
                
            }
            
            if(!alreadyChosen)
            {
                foodPos.x = candidateX;
                foodPos.y = candidateY;
                foodPos.symbol = '$';
            }
        }
    
    
}

void GameMechs::getFoodPos(objPos& returnPos)
{
    
    returnPos = foodPos;


}