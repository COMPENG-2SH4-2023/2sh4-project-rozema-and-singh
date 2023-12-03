#include "MacUILib.h"
#include "Player.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

Food::Food(GameMechs* thisGMRef)
{
    //Game mechanics ref
    mainGameMechsRef = thisGMRef;

    //Food object list
    foodBucket = new objPosArrayList();

    //Generic Food Objects
    objPos temp = {0,0,'s'};
    foodBucket->insertHead(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);

    
}

Food::~Food()
{
    delete[]foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int alreadyChosen, candidateX, candidateY;

    //Temp Player Object
    objPos playerPos;

    //Temp Food Objects
    objPos foodPos;
    objPos otherFoodPos;
    

    //Generate 5 distinct food objects
    for(int z = 0; z < 5; z++){
        
        alreadyChosen = 1;
        while(alreadyChosen)
        {
            alreadyChosen = 0;


            //Generates a random position for x & y that are in a valid range
            candidateX = (rand() % (mainGameMechsRef->getBoardSizeX() - 3)) + 1; 
            candidateY = (rand() % (mainGameMechsRef->getBoardSizeY() -3)) + 1;


            //Check if generated position is taken by player object
            for (int i = 0; i < blockOff->getSize(); i++){
                
                blockOff->getElement(playerPos, i);

                if((candidateX == playerPos.x) && (candidateY == playerPos.y))
                {
                    alreadyChosen = 1;//Keep generating
                    break;
                }
            }

            //Check if generated position is already taken by other food
             for (int j= 0; j < z; j++) {

                foodBucket->getElement(otherFoodPos, j);

                if ((otherFoodPos.x == candidateX) && (otherFoodPos.y == candidateY)){
                    alreadyChosen = 1;//Keep generating
                    break;
                }
            }


            if(!alreadyChosen)
            {
                //foodBucket->getElement(tempPos2, z);
                foodPos.x = candidateX;
                foodPos.y = candidateY;
                if (z == 1) {
                    foodPos.symbol = '2';
                }
                else if (z == 3) {
                    foodPos.symbol = '-';
                }
                else {
                foodPos.symbol = '$';
                }
                foodBucket->insertTail(foodPos);
                foodBucket->removeHead();
                
            }
        }
    }
}



objPosArrayList* Food::getFoodPos()
{
    
    return foodBucket;

}