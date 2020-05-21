using namespace std;
#include<iostream>
#include <math.h>
#include<ctime>
#include<time.h>
#include<fstream>
#include<string>
///size of the 3d array.
const int sizeOfShelf = 10;
///3d array that shows us which places are free.
bool mirrorTable[sizeOfShelf][sizeOfShelf][sizeOfShelf];

class Product
{
private:
    string name;
    int expDate;
    time_t dateOfEntry;
    string supplier;
    string unit;
    int amount;
    unsigned int location;
    string note;
public:
    Product()
    {

    }
    ///constructor with note.
    Product(string name, int expDate, time_t dateOfEntry, string supplier, string unit, int amount, string note)
    {
        this->name = name;
        this->expDate = expDate;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->note = note;
    }
    ///constructor.
    Product(string name, int expDate, time_t dateOfEntry, string supplier, string unit, int amount)
    {
        this->name = name;
        this->expDate = expDate;
        this->dateOfEntry = dateOfEntry;
        this->supplier = supplier;
        this->unit = unit;
        this->amount = amount;
        this->note = "No note set";
    }
    ///setter for Location.
    void setLocation(unsigned int location)
    {
        this->location=location;
    }
    ///setter for Amount.
    void setAmount(int amount)
    {
        this->amount = amount;
    }
    ///setter for DateOfEntry.
    void setDateOfEntry(time_t dateOfEntry)
    {
        this->dateOfEntry = dateOfEntry;
    }
    ///getter for name.
    string getName()
    {
        return name;
    }
    ///getter for supplier.
    string getSupplier()
    {
        return supplier;
    }
    ///getter for unit.
    string getUnit()
    {
        return unit;
    }
    ///getter for amount.
    unsigned int getAmount()
    {
        return amount;
    }
    ///getter for expDate.
    int getExpDate()
    {
        return expDate;
    }
    ///getter for location.
    int getlocation()
    {
        return location;
    }
    ///Prints all the data for **this** Product.
    void Print()
    {
        struct tm dateOfEntry;
        dateOfEntry = *localtime(&(this->dateOfEntry));
        cout<<"name:"<<name<<" expDate:"<<expDate<<" day:"<<dateOfEntry.tm_mday<<" supplier:"<<supplier<<" unit:"<<unit<<" amount:"<<amount<<" note:"<<note<<endl;
    }
    ///calculates expDay from expDate.
    int ExpDay()
    {
        return expDate%100;
    }
    ///calculates expMonth from expDate.
    int ExpMonth()
    {
        return (expDate/100)%100;
    }
    ///calculates expYear from expDate.
    int ExpYear()
    {
        return expDate/10000;
    }
    ///checks if **this** Product is expired.
    bool IsItExpired()
    {
        struct tm dateOfEntry;
        dateOfEntry = *localtime(&(this->dateOfEntry));
        if(ExpYear()>dateOfEntry.tm_year - 100)
        {
            return false;
        }
        if(ExpYear()==dateOfEntry.tm_year - 100&&ExpMonth()>dateOfEntry.tm_mon)
        {
            return false;
        }
        if(ExpYear()==dateOfEntry.tm_year - 100&&ExpMonth()==dateOfEntry.tm_mon&&ExpDay()>dateOfEntry.tm_mday)
        {
            return false;
        }
        else return true;
    }
    ///calculates how many days are left until **this** Product expires.
    int HowLongTillExp()
    {
        int daysLeft;
        struct tm dateOfEntry;
        dateOfEntry = *localtime(&(this->dateOfEntry));
        daysLeft = (ExpYear() - dateOfEntry.tm_year - 100)*365;
        daysLeft = daysLeft + (ExpMonth() - dateOfEntry.tm_mon)*30;
        daysLeft = daysLeft + (ExpDay() - dateOfEntry.tm_mday);
        return daysLeft;
    }
    ///Logs the adding of **this** Product(from the storage) onto the log file.
    void logAddingThisItem()
    {
        struct tm dateOfLog;
        dateOfLog = *localtime(&(this->dateOfEntry));
        ofstream log;
        log.open("log.txt",fstream::app);
        if (log.is_open())
        {
            log<<dateOfLog.tm_mday<<" "<<dateOfLog.tm_mon<<" "<<dateOfLog.tm_year - 100<<" Adding ";
            log<<name<<" "<<expDate<<" "<<supplier<<" "<<unit<<" "<<amount<<" "<<location<<endl;
            log.close();
        }
    }
    ///Logs adding more amount of **this** Product(from the storage) onto the log file.
    void logAddingThisItem(int amount)
    {
        //Adding to the log file (just the new part)
        struct tm dateOfLog;
        dateOfLog = *localtime(&(this->dateOfEntry));
        ofstream log;
        log.open("log.txt",fstream::app);
        if (log.is_open())
        {
            log<<dateOfLog.tm_mday<<" "<<dateOfLog.tm_mon<<" "<<dateOfLog.tm_year - 100<<" Adding ";
            log<<name<<" "<<expDate<<" "<<supplier<<" "<<unit<<" "<<amount<<" "<<location<<endl;
            log.close();
        }
    }
    ///Logs the removing of **this** Product(from the storage) onto the log file.
    void logRemovingThisItem(double removeAmount)
    {
        if(removeAmount>=this->amount)
        {
            for(int p=0;p<this->amount/50+1;p++)
            {
                mirrorTable[this->location/sizeOfShelf*sizeOfShelf][this->location/sizeOfShelf][this->location%sizeOfShelf+p]=false;
            }
        }
        struct tm dateOfLog;
        dateOfLog = *localtime(&(this->dateOfEntry));
        ofstream log;
        log.open("log.txt",fstream::app);
        if (log.is_open())
        {
            log<<dateOfLog.tm_mday<<" "<<dateOfLog.tm_mon<<" "<<dateOfLog.tm_year - 100;
            if(removeAmount>=amount)
            {log<<" RemovingAll ";
            }
            else log<<" Removing("<<(amount - removeAmount)<<"-left) ";
            log<<name<<" "<<expDate<<" "<<supplier<<" "<<unit<<" "<<removeAmount<<" "<<location<<endl;
            log.close();
        }
    }
};
///3D array that we use as our storage.
Product* storage[sizeOfShelf][sizeOfShelf][sizeOfShelf];
///Clears and makes both of the tables (3d arrays) easy to use.
void FillBothTables()
{
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                {
                    if(storage[i][j][k]!=nullptr)
                    {
                        delete storage[i][j][k];
                    }
                }
                mirrorTable[i][j][k] = false;
                storage[i][j][k] = nullptr;

            }
        }
    }
}
///Finds place for product.
///
///Finds the first place in the storage where we can put a new product with a given size.
unsigned int SearchForFreeSpace(unsigned int spaceNeeded)
{
    unsigned int currentSpace;
    for(int i=0;i<sizeOfShelf;i++)
    {
        currentSpace = 0;
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
///Creating a new Product.
///
///Creating a new Product, checking if we can put it next to a Product with the same name and expDate.
///If that is not possible we use SearchForFreeSpace(int) to find the first place where it will fit.
///Log that action.
void AddNewProduct(string name, int expDate, string supplier, string unit, int amount)
{
    time_t now;
    now=time(nullptr);
    int combinedAmount;
    bool flag = true;
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
              if(storage[i][j][k]!=nullptr)
              {
                if(storage[i][j][k]->getName()==name&&storage[i][j][k]->getExpDate()==expDate)
                {
                    combinedAmount = storage[i][j][k]->getAmount() + amount;
                    for(int m=storage[i][j][k]->getAmount()/50 + 1 ; m < combinedAmount/50 + 1; m++)
                    {
                       if(k+m<sizeOfShelf)
                       {
                           if(mirrorTable[i][j][k+m])
                           {
                               flag = false;
                           }
                       }
                       else flag = false;
                    }
                    if(flag)
                    {
                        storage[i][j][k]->setAmount(combinedAmount);
                        for(int m=0; m < combinedAmount/50 + 1; m++)
                        {
                            mirrorTable[i][j][k+m] = true;
                        }
                        storage[i][j][k]->setDateOfEntry(now);
                        storage[i][j][k]->logAddingThisItem(amount);
                        return;
                    }
                }
              }
            }
        }
    }
    Product* newProduct = new Product(name,expDate,now,supplier,unit,amount);
    unsigned int spaceNeeded = newProduct->getAmount()/50+1;

    unsigned int positionToPlaceOn = SearchForFreeSpace(spaceNeeded);
    newProduct->setLocation(positionToPlaceOn);
    storage[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf] = newProduct;
    for(int i=0;i<spaceNeeded;i++)
    {
        mirrorTable[positionToPlaceOn/sizeOfShelf*sizeOfShelf][positionToPlaceOn/sizeOfShelf][positionToPlaceOn%sizeOfShelf + i] = true;
    }
    newProduct->logAddingThisItem();

}
///Remove a set amount of a Product.
///
///Remove a set amount of a Product from the storage by name and amount.
///Log that action.
void RemoveSetAmountOfProduct(string removeName, int removeAmount)
{
    int shortestTimeToExp=2000000;
    unsigned int positionOfShortest;
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(storage[i][j][k]!=nullptr)
                {
                    if(storage[i][j][k]->getName()==removeName&&storage[i][j][k]->getExpDate()<shortestTimeToExp)
                    {
                    positionOfShortest = storage[i][j][k]->getlocation();
                    shortestTimeToExp = storage[i][j][k]->getExpDate();
                    }
                }

            }
        }
    }
    if(shortestTimeToExp!=2000000)
    {
        storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->logRemovingThisItem(removeAmount);
        if(storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->getAmount()>removeAmount)
        {
            storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->setAmount(storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->getAmount() - removeAmount);
        }
        else
        {
            unsigned int howBigIsThis = storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->getAmount()/50+1;
            double leftToGet =removeAmount - storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf]->getAmount();
            delete storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf];
            storage[positionOfShortest/sizeOfShelf*sizeOfShelf][positionOfShortest/sizeOfShelf][positionOfShortest%sizeOfShelf] = nullptr;
            RemoveSetAmountOfProduct(removeName,leftToGet);
        }
    }
    else {cout<<"Amount too low!"<<endl;}
}
///Prints all info for all Products in the storage.
void PrintAllInfoOnAllProducts()
{
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(storage[i][j][k]!=nullptr)
                {
                    storage[i][j][k]->Print();
                }
            }
        }
    }
}
///Full amount of Product.
///
///By a given Product name returns the combined amount of all Product objects with that name in the storage.
int AmountOfThisProductInTheStorage(string name)
{
    int amount = 0;
     for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(storage[i][j][k]!=nullptr)
                {
                    if(storage[i][j][k]->getName()==name)
                    {
                        amount = amount + storage[i][j][k]->getAmount();
                    }
                }
            }
        }
    }
    return amount;
}
///Prints amounts of the products in the storage.
///
///using AmountOfThisProductInTheStorage(string) finds and prints to the console the names and amounts of all Products in the storage.
void PrintAmountsOfAllProducts()
{
   string alreadyCheckedProducts[100];
   int numberOfCheckedProducts = 0;
   bool currentProductIsNew = true;
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(storage[i][j][k]!=nullptr)
                {
                    for(int m=0;m<numberOfCheckedProducts;m++)
                    {
                       if(storage[i][j][k]->getName()==alreadyCheckedProducts[m])
                       {
                           currentProductIsNew = false;
                       }
                    }
                    if(currentProductIsNew)
                    {
                        alreadyCheckedProducts[numberOfCheckedProducts + 1] = storage[i][j][k]->getName();
                        numberOfCheckedProducts++;
                        cout<<"Product: "<<storage[i][j][k]->getName()<<" amount: "<<AmountOfThisProductInTheStorage(storage[i][j][k]->getName())<<endl;
                    }
                    currentProductIsNew = true;
                }
            }
        }
    }
}
///Prints the log from a chosen period.
void PrintLogForPeriod(int fromDate,int toDate)
{
ifstream readStream;
readStream.open("log.txt");
if(readStream.fail())
{
    cerr<<"Error opening file!"<<endl;
    exit(1);
}
int day;
int month;
int year;
string action;
string name;
int expDate;
string supplier;
string unit;
int amount;
unsigned int position;
while(!readStream.eof())
{
    readStream>>day>>month>>year>>action>>name>>expDate>>supplier>>unit>>amount>>position;
    if(year>fromDate/10000||(year==fromDate/10000&&month>fromDate/100%100)||(year==fromDate/10000&&month==fromDate/100%100&&day>=fromDate%100))
    {
       if(year<toDate/10000||(year==toDate/10000&&month<toDate/100%100)||(year==toDate/10000&&month==toDate/100%100&&day<=toDate%100))
        {
            cout<<day<<" "<<month<<" "<<year<<" "<<action<<" "<<name<<" "<<expDate<<" "<<supplier<<" "<<unit<<" "<<amount<<" "<<position<<endl;
        }
    }

}
}
///Saves the current storage to a file with a given name.
void SaveFileAs(string fileName)
{
    ofstream save;
    save.open(fileName);
    if (save.is_open())
    {
        for(int i=0;i<sizeOfShelf;i++)
        {
            for(int j=0;j<sizeOfShelf;j++)
            {
                for(int k=0;k<sizeOfShelf;k++)
                {
                   if(storage[i][j][k] != nullptr)
                   {
                       save<<storage[i][j][k]->getName()<<" "<<storage[i][j][k]->getExpDate()<<" "<<storage[i][j][k]->getSupplier();
                       save<<" "<<storage[i][j][k]->getUnit()<<" "<<storage[i][j][k]->getAmount()<<endl;
                   }
                }
            }
        }
        save.close();
    }
}

