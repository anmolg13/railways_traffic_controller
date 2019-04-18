#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>\
#include <math.h>
#include <dos.h>
#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

class controller{

    public:
    int roll;
    string name;
    int tunits;
    controller()
    {
        roll=0;
        name="";
        tunits=0;
    }
    controller(const controller &d)
    {
        roll=d.roll;
        name=d.name;
        tunits=d.tunits;
    }
    int operator <(controller const &obj)
    {
        if(tunits<obj.tunits)
            return 1;
        else
            return 0;
    }



}tree[100],c[100];

class rail
{
	char nrail[20]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int time,take;
	public:
   void input()
   {
       cout<<"Enter Train Name :";cin>>nrail;
       cout<<"Enter Arrival Time :";cin>>time;
       cout<<"Enter Departure Time :";cin>>take;
   }
   void output()
   {
       cout<<nrail<<endl<<time<<endl<<take<<endl;
   }
   rail()
   {

   }
   rail(string _x, int _y,int _z)
   {
      _x.copy(nrail,11,0);
      time = _y;
      take = _z;
   }
   string getX() const { return nrail; }
   int getY() const { return time; }
   int getZ() const { return take; }
};

// To compare two points
class myComparator
{
public:
    int operator() (const rail& p1, const rail& p2)
    {
        return p1.getY() > p2.getY();
    }
};

//funtion prototypes
void intro1();
void intro();
void welcome1();
void welcome();
void admin();
void gotoxy (int , int );
void rectangle(int ,int ,int ,int );
void display(priority_queue<rail,vector<rail>, myComparator> );
void buildtree(int ,int ,int ,controller [],controller []);
void update(int ,int ,int ,int ,int ,controller [],controller []);
controller func();
controller query(int ,int ,int ,int ,int ,controller []);
void person();
void graph();
void add_train();



COORD coord = {0, 0};
void gotoxy (int x, int y)
        {
        coord.X = x;
        coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }

 void rectangle(int x,int y,int l,int b)
{
    int i,m;
    gotoxy(x,y); printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y); printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",186);
            }

        }

    }

    gotoxy(x,m); printf("%c",200);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}

void display(priority_queue<rail,vector<rail>, myComparator> pq)
{
    int c=0;
    while(pq.empty()==false)
    {
        pq.pop();
        c++;
    }
    cout<<"No. of trains left to arrive: "<<c;

}

void buildtree(int node,int start,int end,controller tree[],controller a[])
{

if(start==end)
{
    tree[node]=a[start];

}
else
{
          int mid=(start+end)/2;
          buildtree(2*node,start,mid,tree,a);
          buildtree(2*node+1,mid+1,end,tree,a);
      if(tree[2*node]<tree[2*node+1])
          {
              tree[node]=tree[2*node];

          }
      else
          {

              tree[node]=tree[2*node+1];
          }
}
}
void update(int node,int start,int end,int idx,int val,controller tree[],controller a[])
{
      if(start==end)
            {
                 a[idx].tunits=val;
                 tree[node].tunits=val;
            }
      else
            {
                int mid=(start+end)/2;
                if(idx>=start&&idx<=mid)
                update(2*node,start,mid,idx,val,tree,a);
                else
                update(2*node+1,mid+1,end,idx,val,tree,a);
                if(tree[2*node]<tree[2*node+1])
                tree[node]=tree[2*node];
                else
                tree[node]=tree[2*node+1];
            }
}
controller func()
{
    controller h;
    h.name="";
    h.roll=0;
    h.tunits=100005;
    return h;
}
controller query(int node,int start,int end,int l,int r,controller tree[])
{
          if(l>end||start>r)
          return func();
          if(l<=start&&r>=end)
            return tree[node];
          controller p1,p2;
          int mid=(start+end)/2;
           p1=query(2*node,start,mid,l,r,tree);
           p2=query(2*node+1,mid+1,end,l,r,tree);
          if(p1<p2)
            return p1;
           else
            return p2;
}

