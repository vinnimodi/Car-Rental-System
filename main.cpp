#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
using namespace std;
bool ageNotEligible=false;
bool endProgram=false;
class CarInfo
{
  public:
    string name,color,fuel,transmission,city;
    int price,capacity;
    CarInfo(string name,string color,string fuel,int capacity,string transmission,string city,int cost)
    {
        this->name=name;
        this->color=color;
        this->fuel=fuel;
        this->transmission=transmission;
        this->city=city;
        this->price=cost;
        this->capacity=capacity;
    }
};
vector<CarInfo> CARS;
static map<string,int> isBooked;
class customer_info
{
   public:
     string name;
     string cars[12];
     int age=0;
     int counter=0;
     int lis_no;
     int pick;
     char drop_location;
     int n,m;
   public:
      void getdata();
};
void customer_info:: getdata()
     {
         cout << "\n\t\t\t\tEnter your name : ";
         cin.ignore();
         getline(cin,name);
    int age=0,counter=0;
         while(age<18)
  {
              cout<<"\t\t\t\tEnter your age : ";
              cin>>age;
              if(age<18 && counter<1){
                  cout<<"\t\t\t\t\tNot eligible, re-enter. "<<endl;
                  counter++;
            }
        else if(counter>=1&&age<18)
        {
            ageNotEligible=true;
            cout<<"\n\t\t\t\tYou've used up all your entries for today, please try again later"<<endl;
            return;
        }
        else
        {
            cout<<"\t\t\t\t\tPassed!"<<endl;
            break;
        }
    }
         cout <<"\t\t\t\tEnter your license number : ";
         cin>>lis_no;
    }

