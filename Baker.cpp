#include <iostream>
#include <vector>

#include "Baker.h"
#include "Bun.h"

#define BAKER_DEBUG1

const int RAND_SKILL_MAX = 10;
const int RAND_SKILL_MIN = 2;

const int RAND_HUNGRY_MAX = 50;
const int RAND_HUNGRY_MIN = 25;

const int RAND_EXP_MAX = 100;
const int RAND_EXP_MIN = 50;

const int MAX_HUNGRY = 100;
const int MIN_HUNGRY = 0;

const int LEVEL_CAP_EXP = 300;
const int MIN_EXP = 0;

//Constructors | Destructors

Baker::Baker()
{
    mSkill = rand() % (RAND_SKILL_MAX - RAND_SKILL_MIN) + RAND_SKILL_MIN;
    mHungry = rand() % (RAND_HUNGRY_MAX - RAND_HUNGRY_MIN) + RAND_HUNGRY_MIN;
    mExperience = rand() % (RAND_EXP_MAX - RAND_EXP_MIN) + RAND_EXP_MIN;
    mBuns = std::vector<Bun*>();

    mBakingCooldown = 0;
    mIsBaking = false;
    mIsBunBaked = false;

#ifdef BAKER_DEBUG
    std::cout << "{Baker}: Default Baker constructor" << std::endl;
#endif

}

Baker::Baker(const Baker &a) {
    mSkill = a.getSkill();
    mHungry = a.getHungry();
    mExperience = a.getExperience();
    this->setBuns(const_cast< std::vector<Bun*>& >(a.getBuns()));

    mBakingCooldown = 0;
    mIsBaking = false;
    mIsBunBaked = false;

#ifdef BAKER_DEBUG
    std::cout << "{Baker}: Copy constructor" << std::endl;
#endif

}

Baker::~Baker()
{
    for(auto p : mBuns){
        delete p;
    }
    mBuns.clear();

#ifdef BAKER_DEBUG
    std::cout << "{Baker}: Destructor" << std::endl;
#endif

}

//Overloaded operations

Baker & Baker::operator=(const Baker& a)
{
    if (this == &a) {
        return *this;
    }

    mExperience = a.getExperience();
    mHungry = a.getHungry();
    mSkill = a.getSkill();
    mIsBaking = a.mIsBaking;
    this->setBuns(const_cast<std::vector<Bun*>& >(a.getBuns()));

#ifdef BAKER_DEBUG
    std::cout << "{Baker}: Overloaded operator=" << std::endl;
#endif

    return *this;
}

//Functions (actions)

void Baker::bakeBun(bool timeDependence)
{
    if (!timeDependence) {
        mBuns.push_back(new Bun());
        return;
    }

    setBakingCooldown((110 - this->getHungry()) / 10 + 2);

    mHungry -= rand() % 7 + 2;
    if (mHungry < MIN_HUNGRY) mHungry = MIN_HUNGRY;
    mIsBaking = true;

#ifdef BAKER_DEBUG
    std::cout << "Baker started to bake new bun!" << std::endl;
#endif

}

void Baker::eatBun()
{
    if(!havingBuns()) return;

    mHungry += rand() % 10 + 5;
    if(mHungry > MAX_HUNGRY) mHungry = MAX_HUNGRY;
    delete mBuns.back();
    mBuns.pop_back();
#ifdef BAKER_DEBUG
    std::cout << "Baker ate last baked bun!" << std::endl;
#endif

}

void Baker::giveBun(Baker & baker)
{
    if (this->havingBuns()) return;

    baker.mBuns.push_back(this->mBuns.back());
    this->mBuns.pop_back();

    this->mHungry -= rand() % 3 + 1;
    if (this->mHungry < MIN_HUNGRY) this->setHungry(MIN_HUNGRY);
#ifdef BAKER_DEBUG
    std::cout << "Baker gave last bun to other baker!" << std::endl;
#endif

}

//Getters

int Baker::getSkill() const
{
    return mSkill;
}

int Baker::getHungry() const
{
    return mHungry;
}

int Baker::getExperience() const
{
    return mExperience;
}

int Baker::getBakingCooldown() const
{
    return mBakingCooldown;
}

const std::vector<Bun*>& Baker::getBuns() const
{
    return mBuns;
}

Bun* Baker::getLastBakedBun() const
{
    if(!havingBuns()) return nullptr;
    return getBuns().back();
}

bool Baker::havingBuns() const
{
    return !getBuns().empty();
}

bool Baker::isBaking() const{
    return mIsBaking;
}

bool Baker::isBunBaked() {
    if(mIsBunBaked){
        mIsBunBaked = false;
        return true;
    }
    return false;
}

//Setters

void Baker::setSkill(const int skill)
{
    mSkill = skill;
}

void Baker::setHungry(const int hungry)
{
    mHungry = hungry;
}

void Baker::setExperience(const int experience)
{
    mExperience = experience;
}

void Baker::setBuns(std::vector<Bun*>& buns)
{
    for(auto p : mBuns){
        delete p;
    }
    mBuns.clear();
    for (auto p : buns) {
        mBuns.push_back(new Bun(*p));
    }
}

void Baker::setBakingCooldown(int cooldown)
{
    mBakingCooldown = cooldown;
}

void Baker::addExperience(const int experience)
{
    mExperience += experience;
    if(mExperience > LEVEL_CAP_EXP){
        mSkill++;
        mExperience = mExperience % LEVEL_CAP_EXP;
    }
}


void Baker::rechargeCooldown()
{
    mBakingCooldown = 0;
}


void Baker::updateBakeCooldown()
{

    if(!mIsBaking) return;

    if(mBakingCooldown > 0){
        mBakingCooldown--;
        return;
    }

    mBuns.push_back(new Bun());
    mIsBaking = false;
    mIsBunBaked = true;
}

//Print

void Baker::printBuns()
{
    std::cout << "Buns of baker: " << std::endl;
    for (auto p : mBuns) {
        p->printBun();
    }
}