void person()
{
      cout<<endl;
      int choice;
      char ch;
      system("cls");
      do
     {
      system("cls");
      cout<<"The Segment Tree of Controllers\n";
      cout<<"1. Display Tree\n";
      cout<<"2. Update\n";
      cout<<"3. Range Minimum\n";
      cout<<"4. Exit\n";
      cout<<"Enter Your Choice:";
      cin>>choice;
      switch(choice)
      {
          case 1: {
                       for(int i=1;i<16;i++)
                        {
                            cout<<tree[i].roll<<" "<<tree[i].name<<" "<<tree[i].tunits<<endl;
                        }
                        break;
                  }
          case 2:{

                     int o,p;
                     cout<<"\nEnter index of the person(1-6):";
                     cin>>o;
                     cout<<"\nEnter value of tunits to be changed:";
                     cin>>p;
                     update(1,1,6,o,p,tree,c);
                     break;

                 }
         case 3:{
                      int o,p;
                      cout<<"\nEnter the range from which you want to find the minimum [1,6] inclusive:";
                      cin>>o>>p;
                      controller m=query(1,1,6,o,p,tree);
                      cout<<"Controller "<<m.name<<" working for "<<m.tunits<<" units";
                      break;
                 }

      }
      cout<<"\nContinue?(Y/N)";
      cin >>ch;
      }while(ch=='y' || ch=='Y');



}

int size=0;

class BoardingPass
{
    public:
	char aname[20];
	char pname[20];
   void input()
   {
       cout<<"Enter Train Name :";cin>>aname;
       cout<<"Enter Passenger Name :";cin>>pname;
   }
   void output()
   {
       cout<<aname<<endl<<pname<<endl;
   }
   BoardingPass(){};
   BoardingPass(char a[20],char p[20])
   {
    strcpy(aname,a);
    strcpy(pname,p);
   }
}BP[20];

void add_passenger()
{
    fstream fil;
    struct BoardingPass P;
    fil.open("PASSENGER.dat",ios::binary|ios::out);
    int ch=1;
    while(ch==1)
    {
        P.input();


        fil.write((char*)&P,sizeof(P));
        cout<<"More (1/0) ?";
        cin>>ch;
    }
    fil.close();
}

void catch_train(string fname)
{
    fstream file;
    struct BoardingPass P;
    int i=0;
    char s1[20];
    char s2[20];
    file.open("PASSENGER.dat",ios::binary|ios::in);
    while(file.read((char*)&P,sizeof(P)))
    {
        strcpy(BP[i].aname,P.aname);
        strcpy(BP[i].pname,P.pname);
        i++;
        size++;

    }
    string temp;
    file.close();
    for(int i=0;i<size;i++)
    {
     temp=BP[i].aname;
     if(temp==fname)
        BP[i].pname;
    }
}

void graph()
{
     priority_queue<rail,vector<rail>,myComparator> pq;
    fstream file;
    string s;
    int t,l;
    class rail B;
    file.open("TRAINS.dat",ios::binary|ios::in);
    while(file.read((char*)&B,sizeof(B)))
    {
        s=B.getX();
        t=B.getY();
        l=B.getZ();
        pq.push(rail(s,t,l));
    }
    file.close();
    cout<<"Trains In The Arriving Queue(prior to their arrival time)\n";
    cout<<"Train Name        Arrival Time   Departure Limit\n";
    priority_queue<rail,vector<rail>,myComparator> jj=pq;
    while (jj.empty() == false)
    {
        rail p = jj.top();
        cout << p.getX() << "           " << p.getY() <<"              "<<p.getZ();
        cout << endl;
        jj.pop();
    }
    cout<<"\nChecking if trains have same arrival times:";
    for(int i=0;i<10;i++)
    {
        cout<<".";
        for(int j=0;j<4000;j++)
            for(int k=0;k<4000;k++)
            {
            }
            }
            cout<<endl;
     priority_queue<rail,vector<rail>,myComparator> rr,ll;
     jj=pq;
    while(jj.empty()==false)
     {
         rail n=jj.top();
         jj.pop();
         rail m=jj.top();
         jj.pop();
         int count=m.getY();
         if(n.getY()==m.getY())
         {
             rr.push(rail(n.getX(),n.getY(),n.getZ()));
             count++;
             jj.push(rail(m.getX(),count,m.getZ()));

         }
         else
         {
             rr.push(rail(n.getX(),n.getY(),n.getZ()));
             rr.push(rail(m.getX(),m.getY(),m.getZ()));
         }

     }
     pq=rr;
    while (pq.empty() == false)
    {
        rail p = pq.top();
        cout << p.getX() << "           " << p.getY() <<"              "<<p.getZ();
        cout << endl;
        pq.pop();
    }
    pq=rr;



    cout<<"This Program is set for One runway (One train can arrive at a a time)\n\n";
    int total;
    cout<<"Enter No. Of Time Cycles:";
    cin>>total;
    cout<<"\n\nThe Complete arriving Simulation Is as follows:-\n\n";
    while(pq.empty()==false)
    {

          if(total>0)
        {
         cout<<"Railway traffic Personal In the control room(who has the least shift period):";
         controller m=query(1,1,6,1,6,tree);
         cout<<"Controller "<<m.name<<" working for "<<m.tunits<<" units\n\n";
         int thresh=m.tunits;

         rail q=pq.top();
        cout<<"Train Asking To Arrive::"<<q.getX()<<" TRAIN\n\n";
        char g;
        cout<<"Grant Permission?(Y/N)";
        cin>>g;
        if(g=='y' || g=='Y')
        {
            cout<<q.getX()<<"Arrived with Arrival time of "<<q.getY()<<" units and will stay "<<q.getZ()<<" units on the runway\n\n";
            total=total-q.getZ();
            thresh=thresh-q.getZ();
            if(thresh<=0)
            {
                for(int i=1;i<7;i++)
                if(c[i].name==m.name)
                update(1,1,6,i,100,tree,c);
            }

            catch_train(q.getX());
                cout<<q.getX()<<"Departed after staying for "<<q.getZ()<<" units\n";
                cout<<"Total Time cycles Left: "<<total<<endl;
                pq.pop();
        }
         else
            {
                cout<<"Access Denied\n\n";
                pq.pop();
            }



    }
    else
            {

                cout<<"Time cycles are ended\n";
                break;
            }



    }
    display(pq);







}

