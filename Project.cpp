using namespace std;
#include<iostream>
#include <math.h>

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
    Product(char* name, int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount, char* note)
    {
        this->name = name;
        this->timeToExp = timeToExp;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->note = note;
    }

            Product(char* name, int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount)
    {
        this->name = name;
        this->timeToExp = timeToExp;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->note = "No note set";
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
const int sizeOfShelf = 10;
Product* kokakola[sizeOfShelf][sizeOfShelf][sizeOfShelf];
bool mirrorTable[sizeOfShelf][sizeOfShelf][sizeOfShelf];

void FillMirrorTable()
{
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                mirrorTable[i][j][k] = false;

            }
        }
    }
}
void PrintMirrorTable()
{
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(mirrorTable[i][j][k])
            {cout<<"There is a product at: "<<"i"<<i<<" j"<<j<<endl;
            }
            }
        }
    }
}
unsigned int SearchForFreeSpace(unsigned int spaceNeeded)
{
    cout<<"WE ARE SEARCHING"<<endl;
    unsigned int currentSpace;
    for(int i=0;i<sizeOfShelf;i++)
    {
        currentSpace = 0;
        //За да сме сигурни, че продуктът ни е за един ред
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(mirrorTable[i][j][k] == false)
                {
                    currentSpace++;
                    if(currentSpace==spaceNeeded)
                    {
                        cout<<"space found at: "<<i*pow(sizeOfShelf,2)+j*sizeOfShelf+(k-spaceNeeded+1)<<endl;
                        return i*pow(sizeOfShelf,2)+j*sizeOfShelf+(k-spaceNeeded+1);
                    }
                }
                else currentSpace = 0;
            }
        }
    }

}
void PutTheProduct(unsigned int positionToPlaceOn,unsigned int spaceNeeded)
{
    for(int i=0;i<spaceNeeded;i++)
    {
        cout<<positionToPlaceOn/pow(sizeOfShelf,2)<<" "<<positionToPlaceOn/sizeOfShelf<<" "<<positionToPlaceOn%sizeOfShelf + i<<endl;
        mirrorTable[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf + i] = true;
    }
}
void AddNewProduct(Product* newProduct)
{
    cout<<"AddNewProduct"<<endl;
    unsigned int spaceNeeded = newProduct->getAmount()/50+1;
    unsigned int positionToPlaceOn = SearchForFreeSpace(spaceNeeded);
    newProduct->setLocation(positionToPlaceOn);
    kokakola[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf] = newProduct;
    PutTheProduct(positionToPlaceOn,spaceNeeded);

}
void AddNewProduct(char* name, int timeToExp,char* dateOfEntry, char* supplier, char* unit, double amount)
{
    cout<<"Creating and adding a new Product"<<endl;
    Product* newProduct = new Product(name,timeToExp,dateOfEntry,supplier,unit,amount);
    unsigned int spaceNeeded = newProduct->getAmount()/50+1;
    unsigned int positionToPlaceOn = SearchForFreeSpace(spaceNeeded);
    newProduct->setLocation(positionToPlaceOn);
    kokakola[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf] = newProduct;
    PutTheProduct(positionToPlaceOn,spaceNeeded);

}

int main()
{
    FillMirrorTable();
    AddNewProduct("kola",30,"30/4/20","koka-kola","0.5L",24);
    AddNewProduct("fanta",30,"30/4/20","koka-kola","0.5L",12);
   // PrintMirrorTable();
    //PutTheProduct(0000,1);
    PrintMirrorTable();
    PrintMirrorTable();
cout<<kokakola[0][0][1]->name<<endl;
};
