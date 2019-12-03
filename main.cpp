#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

#include "Baker.h"
#include "Bun.h"

using namespace std;

const int MAX_ROUNDS = 25;
const int REQUIRED_WINS = 15;

const int MAX_PLANNED = 600;
const int MIN_PLANNED = 300;

const float EXP_PER_PLAN = 100.f;

#define SINGLE_TRAIN_LOG1

int singleTrain(Baker &first, Baker &second, int plannedJob){

    int currentJob = 0;

    for(int i = 0; i < MAX_ROUNDS; i++){
#ifdef SINGLE_TRAIN_LOG
        std::cout << "Round " << i << std::endl;
#endif

        first.updateBakeCooldown();
        second.updateBakeCooldown();

        if(first.isBunBaked()){
            currentJob += first.getLastBakedBun()->getTastiness();
        }

        if(second.isBunBaked()) {
            currentJob += second.getLastBakedBun()->getTastiness();
        }

        if(currentJob >= plannedJob){
#ifdef SINGLE_TRAIN_LOG
            std::cout << "Bakers won!" << endl;
#endif
            break;
        }

        if(!first.isBaking()){
            if(!first.havingBuns()){
                first.bakeBun();
            } else {
                int RAND_ACTION = rand() % 3 + 1;

                if(RAND_ACTION == Baker::ActionType::BAKE){
                    first.bakeBun();
                }
                if(RAND_ACTION == Baker::ActionType::GIVE){
                    first.giveBun(second);
                }
                if(RAND_ACTION == Baker::ActionType::EAT){
                    first.eatBun();
                }
            }
        }

        if(!second.isBaking()){
            if(!second.havingBuns()){
                second.bakeBun();
            } else {
                int RAND_ACTION = rand() % 3 + 1;

                if(RAND_ACTION == Baker::ActionType::BAKE){
                    second.bakeBun();
                }
                if(RAND_ACTION == Baker::ActionType::GIVE){
                    second.giveBun(first);
                }
                if(RAND_ACTION == Baker::ActionType::EAT){
                    second.eatBun();
                }
            }
        }

#ifdef SINGLE_TRAIN_LOG
        std::cout << "{First}: " << first.getHungry() << " " << first.getBakingCooldown() << std::endl;
        std::cout << "{Second}: " << second.getHungry() << " " << second.getBakingCooldown() << std::endl;

        std::cout << "Current job: " << currentJob << std::endl;
        std::cout << endl;
#endif
    }

    first.rechargeCooldown();
    second.rechargeCooldown();

    return currentJob;
}

int bake(Baker first, Baker second) {

    int allExperience = 0;
    int wins = 0;

    while(wins < REQUIRED_WINS)
    {
        int plannedJob = rand() % (MAX_PLANNED - MIN_PLANNED) + MIN_PLANNED;
        std::cout << "Planned buns: " << plannedJob << endl;
        std::cout << "Wins: " << wins << endl;

        int workedJob = singleTrain(first, second, plannedJob);
        int lastGatheredExperience = floor((float) workedJob / (float) plannedJob * EXP_PER_PLAN);
        allExperience += lastGatheredExperience;

        first.addExperience(lastGatheredExperience / 2 + 1);
        second.addExperience(lastGatheredExperience / 2 + 1);

        std::cout << "{First EXP and Skill}: " << first.getExperience() << " " << first.getSkill() << std::endl;
        std::cout << "{Second EXP and Skill}: " << second.getExperience() << " " << second.getSkill() << std::endl;

        if(workedJob > plannedJob) wins++;
    }

    return allExperience;
}

int main() {
    Baker first, second;

    for(int i = 0; i < 10; i++){
        first.bakeBun(false);
        second.bakeBun(false);
    }

    int gatheredExperience = bake(first, second);
    std::cout << "Gathered Exp = " << gatheredExperience << std::endl;

    while(first.havingBuns())
        first.eatBun();

    while(second.havingBuns())
        second.eatBun();


    return 0;
}