class cars
     {
        protected:
         int location,cost;
        CarInfo getCarObjectFromString(string str)
        {
            string name,color,fuel,transmission,city;
            int price,capacity;
            string temp="";
            int count=0;
            for(int i=0;i<str.length();i++)
                {
                if(str[i]!=','){
                    temp+=str[i];
                }
                else{
                    switch(count){
                        case 0:name=temp;break;
                        case 1:color=temp;break;
                        case 2:fuel=temp;break;
                        case 3:capacity=stoi(temp);break;
                        case 4:transmission=temp;break;
                        case 5:city=temp;break;
                        case 6:price=stoi(temp);break;
                        case 7:break;
                    }
                    temp="";
                    count++;
                }
            }
            return CarInfo(name,color,fuel,capacity,transmission,city,price);
        }

        public: cars(){
            fstream db;
            db.open("cardb.txt",ios::in|ios::out);
            if(!db.is_open())
                {
                 cout<<"Unable to open File.";
                 return;
                }
            else
            {
                string line;
                while(getline(db,line))
                {
                    CarInfo temp = getCarObjectFromString(line);
                    CARS.push_back(temp);
                    isBooked.insert({temp.name,0});
                }
            }

        }
public:
    void pick(){
    cout<<"\n\t\t\t\t** Currently we are serving in these metro cities: **"<<endl;
   cout <<"\t\t\t\t1.Delhi";
   cout  <<"\t\t\t\t\t\t2.Mumbai\n";
    cout<< "\t\t\t\t3.Bangalore";
    cout << "\t\t\t\t\t4.Hyderabad\n";
    cout <<"\t\t\t\t5.Chennai";
    cout <<"\t\t\t\t\t6.Kolkata\n";
    cout << endl;
    cout<<"\t\t\t\tEnter the serial number of your location: ";
    cin>>location;
    switch(location)
    {
    case 1: booking_location("Delhi");break;
    case 2: booking_location("Mumbai");break;
    case 3: booking_location("Bangalore");break;
    case 4: booking_location("Hyderabad");break;
    case 5: booking_location("Chennai");break;
    case 6: booking_location("Kolkata");break;
    default:cout<<"\t\t\t\tWrong choice entered!"<<endl;
    }
    }

    string fuelType(string x){
        if(x=="P"){
            return "Petrol";
        }
        else{
            return "Diesel";
        }
    }
    string Transmission_type(string y)
    {
        if(y=="M")
        {
            return "Manual";
        }
        else
        {
            return "Auto";
        }
    }

    void booking_location(string location)
     {
        vector<CarInfo> CarLocation;
        int a;
        int count=0;
        cout<<"\n\tAvailable Cars in "<<location<<" are:"<<endl;
        cout<<"\t***************************************************************************************************"<<endl;
        cout<<"\tModel\t"<<"\t\tColor\t"<<"\tFuel\t"<<"\tCapacity\t"<<"Transmission\t"<<"City\t"<<"Cost/day"<<endl;
        cout<<"\t***************************************************************************************************"<<endl;
        for (int i=0;i<CARS.size();i++)
        {
            if( CARS[i].city==location ){
                if(isBooked[CARS[i].name]==0){
                    cout<<"\t"<<count+1<<" ";
                    cout<<"\t"<<CARS[i].name<<"\t";
                    cout<<"\t"<<CARS[i].color<<"\t";
                    cout<<"\t"<<fuelType(CARS[i].fuel);
                    cout<<"\t\t"<<CARS[i].capacity;
                    cout<<"\t\t"<<Transmission_type(CARS[i].transmission);
                    cout<<"\t\t"<<CARS[i].city;
                    cout<<"\t"<<CARS[i].price<<endl;
                    CarLocation.push_back(CARS[i]);
                    count++;
                }
                else{cout<<"\t"<<CARS[i].name<<":- THIS CAR IS ALREADY BOOKED !!"<<endl;}
            }else{continue;}
        }

        if(count!=0){
            cout<<"\n\t\tEnter your choice : ";
            cin>>a;
            if(isBooked[CarLocation[a-1].name]==1)
            {
                cout<<"Invalid choice,Re-enter your choice : Last attempt."<<endl;
                cin>>a;
                if(isBooked[CarLocation[a-1].name]==1)
                {
                    endProgram=true;
                    return;
                }
            }
            cout<<"\n\tYour choice is : \n";
            cout<<"\t"<<CarLocation[a-1].name;
            cout<<"\t"<<CarLocation[a-1].color;
            cout<<"\t"<<fuelType(CarLocation[a-1].fuel);
            cout<<"\t"<<CarLocation[a-1].capacity;
            cout<<"\t"<<Transmission_type(CarLocation[a-1].transmission);
            cout<<"\t"<<CarLocation[a-1].city;
            cout<<"\t"<<CarLocation[a-1].price<<endl;
            cost=CarLocation[a-1].price;
            isBooked[CarLocation[a-1].name]=1;
        }
        else
            { cout<<"\n\tThere is no car for you to book!"; }
    }
    int get_cost()
    {  return cost;  }
};

class price
     {
        protected:
        int total,days;
        int car_price;
        public:
            price(cars c)
            {  car_price = c.get_cost();   }

            void rent()
            {
                  cout <<"\n\t\tEnter the No. of days for car rent : ";
                  cin>>days;
                  total=days * car_price;
                  cout << "\t\tTotal cost for "<<days<<" days is "<<total<<"."<< endl;
            }
     };

