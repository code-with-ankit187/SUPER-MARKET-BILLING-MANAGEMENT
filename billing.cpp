#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"

//global variable declaration
int k=7,r=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm,dd,yy;
};

ofstream fout;
ifstream fin;

class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        cout<<BLUE<<BOLD<<"\n\n\tItem No: "<<RESET;
        cin>>itemno;
        cout<<BLUE<<BOLD<<"\n\n\tName of the item: "<<RESET;
        cin>>name;
//gets(name);
        cout<<BLUE<<BOLD<<"\n\n\tManufacturing Date(dd-mm-yy): "<<RESET;
        cin>>d.mm>>d.dd>>d.yy;
    }
    void show()
    {
        cout<<"\n\tItem No: ";
        cout<<itemno;
        cout<<"\n\n\tName of the item: ";
        cout<<name;
        cout<<"\n\n\tDate : ";
        cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    int retno()
    {
        return(itemno);

    }

};

class amount: public item
{
    float price,qty,gst,gross,dis,netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

void amount::add()
{
    item::add();
    cout<<BLUE<<BOLD<<"\n\n\tPrice: "<<RESET;
    cin>>price;
    cout<<BLUE<<BOLD<<"\n\n\tQuantity: "<<RESET;
    cin>>qty;
    cout<<BLUE<<BOLD<<"\n\n\tgst percent: "<<RESET;
    cin>>gst;
    cout<<BLUE<<BOLD<<"\n\n\tDiscount percent: "<<RESET;
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross=price+(price*(gst/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\n\tNet amount: ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(44,k);
    cout<<gst;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"GST";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<BLUE<<BOLD<<"\n\t\t                 DETAILS                  "<<RESET;
    cout<<"\n\t\t*********************************************";
    cout<<CYAN<<BOLD<<"\n\n\t\tPRICE                     :"<<price<<RESET;
    cout<<CYAN<<BOLD<<"\n\n\t\tQUANTITY                  :"<<qty<<RESET;
    cout<<CYAN<<BOLD<<"\n\t\tGST PERCENTAGE              :"<<gst<<RESET;
    cout<<CYAN<<BOLD<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis<<RESET;
    cout<<CYAN<<BOLD<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt<<RESET;
    cout<<"\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<CYAN<<ITALIC<<BOLD<<"Super Market Billing "<<RESET;
    gotoxy(25,3);
    cout<<YELLOW<<"===========================\n\n"<<RESET;
    cout<<GREEN<<BOLD<<"\n\t\t1.Bill Report\n\n"<<RESET;
    cout<<GREEN<<BOLD<<"\t\t2.Add/Remove/Edit Item\n\n"<<RESET;
    cout<<GREEN<<BOLD<<"\t\t3.Show Item Details\n\n"<<RESET;
    cout<<GREEN<<BOLD<<"\t\t4.Exit\n\n"<<RESET;
    cout<<GREEN<<BOLD<<"\t\tPlease Enter Required Option: "<<RESET;
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<CYAN<<ITALIC<<BOLD<<"Bill Details"<<RESET;
        gotoxy(25,3);
        cout<<YELLOW<<"================\n\n"<<RESET;
        cout<<RED<<BOLD<<"\n\t\t1.All Items\n\n"<<RESET;
        cout<<RED<<BOLD<<"\t\t2.Back to Main menu\n\n"<<RESET;
        cout<<RED<<BOLD<<"\t\tPlease Enter Required Option: "<<RESET;
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" BILL DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"GST %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<CYAN<<ITALIC<<BOLD<<"Bill Editor"<<RESET;
        gotoxy(25,3);
        cout<<YELLOW<<"=================\n\n"<<RESET;
        cout<<YELLOW<<BOLD<<"\n\t\t1.Add Item Details\n\n"<<RESET;
        cout<<YELLOW<<BOLD<<"\t\t2.Edit Item Details\n\n"<<RESET;
        cout<<YELLOW<<BOLD<<"\t\t3.Delete Item Details\n\n"<<RESET;
        cout<<YELLOW<<BOLD<<"\t\t4.Back to Main Menu "<<RESET;
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<BLUE<<BOLD<<"\n\t\tItem Added Successfully!"<<RESET;
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\tEnter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\tCurrent Details are\n";
                        amt.show();
                        cout<<"\n\n\t\tEnter New Details\n";
                        amt.add();
                        cout<<"\n\t\tItem Details editted";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tItem No does not exist...Please Retry!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<BLUE<<"\n\n\tEnter Item Number to be deleted :"<<RESET;
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
//fstream tmp("temp.dat",ios::binary|ios::out);
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<BLUE<<"\n\t\tItem Succesfully Deleted"<<RESET;
            else if (flag==0)
                cout<<BLUE<<"\n\t\tItem does not Exist! Please Retry"<<RESET;
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\tWrong Choice!!! Retry";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\tEnter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tItem does not exist....Please Retry!";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<CYAN<<BOLD<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?"<<RESET;
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<YELLOW<<BOLD<<"************************** THANKS **************************************"<<RESET;
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tWrong Choice....Please Retry!";
        getch();
        goto menu;
    }
    return 0;
}

