#include <cstdlib>
#include <iostream>

#include "Bun.h"

const int RAND_TASTY_MAX = 100;
const int RAND_TASTY_MIN = 0;

//Static variables

int Bun::bunCounter = 0;

int Bun::getBunCount()
{
    return bunCounter;
}

//Static functions

Bun & Bun::compareBun(Bun & a, Bun & b)
{
    return (a.getTastiness() - b.getTastiness() > 0 ? (a) : (b));
}

//Constructors | Destructors

Bun::Bun()
{
    mName = RAND_NAMES[rand() % (sizeof(RAND_NAMES) / sizeof(RAND_NAMES[0]))];
    mTastiness = rand() % (RAND_TASTY_MAX - RAND_TASTY_MIN) + RAND_TASTY_MIN;

    bunCounter++;

#ifdef BUN_DEBUG
    std::cout << "{Bun}: Default constructor" << std::endl;
#endif

}

Bun::Bun(const Bun & bun)
{
    mTastiness = bun.mTastiness;
    mName = bun.mName;

    bunCounter++;

#ifdef BUN_DEBUG
    std::cout << "{Bun}: Copy constructor" << std::endl;
#endif

}

Bun::~Bun()
{

#ifdef BUN_DEBUG
    std::cout << "{Bun}: Destructor" << std::endl;
#endif

}

//Overloaded operations

Bun & Bun::operator=(const Bun & a)
{
    if (this == &a) {
        return *this;
    }

    this->setName(a.getName());
    this->setTastiness(a.getTastiness());

#ifdef BUN_DEBUG
    std::cout << "{Bun}: Overloaded operator=" << std::endl;
#endif

    return *this;
}

//Getters

int Bun::getTastiness() const
{
    return mTastiness;
}

std::string Bun::getName() const
{
    return mName;
}

// Setters

void Bun::setName(const std::string name)
{
    mName = name;
}

void Bun::setTastiness(const int tastiness)
{
    mTastiness = tastiness;
}

//Print
void Bun::printBun()
{
    std::cout << "Name = " << mName << std::endl;
    std::cout << "Tastiness = " << mTastiness << std::endl;
}