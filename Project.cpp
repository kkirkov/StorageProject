using namespace std;
#include<iostream>

class Product
{
private:
    char* name;
    unsigned int timeToExp;
    char* dateOfEntry;
    char* supplier;
    char* unit;
    double amount;
    unsigned int location;
    char* note;
public:
    Product()
    {

    }
    Product(char* name, unsigned int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount, unsigned int location, char* note)
    {
        this->name = name;
        this->timeToExp = timeToExp;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->location = location;
        this->note = note;
    }

};


int main()
{

};
