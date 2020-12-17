#include <iostream>
#include <string>
#include <stdlib.h>
#include <typeinfo>
using namespace std;
class Person
{

protected:

    string name;
    int id;
    string age;
    string bloodGroup;
    string phone;

public:

    void setName()
    {
        cout<<" Enter name :"<<endl;
        string n;
        cin>> n;
        name = n;
    }
    string getName()
    {
        return name;
    }
    void setId()
    {
        int n;
        cout<<" Enter ID :"<<endl;
        cin>>n;
        id = n;
    }
    int getId()
    {
        return id;
    }
    void setBloodGroup()
    {
        string b;
        cout<<" Enter Blood group :"<<endl;
        cin>>b;
        bloodGroup = b;
    }
    string getBloodGroup()
    {
        return bloodGroup;
    }
    void setPhone()
    {
        string p;
        cout<<" Enter phone no :"<<endl;
        cin>>p;
        phone = p;
    }
    string getPhone()
    {
        return phone;
    }
    void setAge()
    {
        string a;
        cout<<" Enter age :"<<endl;
        cin>>a;
        age = a;
    }
    string getAge()
    {
        return age;
    }

};

class Owner : public Person
{

public:
    static double revenue;
    static double total_income;
    Owner()
    {
        name = "Kadir";
        id = 101;
        age = "24 years";
        bloodGroup = "0(-ve)";
        phone = "05432656898989";
    }


 	
    double getTotalIncome()
    {
        return total_income;
    }

};

double Owner::revenue = 0;
double Owner::total_income = 0;




class Members : public Person
{
    double fee;
public:

    void display()
    {
        cout<<"  Name : "<<name<<endl;
        cout<<"  Id : " <<id<<endl;
        cout<<"  Age : "<<age<<endl;
        cout<<"  Phone : "<<phone<<endl;
        cout<<"  Fee : "<<fee<<endl;
    }
    void setFee()
    {
        int n;
        cout<< " Enter fee per member :"<<endl;
        cin>>n;
        fee = n;
    }
    double getFee()
    {
        return fee;
    }
};


class TraiNer : public Person
{
    double salary;
public:

    void setSalary()
    {
        cout<< " Enter salary of gymnasium ::"<<endl;
        int n;
        cin>>n;
        salary = n;
    }

    int getSalary()
    {
        return salary;
    }
    void displayTrainer()
    {
        cout<<"  Name : "<<name<<endl;
        cout<<"  Id : " <<id<<endl;
        cout<<"  Age : "<<age<<endl;
        cout<<"  Phone : "<<phone<<endl;
        cout<<"  Salary : "<<salary<<endl<<endl;
    }

};

class StoredData
{
public:

    Members member[100];
    TraiNer trainer[10];
    static int No_member;

};
int StoredData::No_member;
int main()
{
    StoredData data;
    Owner owner;
    int No_trainer = 0;
    cout<<"******************GYM MANAGEMENT SYSTEM************************"<<endl;
    cout<<endl;
    cout<<"================================================================"<<endl;
    while(1)
    {
        cout<<" Enter 1 for register member "<<endl;
        cout<<" Enter 2 to  member information details  "<<endl;
        cout<<" Enter 3 for register of trainer "<<endl;
        cout<<" Enter 4 to know trainer information details"<<endl;
        cout<<" Enter 5 to show revenue details "<<endl;
        cout<<" Enter 6 to show income details "<<endl;
        cout<<" Enter 0 to exit"<<endl<<endl;
        cout<<"===================================================================="<<endl<<endl;

        cout<<" Enter your choice ::";
        char choice;
        cin>>choice;

        switch(choice)
        {
        case '1':
            {
                int m,i;
                cout<<" Enter number of member that you want to register "<<endl;
                cin>>m;
                
                if(typeid(m).name()!=typeid(int).name())
                {
                	cout<<" Please enter an integer number "<<endl;
                	cin>>m;
				}
                
                
               
                StoredData::No_member = m;
                for(i = 0; i<StoredData::No_member;i++)
                {
                    data.member[i].setName();
                    data.member[i].setId();
                    data.member[i].setPhone();
                    data.member[i].setFee();
                    data.member[i].setAge();
                    data.member[i].getBloodGroup();

                }
                break;
            }
        case '2':
            {
                if(StoredData::No_member != 0)
                {
                    cout<<" Please enter id of member to show details "<<endl;
                    int d;
                    cin>>d;
                    for(int i= 0; i<StoredData::No_member;i++)
                    {
                        if(data.member[i].getId() == d)
                        {
                            data.member[i].display();
                            break;
                        }
                        else
                        {
                            cout<<" Your ID is wrong !!!"<<endl<<endl;
                            break;
                        }
                    }
                }
                else
                {
                    cout<<" There is no member registered yet !!!"<<endl<<endl;
                }

                break;
            }
            case '3':
            {
                int m,i;
                cout<<" Enter number of trainer that you want to register "<<endl;
                cin>>m;
                No_trainer = m;
                for(i = 0; i<No_trainer;i++)
                {
                    data.trainer[i].setName();
                    data.trainer[i].setId();
                    data.trainer[i].setPhone();
                    data.trainer[i].setSalary();
                    data.trainer[i].setAge();

                }
                break;
            }
            case '4':
            {
                if(No_trainer != 0)
                {
                    cout<<" Please enter id of trainer to show details ::"<<endl;
                    int d;
                    cin>>d;
                    for(int i= 0; i<No_trainer;i++)
                    {
                        if(data.trainer[i].getId() == d)
                        {
                            data.trainer[i].displayTrainer();
                            break;
                        }
                        else
                        {
                            cout<<" Your ID is wrong !!!"<<endl<<endl;
                            break;
                        }
                    }
                }
                else
                {
                    cout<<" There is no trainer registered yet !!!"<<endl<<endl;
                }

                break;
            }
            case '5':
            {
                double d = 0.0;
                    if(StoredData::No_member != 0)
                    {
                        for(int i= 0;i<StoredData::No_member;i++)
                        {
                            d = d + data.member[i].getFee();
                        }
                        Owner::revenue =d;
                        cout<<" Total revenue : "<<Owner::revenue<<endl<<endl;

                    }
                    else
                    {
                        cout<<" There is no member registered yet !!!"<<endl<<endl;
                    }

                break;
            }
            case '6':
            {
                double  s = 0;
                for(int i=0;i<No_trainer;i++)
                {
                    s += data.trainer[i].getSalary();
                }
                Owner::total_income = Owner::revenue - s;
                cout<<" Total revenue : "<<Owner::revenue<<endl;
                cout<<" Total trainer salary : "<<s<<endl;
                cout<<" Total income : "<<Owner::total_income<<endl<<endl;
                cout<<"========================================================"<<endl<<endl;
                break;
            }
            case '0':
            {

                exit(1);
            }
        default :
            {
                cout<<" Sorry your choice is wrong ! please try again"<<endl<<endl;
                cout<<" ........................... "<<endl<<endl;
                break;	
            }
        }
        }


    return 0;
}
