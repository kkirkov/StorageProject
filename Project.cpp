using namespace std;
#include<iostream>
#include <math.h>
#include<ctime>
#include<time.h>
#include<fstream>
#include<string>
class Product
{
private:
public:
    char* name;
    int timeToExp;
    time_t dateOfEntry;
    char* supplier;
    char* unit;
    double amount;
    unsigned int location;
    char* note;
public:
    Product()
    {

    }
    Product(char* name, int timeToExp,time_t dateOfEntry, char* supplier, char* unit, double amount, char* note)
    {
        this->name = name;
        this->timeToExp = timeToExp;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->note = note;
    }

    Product(char* name, int timeToExp,time_t dateOfEntry, char* supplier, char* unit, double amount)
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
    void Print()
    {
        struct tm dateOfEntry;
        dateOfEntry = *localtime(&(this->dateOfEntry));
        cout<<"Name:"<<name<<" TimeToExpire:"<<timeToExp<<" day:"<<dateOfEntry.tm_mday<<" supplier:"<<supplier<<" unit:"<<unit<<" amount:"<<amount<<" note:"<<note<<endl;
    }


};
const int sizeOfShelf = 10;
Product* kokakola[sizeOfShelf][sizeOfShelf][sizeOfShelf];
bool mirrorTable[sizeOfShelf][sizeOfShelf][sizeOfShelf];

void FillBothTables()
{
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                mirrorTable[i][j][k] = false;
                kokakola[i][j][k] = nullptr;

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
                {
                    cout<<"There is a product at: "<<i<<" "<<j<<" "<<k<<endl;
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
                       return i*pow(sizeOfShelf,2)+j*sizeOfShelf+(k-spaceNeeded+1);
                    }
                }
                else currentSpace = 0;
            }
        }
    }

}

//Създаваме продукт и го поставяме на първото свободно място, на което ще се събере
void AddNewProduct(char* name, int timeToExp, char* supplier, char* unit, double amount)
{
    time_t now;
    now=time(nullptr);
    cout<<"Creating and adding a new Product"<<endl;
    Product* newProduct = new Product(name,timeToExp,now,supplier,unit,amount);
    unsigned int spaceNeeded = newProduct->getAmount()/50+1;
    unsigned int positionToPlaceOn = SearchForFreeSpace(spaceNeeded);
    newProduct->setLocation(positionToPlaceOn);
    kokakola[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf] = newProduct;
    for(int i=0;i<spaceNeeded;i++)
    {
        //cout<<positionToPlaceOn/pow(sizeOfShelf,2)<<" "<<positionToPlaceOn/sizeOfShelf<<" "<<positionToPlaceOn%sizeOfShelf + i<<endl;
        mirrorTable[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf + i] = true;
    }

}

//премахваме определено количество от продукт
void RemoveSetAmountOfProduct(char* removeName, double removeAmount)
{
    int shortestTimeToExp=10000;
    cout<<shortestTimeToExp<<endl;
    unsigned int positionOfShortest;
    //Откриваме най-краткосрочния продукт от този вид
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(kokakola[i][j][k]!=nullptr)
                {
                    if(kokakola[i][j][k]->name==removeName&&kokakola[i][j][k]->timeToExp<shortestTimeToExp)
                    {
                    positionOfShortest = kokakola[i][j][k]->location;
                    shortestTimeToExp = kokakola[i][j][k]->timeToExp;
                    }
                }

            }
        }
    }
    if(shortestTimeToExp!=10000)
    {
        if(kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->amount>removeAmount)
        {
            //Взимаме част от най-краткосрочния продукт
            kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->amount = kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->amount - removeAmount;
        }
        else
        {
            //Взимаме целия най-краткосрочен продукт, защото ни трябва точно толкова или повече
            unsigned int howBigIsThis = kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->amount/50+1;
            double leftToGet =removeAmount - kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->amount;
            for(int p=0;p<howBigIsThis;p++)
            {
                mirrorTable[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf+p]=false;
            }
            delete kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf];
            kokakola[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf] = nullptr;
            //Търсим си останалото
            RemoveSetAmountOfProduct(removeName,leftToGet);
        }
    }
    else {cout<<"Amount too low!"<<endl;}
}

int main()
{
    FillBothTables();

 //   AddNewProduct("kola",10,"koka-kola","0.5L",10);
  //  AddNewProduct("fanta",30,"koka-kola","0.5L",12);
  //  AddNewProduct("kola",20,"koka-kola","0.5L",20);


time_t now;

struct tm nowLocal;
now=time(nullptr);
nowLocal = *localtime(&now);
cout<< nowLocal.tm_mday;
/*
ofstream writeStream;
myfile.open("newfile.txt");
myfile
*/
ifstream readStream;
readStream.open("newfile.txt");
if(readStream.fail())
{
    cerr<<"Error opening file!"<<endl;
    exit(1);
}
char* name;
int timeToExp;
char* supplier;
char* unit;
double amount;
while(!readStream.eof())
{
    readStream>>name;
    cout<<name<<endl;
    readStream>>timeToExp>>supplier>>unit>>amount;
    cout<<name<<timeToExp<<supplier<<unit<<amount<<endl;
//    AddNewProduct(name,timeToExp,supplier,unit,amount);
}


    PrintMirrorTable();
    RemoveSetAmountOfProduct("kola",32);
    PrintMirrorTable();
    kokakola[0][0][1]->Print();




return 0;
};
