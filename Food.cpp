#include "MacUILib.h"
#include "Player.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

Food::Food()
{
    foodBucket = new objPosArrayList();
    
}

Food::~Food()
{
    delete[]foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int alreadyChosen, candidateX, candidateY;
    objPos tempPos;
    objPos foodPos;
    
    for(int z = 0; z<2; z++){
        alreadyChosen = 1;
        while(alreadyChosen)
        {
            alreadyChosen = 0;


            candidateX = (rand() % (30 - 3)) + 1; // generates a random position for x & y that are in a valid range
            candidateY = (rand() % (15 -3)) + 1;
            for (int i = 0; i < blockOff->getSize(); i++){
                
                blockOff->getElement(tempPos, i);
                if((candidateX == tempPos.x) && (candidateY == tempPos.y)) //checks if chosen position is on the character
                {
                    alreadyChosen = 1;
                    
                }
            }
            if(!alreadyChosen)
            {
                foodPos.x = candidateX;
                foodPos.y = candidateY;
                foodPos.symbol = '$';
                foodBucket -> insertTail(foodPos);
            }
        }
    }
}

void Food::getFoodPos(objPos& returnPos)
{
    
    foodBucket -> getHeadElement(returnPos);

}