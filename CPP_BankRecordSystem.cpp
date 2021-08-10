#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class CPP_BankRecordSystem
{
    private:
        char account_no[20];
        char fName[10];
        char lName[10];
        float totalBalance;
    public:
        void readData();
        void showData();
        void writeRecord();
        void readRecord();
        void searchRecord();
        void editRecord();
        void deleteRecord();

};
void CPP_BankRecordSystem :: readData()
{
    cout<<"\nEnter Account Number : ";
    cin>>account_no;
    cout<<"Enter First name : ";
    cin>>fName;
    cout<<"Enter Last Name : ";
    cin>>lName;
    cout<<"Enter Balance : ";
    cin>>totalBalance;
    cout<<endl;
}
void CPP_BankRecordSystem :: showData()
{
    cout<<"\nAccount Number : "<<account_no<<endl;
    cout<<"First Name : "<<fName<<endl;
    cout<<"Last Name : "<<lName<<endl;
    cout<<"Current Balance : Rs."<<totalBalance<<endl;
    cout<<"-------------------------------------"<<endl;
}
void CPP_BankRecordSystem :: writeRecord()
{
    ofstream outfile;
    outfile.open("record.bank" , ios::binary|ios::app);
    readData();
    outfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    outfile.close();
}
void CPP_BankRecordSystem :: readRecord()
{
    ifstream infile;
    infile.open("record.bank" , ios::binary);
    if(!infile)
    {
        cout<<"Error while opening! File Not Found..!"<<endl;
        return;
    }
    cout<<"\n* * * Data From File * * *"<<endl;
    while (!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            showData();
        }
    }
    infile.close();
}
void CPP_BankRecordSystem :: searchRecord()
{
    int n;
    ifstream infile;
    infile.open("record.bank" , ios::binary);
    if(!infile)
    {
        cout<<"\nError while opening! File Not Found..!"<<endl;
        return;
    }
    infile.seekg(0 , ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" record in the file.";
    cout<<"\nEnter Record Number To Search : ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    showData();
}
void CPP_BankRecordSystem :: editRecord()
{
    int n;
    fstream iofile;
    iofile.open("record.bank" , ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError while opening! File Not Found..!"<<endl;
        return;
    }
    iofile.seekg(0 , ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" record int he file.";
    cout<<"\nEnter Record Number To Edit : ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    showData();
    iofile.close();
    iofile.open("record.bank" , ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to modify : "<<endl;
    readData();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void CPP_BankRecordSystem :: deleteRecord()
{
    int n;
    ifstream infile;
    infile.open("record.bank" , ios::binary);
    if(!infile)
    {
        cout<<"\nError while opening! File Not Found..!"<<endl;
        return;
    }
    infile.seekg(0 , ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" record in the file.";
    cout<<"\nEnter Record Number To Delete : ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank" , ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0 ; i<count ; i++)
    {
        infile.read(reinterpret_cast<char*>(this), sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tempfile.bank" , "record.bank");
}
int main()
{
    CPP_BankRecordSystem BRS;
    int choice;
    cout<<"* * * * * Account Information Systsem * * * * *"<<endl;
    while (true)
    {
        cout<<" Select below one option :- ";
        cout<<"\n\t1-->Add record to file.";
        cout<<"\n\t2-->Show record from file.";
        cout<<"\n\t3-->Search record from file.";
        cout<<"\n\t4-->Update record.";
        cout<<"\n\t5-->Delete record.";
        cout<<"\n\t6-->Quit.";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                BRS.writeRecord();
                break;
            case 2:
                BRS.readRecord();
                break;
            case 3:
                BRS.searchRecord();
                break;
            case 4:
                BRS.editRecord();
                break;
            case 5:
                BRS.deleteRecord();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<"\nInvalid Choice...!";
                exit(0);
        }
    }
    system("pause");
    return 0;
}