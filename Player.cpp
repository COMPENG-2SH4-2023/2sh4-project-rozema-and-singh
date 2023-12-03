#include "Player.h"
#include "Food.h"
#include <stdio.h>

using namespace std;

Player::Player(GameMechs* thisGMRef, Food* pFood)
{

    //Other class references
    mainGameMechsRef = thisGMRef;
    foodRef = pFood;

    //Seperate score variable for bonus
    score = 0;

    //Enumeration State for FSM Movement
    movement = STILL;

    //Player object List
    playerPosList = new objPosArrayList();
    
    //First Head Object
    objPos temp;
    temp.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, 'O');
    playerPosList->insertHead(temp);
    
    //Improves Random Generation
    srand(time(NULL));
    
}


Player::~Player()
{
    // delete any heap members here
    delete[] playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list

    return  playerPosList;//Returns obj pos list
}

void Player::updatePlayerDir()
{
    
    //Check if there is an input to be processed
    char BTNpressed = mainGameMechsRef -> getInput();

    //Processes input
    switch(BTNpressed) 
    {                      
        case 27://Escape Key  
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

    //Get first player element
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);

    //--Movement Process--
    switch(movement) 
        {
            case UP: 
                playerPos.y--;
                break;
                
            case DOWN:
                playerPos.y++;
                break;
                
            case LEFT:
                playerPos.x--;
                break;
                
            case RIGHT:
                playerPos.x++;
                break;
                
            case STILL:
                break;
            }
    
    //Wrap around Logic
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

    //Create the illusion of movement
    playerPosList->insertHead(playerPos);
    playerPosList->removeTail();


    //-- Collision Detection --

    //List of food positions
    objPosArrayList* foodPosL;
    foodPosL = (foodRef->getFoodPos());


    bool collision = false;
    int num_growth = 1;
    objPos foodPos;
    
    for (int i = 0; i < 5; i ++){
        foodPosL->getElement(foodPos, i);
        
        //Detect a collision
        if (((playerPos.x == foodPos.x) && (playerPos.y == foodPos.y))) {
            
            //Special Character Features
            if (foodPos.symbol == '2') {
                num_growth = 2;//Adds 2 snake characters
                score += 3;//Adds an additional 3 points
            }
            if (foodPos.symbol == '-') {
                num_growth = 0;

                if (playerPosList->getSize() > 1) {//Prevents player from deleting themselves
                playerPosList->removeTail();
                }
            }

            //Increase Player Length based on Character Colelcted
            for (int w = 0; w < num_growth; w++  ) {
            
                switch(movement) 
            {
                case UP: 
                    playerPos.y--;
                    break;
                    
                case DOWN:
                    playerPos.y++;
                    break;
                    
                case LEFT:
                    playerPos.x--;
                    break;
                    
                case RIGHT:
                    playerPos.x++;
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
        
            playerPosList->insertHead(playerPos);
        }

            //Re-gen Food Positons
            score += 1;
            foodRef->generateFood(playerPosList);
            break;
        }        
   }

   

   

}

    //suicide/self-collision check
bool Player::checkSelfCollision() {

    int size = playerPosList->getSize();
    objPos playerHead;
    objPos bodyPart;
    playerPosList->getHeadElement(playerHead);
    
    //Compare Head position to rest of body
    for (int i = 1; i < size; i++) {
        playerPosList->getElement(bodyPart, i);
        if ((playerHead.x == bodyPart.x) && (playerHead.y == bodyPart.y)) {
            return true;
        }
    }
    return false;
}

    //Used for bonus
int Player::getScore() {
    return score;
}
