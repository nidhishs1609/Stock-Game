/*
  Stockgame
  --------CREATED BY: Atmesh and Nidhish-----------------------
*/
#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>
#include<stdio.h>
#include <ctype.h>
#include<string.h>
#include <time.h>

struct industry
	{
	 char industryname[50];
	 float value;
	 int growth;
	 int code;
	}ind[10] = { {"Technology",10000,0,0},
	    {"Agriculture",10000,0,1 },
	    {"Automobiles",10000,0,2},
	    {"Chemical",10000,0,3},
	    {"Services",10000,0,4},
	    {"Education",10000,0,5},
	    {"Healthcare",10000,0,6},
	    {"Entertainment",10000,0,7},
	    {"Textile",10000,0,8},
	    {"Wholesale",10000,0,9}
	  };

struct company
	{
	 char name[25];
	 int indcode[2];
	 float stockval;
	 float growth;
	 int age;
	 int code;
	 int luck;
	 float preval;
	}com[10];

struct user
	{
	  char name[25];
	  int companycodes[10];
	  float share[10];
	  float balance;
	  float networth;
	  int bestscore;
	  int compno;
	}us;

//functions in the program
void initializeind(industry&);
void updateind(industry&);
void age(company&);
void luck(company&);
void stock(company&);
void updatecomp(company&);
void companydisplay(company&);
void rulespage(void);//pending
void homepage(void);
void game(void);

// timer code
int resetted, running, beg, end;

class timer {
	public:
		timer();
		void start();
		void stop();
		void reset();
		void resume();
		unsigned long  getTime();
	private:
		unsigned long  beg;
		unsigned long  end;
	};

timer::timer()
	{
	 resetted = 1;
	 running = 0;
	 beg = 0;
	 end = 0;
	}

void timer::start()
	{
		if(! running)
		{
			if(resetted)
				beg = (unsigned long) clock();
			else
				beg -= end - (unsigned long) clock();
			running = 1;
			resetted = 0;
		}
	}

unsigned long timer::getTime()
	{
	 if(running)
		return ((unsigned long) clock() - beg) / CLOCKS_PER_SEC;
	 else
		return end - beg;
	}

void timer::resume()
{
	if(!running)
	{       running=1;
		beg -= end - (unsigned long) clock();

	}
}

void timer::stop()
	{
		 if(running==1)
		 {
			running=0;
			resetted=0;
		 }

	}

void main()
	{
	 clrscr();
	randomize();
	 homepage();
	 getch();
	}

//functions

void updateind(industry &ind)
	{
	 ind.value += (float)((ind.growth/100)*ind.value); //Updates the industry's value when called
	}

void initializeind(industry &ind)
	{
	//To assign values to the industry at the start of the program
	 ind.growth = random(10) - random(12);
	 ind.value = (random(3000) +random(2000)+6000)*10;
	}

void age(company &co)
	{
	//Assigns a Random age to the company. Age is later used in calculations to determine the company's stock value.
	  co.age = 20-random(20);
	}

void luck(company &co)
	{
	 //Assigns a Random Luck to the company, It is later used in calculations to determine the company's stock value.
	 co.luck = ( random(10) - random(12) )+ ( random(10) - random(8) );
	}

void stock(company &co)
	{
	 //Calculation of the given company's stock value
	 int x = random(1);
	 co.stockval = (float)((ind[co.indcode[x]].value * co.age + ind[co.indcode[1-x]].value * co.luck)/(random(50) + 100));
	}

void updatecomp(company &co)
	{
	 //To refresh the values of the company
	 co.preval = co.stockval;
	 luck(co);
	 stock(co);
	 co.growth = (float)((co.stockval - co.preval)/co.preval)*100;
	}

void companydisplay(company &co)
	{
	 //Because writing the same cout statement multiple times can get agonizing
	 cout<<"Name: "<<co.name<<endl;
	 cout<<"Per Stock Value: "<<co.stockval<<" Growth: "<<co.growth<<endl;
	}