void add_train()
{
    fstream fil;
    rail A;
    fil.open("TRAINS.dat",ios::binary|ios::app);
    int ch=1;
    while(ch==1)
    {
        A.input();


        fil.write((char*)&A,sizeof(A));
        cout<<"More (1/0) ?";
        cin>>ch;
    }
    fil.close();
}




void intro()
{
     system("cls");
      char jk;
      do{
            system("cls");
      int choice;
      char ch;
      cout<<"Welcome To Railway Traffic Control\n";
      cout<<"1. List Of The Railway Traffic Controllers\n";
      cout<<"2. Railway Station arriving Queues And Mechanism\n";
      cout<<"3. Add trains\n";
      cout<<"4. Add Passengers\n";
      cout<<"5. Exit\n";
      cout<<"Enter Your Choice:";
      cin>>choice;
      switch(choice)
      {
          case 1: {
              person();
              break;
                  }
          case 2: {
                  graph();
                  break;
                  }
          case 3: {
                  add_train();
                  break;
                  }
          case 4: {
                  add_passenger();
                  break;
                  }

      }
      cout<<"\nContinue?(Y/N)";
      cin >>jk;
      }while(jk=='y' || jk=='Y');


}

void welcome1()
{
    system("cls");

system("color b0");
rectangle(10,6,80,30);
gotoxy(29,10);cout<<"RAILWAYS TRAFFIC CONTROLLER";

gotoxy(34,8);cout<<"_____________";
gotoxy(34,11);cout<<"_____________";

gotoxy(20,15);cout<<"                 SUBMITTED BY";
gotoxy(15,16);cout<<"                    **ANMOL GOYAL**";
gotoxy(18,23);cout<<"                   A PROJECT IN C++ ";
char ch;
ch=getche();
if(ch==13)
{
    intro1();
}
}

void intro1()
{
    char c;
    do
    {
        system("cls"); //Clears the screen
        rectangle(8,9,70,13);
        gotoxy(31,11); cout<<"Press <-'Enter to login \n\n\n\t\t\t\t\t";
        c=getche(); //Variable c stores the key pressed by user
        if (c==13)
        admin();
        if (c==27)
        exit(0); //27 is ASCII code of escape key

    }while(1); //infinite loo
}

void admin()

{/*char d[6],p[6];

    system("cls");
cout<<"Login Id:";cin>>d;
cout<<"Password(5 characters):";
int i=0;
char c;
for(i=0;i<5;i++)
{
c=getch();
p[i]=c;
printf("*");
}
p[i]='\0';

if((strcmp(d,"admin")==0)&&(strcmp(p,"admin")==0))
{

}
else{
    printf("No match!!");*/

intro();
}




int main()
{
    fstream file;

    file.open ("personnel.txt", ios::out | ios::in );
    string x;int y,w;
    int i=1;
    while(file>>w>>x>>y)
    {
      c[i].roll=w;
      c[i].name=x;
      c[i].tunits=y;
      i++;
    } //got the data
    /* storing the data in the segment tree*/
    buildtree(1,1,6,tree,c);
    file.close();
    welcome1();



    return 0;
}
