#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

int officerlogin(int access,string* p)
{
    int counter;
    string userID, password, ID, pass;
    system("cls");
    cout <<"\t\t\t Please enter the userID and password\n\n";
    cout <<"\t\t\t UserID: ";
    cin >> userID;
    *p = userID;
    cout <<"\t\t\t password: ";
    cin >> password;
    cout << "\n\n";
    ifstream input("logininfo.txt");

    while(input>>ID>>pass)
    {
        if(ID==userID && pass==password)
        {
            access = 1;
            counter = 1;
            system("cls");
        }
    }
    input.close();
    if(counter==1)
    {
        cout<<"\t\t\t Login successful\n\n\n";
    }
    else
    {
        cout<<"\t\t\t Login ERROR\n\n\n";
    }
    return access;
}

void registration()
{
    string ruserID,rpassword,rID,rpass;
    system("cls");
    cout<<"\t\t\t Enter UserID: ";
    cin >> ruserID;
    cout << "\t\t\t Enter password: ";
    cin >> rpassword;

    ofstream f1("logininfo.txt", ios::app);
    ofstream casefile(ruserID+".txt");
    f1 << ruserID << ' ' << rpassword << endl;
    system("cls");
    cout << "\n\t\t\t            Registration complete\n         ";
    system("pause");
    system("cls");
}

//.....................Cases structure declaration...............
struct Case {
    int casenumber;
	string name;
	int age;
	char sex;
	string address;
	string crime;
};

//..................Officer structure declaration...............
struct officer {
	string username;
	string password;
	Case assigned_cases[100];
};
//...........................Input file to array................
int inputtoarray(string filename,Case cases[])
{
    int casenumber;
	string name;
	int age;
	char sex;
	string address;
	string crime;

	int Size = 0;
    ifstream fsize(filename+".txt");
    int i = 0;
    while(fsize >> casenumber >> name >> age >> sex >> address >> crime)
    {
        Size = Size + 1;
    }

    ifstream f2(filename+".txt");
    while(f2 >> casenumber >> name >> age >> sex >> address >> crime)
    {
        cases[i].casenumber = casenumber;
        cases[i].name = name;
        cases[i].age = age;
        cases[i].sex = sex;
        cases[i].address = address;
        cases[i].crime = crime;
        i++;
    }

	return Size;
}

//...........................input array to file................
void inputtofile(string filename,Case cases[],int s)
{
    ofstream savefile(filename+".txt");
    for(int i=0;i<s;i++)
    {
        savefile << cases[i].casenumber << ' ' << cases[i].name << ' ' << cases[i].age << ' ' << cases[i].sex << ' ' << cases[i].address << ' ' << cases[i].crime <<endl;
    }
}

//...........................Print case.........................
void printcaseinfo(Case c)
{
    cout << "\tCase number: " << c.casenumber <<endl;
    cout << "\tName: " << c.name <<endl;
    cout << "\tAge: " << c.age <<endl;
    cout << "\tGender: " << c.sex <<endl;
    cout << "\tAddress: " << c.address <<endl;
    cout << "\tCrime: " << c.crime <<endl;
}

//............................Add new case......................
void addnew(string filename,int who)
{
    int Casenumber, Age;
    string Name, Address, Crime;
    char Sex;

		cout << "Case number: ";
		cin.ignore();
		cin >> Casenumber;

		cout << "name: ";
		cin.ignore();
		cin >> Name;

		cout << "age: ";
		cin.ignore();
		cin >> Age;

		cout << "gender(m/f): ";
		cin.ignore();
		cin >> Sex;

		cout << "address: ";
		cin.ignore();
		getline(cin,Address);

		cout << "crime: ";
		cin.ignore();
		cin >> Crime;

		ofstream adminfile("admin.txt",ios::app);
		adminfile << Casenumber << ' ' << Name << ' ' << Age << ' ' << Sex << ' ' << Address << ' ' << Crime <<endl;
		if(who == 2)
        {
        ofstream officerfile(filename+".txt",ios::app);
		officerfile << Casenumber << ' ' << Name << ' ' << Age << ' ' << Sex << ' ' << Address << ' ' << Crime <<endl;
        }

        system("pause");
        system("cls");
}
//........................display all cases...............................
void display(Case usercases[],int s)
{
    for(int i=0;i<s;i++)
    {
        cout << "Case " << i+1 << ":" <<endl;
        printcaseinfo(usercases[i]);
        cout << "\n\n";
    }
}

//........................search a case.....................................
int searchcase(Case usercases[],int s)
{
    int number;
    Case searchedcase;
    int index;
    int Cnt = 0;
    cout << "search by casenumber: "<<endl;
    cin >> number;
    for(int i=0;i<s;i++)
    {
        if(number==usercases[i].casenumber)
        {
            Cnt++;
            index = i;
            searchedcase = usercases[i];
            printcaseinfo(usercases[i]);
            cout << "\n";
        }
    }
    if(Cnt == 0)
        {
            cout << "\t\t\tNo cases found!\n\n";
        }
    return index;
}