void game(void)
	{

 	 //The Part of the program
	 int i,j,m,flag,x=20;
	 char comname1[20][20] = {"Agro","Micro","Mega","Mini","e-","Tex","Syn","hyper","solar","moto","energy"};
	 char comname2[20][20] = {"Tech","Inc.","pvt.ltd.","kart","care","ride","zone","city","motors","sports"};
	 us.balance = 10000;
	 //Initialising Industry Values
	 for(i=0;i<10;i++)
	   {
		initializeind(ind[i]);
	   }
	 //Generating Companies
	 for(i=0;i<10;i++)
	 	{

	 	 strcat(com[i].name,comname1[random(11)]);
	 	 strcat(com[i].name,comname2[random(9)]);
	 	 age(com[i]);
	 	 com[i].indcode[0] = random(5);
	 	 com[i].indcode[1] = random(5) +5;
	 	 updatecomp(com[i]);

		 if(com[i].stockval<0)
	   	 	com[i].stockval*= -1;

	}

	goto start1;
	 start:
	 us.compno =0;
	 us.balance =us.networth;
	 start1:
	 while (x!=99)
	 {
	   clrscr();
	   cleardevice();
	 for(i=0;i<10;i++)
	 	{
	   	 flag =0;
	   	 for(j=0;j<us.compno;j++)
		  	 {
				 if(i== us.companycodes[j])
					 flag =1;
		  	 }
	 if (flag!=1)
		{
			cout<<"Company "<<i<<": "<<com[i].name<<" Industries: "<<ind[com[i].indcode[0]].industryname<<" & "<< ind[com[i].indcode[1]].industryname<<endl;
			cout<<"Value of Each Share :"<<com[i].stockval<<endl;
		}
	flag=0;
	}

	cout<<"Your Balance is: "<<us.balance<<endl;
	cout<<"Enter Code (Company Number) or exit number: ";
	cin>>x;

	  us.companycodes[us.compno] = x;
	  if (x!=99)
		  {
		   if (us.balance <100)
			   x=99;

		  cout<<"Enter Number of Stocks you want to buy";
		  cin>>m;
		  us.share[us.compno] = m;
		  us.balance -= (float)us.share[us.compno] * com[us.companycodes[us.compno]].stockval;
		  }
	us.compno++;
	}
  timer t;
	 t.start();
 /*	for(i=0;i<10;i++)
	   updateind(ind[i]);
	for(i=0;i<10;i++)
	   updatecomp(com[i]); */
	 while(!kbhit())
	  {

		 if(t.getTime()%5==0)
		   {

			  if(j<=6)
				{
					clrscr();
					cleardevice();
					us.networth = us.balance;
					j++;

					for(i=0;i<us.compno-1;i++)
					updatecomp(com[us.companycodes[i]]);

					for(i=0;i<us.compno-1;i++)
						{
							companydisplay(com[us.companycodes[i]]) ;
							us.networth += us.share[i]* com[us.companycodes[i]].stockval;
						}
					cout<<endl<<"Your Networth is "<<us.networth<<" Of which "<<us.networth - us.balance<<" is from your investments";

					if (j==1)
						delay(5000);
					if(us.networth>20000||us.networth<0)
						goto line;
					delay(1000);
				}
			   else
				{
				 j=0;
				 clrscr();
				 cleardevice();
				 cout<<"Would You Like to continue with your Investments ?"<<endl<<"Enter 1 to continue"<<endl<<"Enter 2 to make new investments";
				 cin>>x;
			   switch (x)
				{
				 case 2: goto start;
				 case 1:
					 clrscr();
					 cleardevice();
					 us.networth = us.balance;
					 j++;
					 for(i=0;i<us.compno-1;i++)
						updatecomp(com[us.companycodes[i]]);
					 for(i=0;i<us.compno-1;i++)
						{
						 companydisplay(com[us.companycodes[i]]) ;
						 us.networth += us.share[i]* com[us.companycodes[i]].stockval;
						}
					 cout<<endl<<"Your Networth is "<<us.networth<<" Of which "<<us.networth - us.balance<<" is from your investments";
					 if(us.networth>15000||us.networth<0)
					 goto line;
					delay(1000);
				 }
			   }

		 }
	   }
 goto b;
 line:
 clrscr();
 cleardevice();
 if(us.networth >20000)
	cout<<"You won! You reached the target of Rs.20,000. Your final networth was "<<us.networth<<endl<<"Congratulations! "<<us.name;
 else
	cout<<"Aww You Lost! You went bankrupt (And in debt), your Final networth was "<<us.networth<<endl<<"Better Luck Next Time, "<<us.name;
	b: getch();
}

