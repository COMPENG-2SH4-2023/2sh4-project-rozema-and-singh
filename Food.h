#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"


class Food
{
    private:
        
        objPosArrayList* foodBucket;

    public:
        
        Food();
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        void getFoodPos(objPos& returnPos);
};





#endif 