class listing_car : public cars
     {
      protected:
      string car_name;
      string listcolour;
      string listtransmission;
      string listfuel;
      string listcity;
      int listcapacity;
      int listprice;
      public:

      void listing()
      {
          cout << "\n\t\t\t\tEnter the name of the car : ";
          cin.ignore();
          getline(cin,car_name);

          cout <<"\t\t\t\tEnter the colour of the car : ";
          cin>>listcolour;

          cout << "\t\t\t\tEnter the transmission type (M/A): ";
          string transmission;
          cin>>transmission;
            if(transmission=="manual"){listtransmission="M";}
            else if(transmission=="auto"){listtransmission="A";}
            else if(transmission=="M"){listtransmission="M";}
            else if(transmission=="A"){listtransmission="M";}
            else{cout<<"\t\t\t\t\tYou have entered an invalid choice";return;}

          cout << "\t\t\t\tEnter the fuel type (P/D): ";
          string fuel;cin>>fuel;
          if(fuel=="petrol"){listfuel="P";}
            else if(fuel=="diesel"){listfuel="D";}
            else if(fuel=="P"){listfuel="P";}
            else if(fuel=="D"){listfuel="D";}
            else{cout<<"\t\t\t\t\tYou have entered an invalid choice.";return;}

          cout << "\t\t\t\tEnter the seating capacity of the car in numbers eg 2,3,4 : ";
          cin >> listcapacity;

          cout<<"\t\t\t\tEnter the rent per day at which you want to list it out eg 2000 : ";
          cin>>listprice;

          cout << "\t\t\t\tEnter the city where you want to rent out the car eg Delhi : ";
          cin>> listcity;

        cout<<"\n\t\t**************************************************************************************************"<<endl;
        cout<<"\t\tModel\t\t"<<"Colour\t\t"<<"Fuel\t"<<"\tCapacity\t"<<"Transmission\t"<<"City\t\t"<<"Cost/day"<<endl;
        cout<<"\n\t\t**************************************************************************************************"<<endl;
            cout<<"\t\t"<<car_name<<"\t\t";
            cout<<listcolour<<"\t\t";
            cout<<listfuel<<"\t\t";
            cout<<listcapacity<<"\t\t";
            cout<<listtransmission<<"\t\t";
            cout<<listcity<<"\t\t";
            cout<<listprice<<endl;

          fstream myfile("cardb.txt",ios::app);
          if(myfile.is_open())
          {
              string l=car_name;
              l+=",";l+=listcolour;l+=",";l+=listfuel;l+=",";l+=to_string(listcapacity);l+=",";l+=listtransmission;
              l+=",";l+=listcity;l+=",";l+=to_string(listprice);l+=",";
              myfile<<endl<<l;
          }
          myfile.close();
    }
};

int main()
{
cars c1;
system("Color B0");
int c;
cout<<"\t\t\t------------------------------------------------------------------------\t\t\t\t\t\n";
cout<<"\t\t\t------------------------------------------------------------------------\t\t\t\t\t"<<endl;
cout << "\t\t\t\t\t  *** RENT n' DRIVE! ***"<<endl;
cout<<"\t\t\t\t\t*** WELCOME TO RENT n' DRIVE ***"<<endl;
cout<<"\t\t\t------------------------------------------------------------------------\t\t\t\t\t\n";
cout<<"\t\t\t------------------------------------------------------------------------\t\t\t\t\t"<<endl;
cout << "\t\t\tWe provide the following services:-\n\n";
cout << "\t\t\t1. Rent a car" <<endl;
cout << "\t\t\t2. List your car for rent\n\n\n";
cout << "\t\t\tEnter your choice : ";
cin >> c;

switch(c)
{
   case 1:
{
customer_info obj;
obj.getdata();
if(!ageNotEligible)
    {
    c1.pick();
    if(endProgram){return 0;}
    price p1(c1);
    p1.rent();
}
else
{
    return 0;
}
cout<<"\n\t\tDo you wish to rent another car - "<<endl;
cout<<"\t\t\t1.Yes"<<endl;
cout<<"\t\t\t2.No"<<endl;
int ch;
cin>>ch;
if (ch==1)
{

customer_info obj;
system("CLS");
obj.getdata();

c1.pick();
if(endProgram){return 0;}
price p1(c1);
p1.rent();
}
   else if (ch==2) cout<<"Thank you for using our services!"<<endl;
}
break;
case 2:
{
listing_car l1;
l1.listing();
break;
}
default:cout << "Wrong choice entered.";break;
}
return 0;
}
