#include "GameMechs.h"
#include "MacUILib.h"
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    
    boardSizeX = boardX;
    boardSizeY = boardY;

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