void rulespage(void)
	{
	 clrscr();
	 cleardevice();
	 settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
	 outtextxy(20,145,"GUIDELINES:");
	 settextstyle(SMALL_FONT,HORIZ_DIR,4);
	 outtextxy(15,195,"1.At a time a player can choose to invest in any number of companies.");
	 outtextxy(15,205,"2.Please enjoy yourself while doing so and do not be disappointed with your result at the end of 10 minutes.");
	 outtextxy(15,215,"4.The stock market is open for 10 minutes");
	 outtextxy(15,225,"5.Every player recieves $10,000");
	 outtextxy(15,235,"6.The exit code while buying stocks is 99.");
	 outtextxy(15,245,"7.After every minute the stocks which have been bought will be sold.");
	 outtextxy(15,255,"8.If the players networth increases he wins else if his networth decreases to less than half he looses.");
	 outtextxy(15,265,"9.If there is no change in net worth after market time he/she looses.");
	 setcolor(GREEN);
	 settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	 outtextxy(15,275,"Enter C to continue to game or H to home");
	 int x;
	 x = getch();
	 switch(x)
		 {
		  case 'c': game();
			    break;

		  case 'C': game();
			    break;

		  case 'H': homepage();
			    break;

		  case 'h': homepage();
			    break;
		 }
	}

void rectangledraw(int q,int w,int e,int r)
	{
	 for(int j=0;j<4;j++)
		rectangle(q+j,w+j,e-j,r-j);
	}


void homepage(void)
	{
	 clrscr();

	 int gdriver = DETECT, gmode;
	 initgraph(&gdriver,&gmode,"C:\\TURBOC3\\BGI");

	 //coverpage
	 rectangledraw(190,120,430,185);
	 settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
	 outtextxy(215,135,"STOCK-GAME");
	 setcolor(RED);
	 settextstyle(TRIPLEX_FONT, HORIZ_DIR,3);
	 outtextxy(250,215,"1.START");
	 outtextxy(250,245,"2.GUIDELINES");
	 outtextxy(250,275,"3.EXIT");
	 setcolor(WHITE);
	 settextstyle(SMALL_FONT, HORIZ_DIR,4);
	 outtextxy(0,440,"               ------------------------------------------------------------------------");
	 outtextxy(230,450,"BUILT BY: Atmesh and Nidhish");

	 int x;
	 cin>>x;
	 if (x==1)
		   {
		      cleardevice();
		      rectangledraw(190,120,430,185);
		      settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
		      outtextxy(215,135,"STOCK-GAME");
		      settextstyle(SMALL_FONT, HORIZ_DIR,4);
		      outtextxy(0,440,"               ------------------------------------------------------------------------");
		      outtextxy(230,450,"BUILT BY: Atmesh and Nidhish");
		      clrscr();
		      cleardevice();
		      setcolor(RED);
		      settextstyle(TRIPLEX_FONT, HORIZ_DIR,4);
		      delay(1000);
		      clrscr();
		      cleardevice();
		      cout<<"Name:";
		      cin>>us.name;
		      settextstyle(SMALL_FONT, HORIZ_DIR,6);
		      outtextxy(10,25,"Hello!");
		      outtextxy(10,35,"We shall now take you to the List of companies and their");
		      outtextxy(10,45,"stock prices!");
		      delay(5000);
		      game();
		   }
	 else if (x==2)
		 rulespage();
	 else if (x==3)
		  exit(0);
	}