///Clears all the Products that have expired or are about to.
///
///Clears all the Products from the storage that have expired or are about in the next 10 days.
///Logs that action.
///Prints the deleted Products.
void Clean()
{
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(storage[i][j][k] != nullptr)
                {
                    if(storage[i][j][k]->HowLongTillExp()<=10)
                    {
                           storage[i][j][k]->logRemovingThisItem(storage[i][j][k]->getAmount());
                           storage[i][j][k]->Print();
                          delete storage[i][j][k];
                    }
                }
            }
        }
    }
}
///Opens a storage file.
///
///Clears the tables from all of the current data and loads the data from a file.
string OpenFile()
{
    FillBothTables();
    string fileName;
     cout<<"Write the name of the file that you want to open:";
            cin>>fileName;
            ifstream readStream;
        readStream.open(fileName);
        if(readStream.fail())
        {
            cerr<<"Error opening file!"<<endl;
            exit(1);
        }
        string name;
        int expDate;
        string supplier;
        string unit;
        double amount;
        while(!readStream.eof())
        {
            readStream>>name>>expDate>>supplier>>unit>>amount;
            cout<<name<<expDate<<supplier<<unit<<amount<<endl;
            AddNewProduct(name,expDate,supplier,unit,amount);
        }
        return fileName;
}
///Calculates the money that will be lost if a Product were to expire.
///
///Calculates the money that will be lost if (given number of days) were to pass from a Product with a given name and price.
void MoneyLoss()
{
    string name;
    cout<<"name:";
    cin>>name;
    cout<<endl;
    float price;
    cout<<"price:";
    cin>>price;
    cout<<endl;
    int days;
    cout<<"days:";
    cin>>days;
    int amount;
    for(int i=0;i<sizeOfShelf;i++)
    {
        for(int j=0;j<sizeOfShelf;j++)
        {
            for(int k=0;k<sizeOfShelf;k++)
            {
                if(storage[i][j][k] != nullptr)
                {
                    if(storage[i][j][k]->getName()==name&&storage[i][j][k]->HowLongTillExp()<=days)
                    {
                        amount=amount+storage[i][j][k]->getAmount();
                    }
                }
            }
        }
    }
    cout<<"The loss will be:"<<amount*price<<endl;

}



