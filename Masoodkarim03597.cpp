#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Structure to keep track of various locations
struct Point
{
    int x;
    int y;

    Point(int _x, int _y): x(_x), y(_y)
    {
    	
    }
};
//Structure for the Player object
struct Player
{
    int food;
    int health;
    bool alive;
    int x;
    int y;
    Player()
    {
        food = 64;
        health = 10;
        alive = true;
    }
    void loseHealth()
    {
        if(health>0)
            health--;
        if(health==0)
            alive = false;
    }
    void gainHealth()
    {
        if(health<10)
            health++;
    }
};

typedef const int cint;        
typedef const Point cPoint;

char* CreateDungeon(int, int, Point&, Point&);      //Creates the dungeon
void Traversal(char*, Point&, cPoint&, cint, cint); //Used for moving inside dungeon
void Combat(Player&, int);  //Used for simulating combat
void TrapStatements();  //3 statements that show at random when the player activates a trap
void FoodStatements();  //3 statements that show at random when the player finds food
void HitStatements();   //3 statements that show at random when the player hits enemy
void GetHitStatements();//3 statements that show at random when the player gets hit
void NextPosition(char* d,int R,int C,int w,Player& objectect); // has conditions for player when it encounters elements inside dungeon
void Print(char* d,int h,int w);// to print dungeon
int main ()
{
    srand(time(0));

    int width = 0;
    int height = 0;

    cout<<"width? ";
    cin>> width;
    cout<<"height? ";
    cin>> height;


    Point startPoint(0,0);
    Point exitPoint(0,0);

    char* dungeon = NULL;
    Player p1;
    dungeon = CreateDungeon(width, height, startPoint, exitPoint);

    Traversal(dungeon, startPoint, exitPoint, width, height);

    delete[]dungeon; // to free memory

    return 0;
}

void TrapStatements()
{
int Random=rand()%3;
if (Random==0)
{ cout<<" You fell into a gutter! hopefully its morning and everything smells fresh! "<<endl;
}
else if (Random==1)
{
  cout<<" You ran into a woman! She pulled your hair and draged you against the floor untill she realized that you were not her Ex! "<<endl;
}
else
{
  cout<<"you were fooled! There is another assignment coming out on monday to Bamboozle you! "<<endl;
}

}


void FoodStatements()
{
int Random=rand()%3;
if (Random==0)
{ cout<<" There you go! Have some pickles with chilled garlic sauce!"<<endl;
}
else if (Random==1)
{
  cout<<" This apple might last you for a couple of months! "<<endl;
}
else
{
  cout<<" Finallllly! Your favourite Kawwa Biryani will be served with extra wings and crow milk !"<<endl;
}

}


void HitStatements()
{
int Random=rand()%3;
if (Random==0)
{ cout<<" Wow! incredible Technique! you kept scrutining the enemy until he exploded into tears!"<<endl;
cout<<" You killed an enemy!"<<endl;
}
else if (Random==1)
{
  cout<<" Legendary! Your stupid jokes compelled enemy to commit Suicide!"<<endl;
  cout<<" You killed an innocent!"<<endl;
}
else
{
  cout<<" Good God! enemy couldnt breathe because sometimes its good not to take a bath! "<<endl;
  cout<<" enemy stinked annd killed!"<<endl;
}
}

void GetHitStatements()
{
int Random=rand()%3;
if (Random==0)
{ cout<<" You got a shot in the head!"<<endl;
cout<<" You lost 1 Helth!"<<endl;
}
else if (Random==1)
{
  cout<<"That pinch is really going to kill you!"<<endl;
  cout<<" You lost 1 Helth!"<<endl;
}
else
{
  cout<<" OOOOH Man! you really suck at fighting "<<endl;
  cout<<" You lost 1 Helth!"<<endl;
}
}

void Combat(Player& player, int enemies)
{
Player object;
int count=0;
cout<<"*********Fight loser!*********"<<endl;
while (count<=enemies)
{
int  RandomHit= (rand()%10)+1;
  if (RandomHit<4)
  {
   HitStatements();
   count++;
  }
  else if (RandomHit==5)
  {
  GetHitStatements();
  player.loseHealth();
  }
}
cout<<"*******dandli hui hai!******"<<endl;
}

char* CreateDungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint)
      {  
	  int capacity =   width * height;
char *Size;
Size= new char[capacity];
srand(time(0));
    int count=0;
for (int i=0; i<height; i++)
{

for(int j=0; j<width; j++)
{
// condition to create outer walls!
if ((i==0) | (j==0) |  (i==height-1 ) | (j==width-1))
{
Size[count]='w';
count+=1;
}
else
{
	//to get an empty dungeon
Size[count]=' ';
    count+=1;
}
}
cout<<endl;
   }
   //placement of trap,enemy,food,inner walls and health!
for(int k=0; k<capacity;k++)
{
  if ( Size[k]==' ')
  {
  int Random1 = rand()%5;
  if ( Random1==1)
  {
    int Random2 = rand()%100;

  if (Random2 < 15 )
  {
  Size[k] = 'E';
  }
  else if (Random2<30)
  {
  Size[k] = 'H';
  }
  else if (Random2< 45 )
  {
  Size[k] = 'T';
  }
  else if ( Random2<60)
  {
  Size[k] = 'F';
   }
  else
  {
  Size[k] = 'w';
   }
   }
  }

} 
// initializing position of player and exit point
ref_startPoint.x=1;
ref_startPoint.y=1;
Size[ref_startPoint.x*width+ref_startPoint.y]='P';

ref_exitPoint.x= width-2;
ref_exitPoint.y=height-2;
Size[ref_exitPoint.x*width+ref_exitPoint.y]='X';
return Size;
}

// to print function
void Print(char* Size,int h,int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cout<<Size[i*w+j];
        }
        cout<<endl;
    }
}
void Traversal(char* dungeon, Point& startPoint, cPoint& exitPoint, cint width, cint height)
{
    cout<<"After being captured by a raid of some robbers on your caravan"<<endl;
    cout<<"you find yourself alone in a dark dungeon. With nothing but your"<<endl;
    cout<<"wits,you chose to take a step...."<<endl;
    // creating object and initializing it to Point!
    struct Player p1;
    p1.x=startPoint.x;
    p1.y=startPoint.y;
    //while true game will run!
    while(p1.food>0 & p1.health>0 & p1.alive==true){// compare(p1.x,p1.y,exitPoint.x,exitPoint.y)!=true){
        Print(dungeon,height,width);
        p1.food--;
        char input;
        cout<<"The keys for moving up,down,left and right are: u,d,l,r and if you like to exit press x: "<<endl;
        cin>>input;
        //to move up
        if(input=='u'){
            p1.x--;
            if(dungeon[((p1.x))*width+p1.y]=='w'){cout<<"You are at the edge of the room"<<endl;p1.x++;}
            else{
                 NextPosition(dungeon,p1.x,p1.y,width,p1);
                 dungeon[(p1.x+1)*width+p1.y]=' ';  /// assign empty space to preceding position of player
            }
        }
        //to  move down
        if(input=='d'){
            p1.x++;
            if(dungeon[(p1.x)*width+p1.y]=='w'){cout<<"You are at the edge of the room"<<endl;p1.x--;}
            else{
            NextPosition(dungeon,p1.x,p1.y,width,p1);
            dungeon[(p1.x-1)*width+p1.y]=' ';
            }
        }
        //to move to the left
        if(input=='l'){
            p1.y--;
            if(dungeon[((p1.x))*width+(p1.y)]=='w'){cout<<"You are at the edge of the room"<<endl;p1.y++;}
            else{
            NextPosition(dungeon,p1.x,p1.y,width,p1);
            dungeon[(p1.x)*width+(p1.y+1)]=' ';
            }
        }
        //to move to the right
        if(input=='r'){
            p1.y++;
            if(dungeon[((p1.x))*width+(p1.y)]=='w'){cout<<"You are at the edge of the room"<<endl<<p1.y--;}
            else{
            NextPosition(dungeon,p1.x,p1.y,width,p1);
            dungeon[(p1.x)*width+(p1.y-1)]=' ';//  assigning empty space to player's previous position
            }
        }
    cout<<"you have food left for "<<p1.food<<" more turns "<<endl;
        
        if(input=='x')
        {
        	p1.alive=true;
        	
		}
        

}
}
void NextPosition(char* d,int R,int C,int w,Player& object){
	        if (d[(R)*w+C]=='X'){
	        	object.alive=false;
			}
			
            else if(d[(R)*w+C]=='T'){
            d[(R)*w+C]='P';
            TrapStatements();
            object.loseHealth();
            cout<<endl<<"your current health is: "<<object.health<<endl;
            }
            else if(d[(R)*w+C]=='F'){d[(R)*w+C]='P';
            //random food generator
            int FoodNum=(rand()%5)+4;
            object.food+=FoodNum;
            cout<<"you gained food for "<< FoodNum << " moves!"<<endl;
            cout<<"current food is "<<object.food<<endl;
            FoodStatements();
            }
            else if(d[(R)*w+C]=='H'){d[(R)*w+C]='P';
            cout<<"You gained health"<<endl;
            object.gainHealth();
            cout<<"current health:"<<object.health<<endl;}
            else if(d[(R)*w+C]=='E'){d[(R)*w+C]='P';
            cout<<"Enemy alert! either fight like a king or go Panama!"<<endl;
            //random enemy generator
            int enemies=(rand()%3)+2;
            cout<<"enemies"<<enemies;
            Combat(object,enemies);
            }
            else{
            d[(R)*w+C]='P';
            }
}