//........................delete case........................................
void deletecase(Case usercases[],int s)
{
    int number;
    Case searchedcase;
    int index;
    int Cnt = 0;
    cout << "search by casenumber: "<<endl;
    cin >> number;
    for(int i=0;i<s;i++)
    {
        if(number==usercases[i].casenumber)
        {
            Cnt++;
            index = i;
            searchedcase = usercases[i];
            for(int i=index;i<s;i++)
            {
                usercases[i] = usercases[i+1];
            }
        }
    }
    if(Cnt == 0)
        {
            cout << "\t\t\tNo cases found!\n\n";
        }
}

//........................update case........................................
void updatecase(Case usercases[],int s)
{
    int index = searchcase(usercases,s);
    string Name = usercases[index].name;
	int Age = usercases[index].age;
	char Sex = usercases[index].sex;
	string Address = usercases[index].address;
	string Crime = usercases[index].crime;

    cout << "\t\t\t 1.name 2.age 3.sex 4.address 5.crime\n";
    cout << "\t\t\t What do you wish to update: ";
    int choice;
    cin >> choice;
    if (choice==1)
    {
        cin >> Name;
        usercases[index].name = Name;
    }
    else if(choice==2)
    {
        cin >> Age;
        usercases[index].age = Age;
    }
    else if(choice==3)
    {
        cin >> Sex;
        usercases[index].sex = Sex;
    }
    else if(choice==4)
    {
        cin >> Address;
        usercases[index].address = Address;

    }
    else if(choice==5)
    {
        cin >> Crime;
        usercases[index].crime = Crime;
    }
    else
    {
        cout << "sorry no such thing!";
    }
}



int main()
{
    string filename;
    int access = 0;
    int c;
    cout << "\n\n";
    cout << "\t\t\t==================================================================\n";
    cout << "\t\t\t|          Welcome to the Criminal investigation system          |\n";
    cout << "\t\t\t==================================================================\n\n";
    cout << "\t\t\t          made by: Omar / Mazen / Hassan / Ahmed / Aley           \n\n\n";
    //..................................login form...........................
    int who;
    cout << "Press (1) for admin or (2) for officer: ";
    cin >> who;
    if(who == 2)
    {
        while (access == 0)
        {
            cout << "\n\t| press 1 to Login         |\n";
            cout <<   "\t| press 2 to Register      |\n";
            cout << "\n\tPlease enter your choice: ";
            cin >> c;
            cout <<endl;
            switch(c)
            {
                case 1:
                    access = officerlogin(access,&filename);
                    break;
                case 2:
                    registration();
                    break;
                default:
                    cout << "\t\t\t please Enter a valid choice!\n\n\n\n";
                    system("pause");
                    system("cls");
                    main();
            }
        }
    }
    else if(who == 1)
    {
        while(access == 0)
        {
            system("cls");
            string username, password;
            cout <<"\t\t\t\t Please enter the userID and password\n\n";
            cout <<"\t\t\t\t UserID: ";
            cin >> username;
            cout <<"\t\t\t\t password: ";
            cin >> password;
            system("cls");
            if (username == "admin" && password == "admin")
            {
                access = 1;
                filename = "admin";
                cout << "\n\t\t\t Login successful!\n\n\n";
            }
            else
            {
                cout << "\t\t\t\t Login ERROR!\n\n\n";
                system("pause");
            }
        }
    }

   //...........................program...........................................
    int Size;
    Case* usercases = new Case[Size];

    int loop = 1;
    while (loop == 1)
    {
        Size = inputtoarray(filename,usercases);
        cout << "\t\t\t 1.add new case\n";
        cout << "\t\t\t 2.display cases\n";
        cout << "\t\t\t 3.search for a case\n";
        if(who == 1)
        {
        cout << "\t\t\t 4.delete a case\n";
        cout << "\t\t\t 5.update a case\n";
        }
        cout << "\t\t\t 6.Exit to main menu\n";
        cout << "\t\t\t 7.Exit system\n";
        cout << "\n\t\t Please enter your choice: ";
        cin >> c;
        system ("cls");

        if(c==1)
        {
            addnew(filename,who);
        }
        else if(c==2)
        {
            display(usercases,Size);
            system("pause");
            system("cls");
        }
        else if(c==3)
        {
            searchcase(usercases,Size);
            system("pause");
            system("cls");
        }
        else if(c==4)
        {
            deletecase(usercases,Size);
            Size--;
            inputtofile(filename,usercases,Size);
            system("pause");
            system("cls");

        }
        else if(c==5)
        {
            updatecase(usercases,Size);
            inputtofile(filename,usercases,Size);
            system("pause");
            system("cls");
        }
        else if(c==6)
        {
            system("cls");
            main();
        }
        else if(c==7)
        {
            cout << "\t\t\t\tSystem terminated!\n\n\n";
            return 0;
        }
        else
        {
            cout << "\t\t\t please valid choice!\n\n";
            system("pause");
            system("cls");
        }
    }
    delete[] usercases;
    usercases = NULL;
}
