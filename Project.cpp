using namespace std;
#include<iostream>

class Product
{
private:
public:
    char* name;
    int timeToExp;
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
    Product(char* name, int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount, unsigned int location, char* note)
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
        Product(char* name, int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount, unsigned int location)
    {
        this->name = name;
        this->timeToExp = timeToExp;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->location = location;
    }
            Product(char* name, int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount)
    {
        this->name = name;
        this->timeToExp = timeToExp;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
    }
    void setLocation(unsigned int location)
    {
        this->location=location;
    }
    unsigned int getAmount()
    {
        return amount;
    }


};
Product* kokakola [2][2];
bool mirrorTable [2][2];

void FillMirrorTable()
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            mirrorTable[i][j] = false;
        }
    }
}
unsigned int SearchForFreeSpace(unsigned int spaceNeeded)
{
    unsigned int currentSpace;
    for(int i=0;i<2;i++)
    {
        currentSpace = 0;
        //За да сме сигурни, че продуктът ни е за един ред
        for(int j=0;j<2;j++)
        {
            if(mirrorTable[i][j] = false)
            {
                currentSpace++;
                if(currentSpace==spaceNeeded)
                {
                    return i*100+(j-spaceNeeded);
                }
            }
            else currentSpace = 0;
        }
    }

}
void PutTheProduct(unsigned int positionToPlaceOn,unsigned int spaceNeeded)
{
    for(int i=0;i<spaceNeeded;i++)
    {
        mirrorTable[positionToPlaceOn/100][positionToPlaceOn%100 + i] = true;
    }
}
void AddNewProduct(Product* newProduct)
{
    unsigned int spaceNeeded = newProduct->getAmount()/50;
    unsigned int positionToPlaceOn = SearchForFreeSpace(spaceNeeded);
    newProduct->setLocation(positionToPlaceOn);
    kokakola[positionToPlaceOn/100][positionToPlaceOn%100] = newProduct;
    PutTheProduct(positionToPlaceOn,spaceNeeded);

}


int main()
{
    FillMirrorTable();
    Product* kola  = new Product("kola",30,"30/4/20","koka-kola","0.5L",24,1001);
    Product* fanta  = new Product("fanta",30,"30/4/20","koka-kola","0.5L",12,1002);
    kokakola[0][0] = kola;
    kokakola[0][1] = fanta;
cout<<kokakola[0][1]->name<<endl;
};
