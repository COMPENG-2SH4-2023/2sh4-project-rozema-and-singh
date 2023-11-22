#include "Player.h"

using namespace std;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    movement = STILL;

    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    //returnPos = playerPos;-changed
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    
    
    char BTNpressed = mainGameMechsRef -> getInput();

    switch(BTNpressed) 
    {                      
        case 27:  
            mainGameMechsRef -> setExitTrue();
            break;
            
        case 'W':
        case 'w':
                
            if(movement !=  DOWN || movement ==  STILL) 
            {
                movement =  UP;
                
                   
            }    
            break;
            
        case 'S':
        case 's':
                
            if(movement != UP || movement == STILL) 
            {
                movement = DOWN;
                
            }
            break;
            
        case 'A':
        case 'a':
            if(movement != RIGHT || movement == STILL) 
            {
                movement = LEFT; 
                
                    
            } 
            break;
            
        case 'D':
        case 'd':
            if(movement != LEFT || movement == STILL) 
            {
                movement = RIGHT;
                
                   
            } 
            break;
            
        default:
                
            break;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    switch(movement) 
        {
            case UP: 
                playerPos.y--;
                //moveCount++;
                break;
                
            case DOWN:
                playerPos.y++;
                //moveCount++;
                break;
                
            case LEFT:
                playerPos.x--;
                //moveCount++;
                break;
                
            case RIGHT:
                playerPos.x++;
                //moveCount++;
                break;
                
            case STILL:
                break;
            }
    
    if(playerPos.x >= (mainGameMechsRef -> getBoardSizeX() - 1))
    {
        playerPos.x = 1;

    }
    else if (playerPos.x <= 0)
    {
        playerPos.x = (mainGameMechsRef -> getBoardSizeX() - 2);

    }
    else if(playerPos.y >= (mainGameMechsRef -> getBoardSizeY() - 1))
    {
        playerPos.y = 1;
    }
    else if(playerPos.y <= 0)
    {
        playerPos.y = (mainGameMechsRef -> getBoardSizeY() - 2);
    }

    
}

