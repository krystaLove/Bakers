#pragma once

#include <string>

const std::string RAND_NAMES[] = {
        "Bun with meat",
        "Bun with potato",
        "Bun with cot. cheese and musshrooms"
};

class Bun
{
public:

    //Static variables
    static int bunCounter;

    //Constructors
    Bun();
    Bun(const Bun&);
    ~Bun();

    //Overload
    Bun& operator=(const Bun& a);

    //Static functions
    static int getBunCount();
    static Bun& compareBun(Bun& a, Bun& b);

    //Getters
    int getTastiness() const;
    std::string getName() const;

    //Setters
    void setName(const std::string);
    void setTastiness(const int);

    //Output
    void printBun();

private:

    //Variables
    std::string mName;
    int mTastiness;
};