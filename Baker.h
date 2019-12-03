#pragma once

#include <vector>

#include "Bun.h"

class Baker
{
public:
    //Static
    enum ActionType{EAT = 1, GIVE = 2, BAKE = 3};

    //Constructors | Destructors
    Baker();
    Baker(const Baker&);
    ~Baker();

    //Overloaded operations
    Baker& operator=(const Baker& a);

    //Functions
    void bakeBun(bool timeDependence = true);
    void eatBun();
    void giveBun(Baker& baker);

    //Getters
    int getSkill() const;
    int getHungry() const;
    int getExperience() const;
    int getBakingCooldown() const;
    const std::vector<Bun*>& getBuns() const;
    Bun* getLastBakedBun() const;
    bool havingBuns() const;
    bool isBaking() const;
    bool isBunBaked();

    //Setters
    void setSkill(const int skill);
    void setHungry(const int hungry);
    void setExperience(const int experience);
    void setBuns(std::vector<Bun*>& buns);
    void updateBakeCooldown();
    void rechargeCooldown();

    void addExperience(const int experience);

    //Output
    void printBuns();

private:
    //
    void setBakingCooldown(int coolDown);

    //Variables
    std::vector<Bun*> mBuns;
    int mSkill;
    int mHungry;
    int mExperience;

    int mBakingCooldown;
    bool mIsBaking;
    bool mIsBunBaked;
};