int main()
{
FillBothTables();
string fileName;
cout<<"Hello, welcome to StorageProject"<<endl<<"Write the name of the file that you want to open:";
cin>>fileName;
ifstream readStream;
readStream.open(fileName);
if(readStream.fail())
{
    cerr<<"Error opening file!"<<endl;
    exit(1);
}
string name;
int expDate;
string supplier;
string unit;
double amount;
while(!readStream.eof())
{
    readStream>>name>>expDate>>supplier>>unit>>amount;
    cout<<name<<expDate<<supplier<<unit<<amount<<endl;
    AddNewProduct(name,expDate,supplier,unit,amount);
}
int nextAction;
while(nextAction != 6)
{
    cout<<"open-1, close-2, save-3, save as-4, help-5, exit-6, print-7, add-8, remove-9, log-10, clean-11, bonus-12"<<endl;
    cout<<"Next action:";
    cin>>nextAction;
    switch(nextAction)
    {
        case 1: {
          fileName = OpenFile();
        break;
        }

        case 2:
        {
            int command;
            cout<<"open-1, exit-any other number"<<endl;
            cin>>command;
            if(command==1)
            {
                fileName = OpenFile();
            }
            else return 0;
            break;
        }


        case 3:
        {
            SaveFileAs(fileName);
            break;
        }

        case 4:
        {
            cout<<"name of file:";
            cin>>fileName;
            cout<<endl;
            SaveFileAs(fileName);
            break;
        }


        case 5:
        {
            cout<<"open <file>	opens <file>"<<endl;
            cout<<"close			closes currently opened file"<<endl;
            cout<<"save			saves the currently open file"<<endl;
            cout<<"saveas <file>	saves the currently open file in <file>"<<endl;
            cout<<"help			prints this information"<<endl;
            cout<<"exit			exists the program"<<endl;
            cout<<"print          prints what is currently in the storage"<<endl;
            cout<<"add            add a new product to the storage"<<endl;
            cout<<"remove         remove an amount of a product from the storage"<<endl;
            cout<<"log            print the log of product added or removed from the storage"<<endl;
            cout<<"clean          remove all the products that have expired or are about to expire"<<endl;
            cout<<"bonus          by product's price see what the loss will be for a period if it were to expire"<<endl;
            break;
        }


        case 7:
        {
            PrintAllInfoOnAllProducts();
            break;
        }


        case 8:
        {
        cout<<"name:";
        cin>>name;
        cout<<endl;
        cout<<"expDate:";
        cin>>expDate;
        cout<<endl;
        cout<<"supplier:";
        cin>>supplier;
        cout<<endl;
        cout<<"unit:";
        cin>>unit;
        cout<<endl;
        cout<<"amount:";
        cin>>amount;
        cout<<endl;
        AddNewProduct(name,expDate,supplier,unit,amount);
        break;
        }

        case 9:
        {
        cout<<name;
        cin>>name;
        cout<<endl;
        cout<<"amount:";
        cin>>amount;
        cout<<endl;
        RemoveSetAmountOfProduct(name,amount);
        break;
        }

        case 10:
        {
        int Day;
        int Month;
        int Year;
        cout<<"fromDay:";
        cin>>Day;
        cout<<endl;
        cout<<"fromMonth";
        cin>>Month;
        cout<<endl;
        cout<<"fromYear";
        cin>>Year;
        cout<<endl;
        int fromDate = Day + 100*Month + 10000*Year;
        cout<<"toDay:";
        cin>>Day;
        cout<<endl;
        cout<<"toMonth";
        cin>>Month;
        cout<<endl;
        cout<<"toYear";
        cin>>Year;
        cout<<endl;
        PrintLogForPeriod(fromDate,Day + 100*Month + 10000*Year);
        break;
        }

        case 11:
        {
        Clean();
        break;
        }
        case 12:
        {
        MoneyLoss();
         break;
        }
    }
}

return 0;
};
