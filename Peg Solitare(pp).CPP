//FINAL VERSION OF PEG SOLITAIRE

//HEADER FILES USED
#include<graphics.h>			//For graphics
#include<stdlib.h>                      //For exit()
#include<iostream.h>                    //For cout
#include<conio.h>                       //For getch()
#include<dos.h>                         //For delay
#include<bios.h>                        //For key input

//DEFINE
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define YES 1
#define NO 0

//GLOBAL VARIABLES
//for mid screen coordinates
int x = 320;
int y = 100;

//Number of marbles in game
int marbles = 32;

//Default marble color i.e. PURPLE
int m_color = 5;

//Area for the graph
size_t area;

//Pointer for dynamically assigning memory to area
void *p;

//Initial board matrix
int board[7][7] =
{
	{-1, -1, 1, 1, 1, -1, -1,},
	{-1, -1, 1, 1, 1, -1, -1,},
	{ 1,  1, 1, 1, 1,  1,  1,},
	{ 1,  1, 1, 0, 1,  1,  1,},
	{ 1,  1, 1, 1, 1,  1,  1,},
	{-1, -1, 1, 1, 1, -1, -1,},
	{-1, -1, 1, 1, 1, -1, -1,}
};

//-------------------------------------------------
//LIST OF FUNCTIONS
//-------------------------------------------------
//Function to open graph
void Graph();
//Function to create marbles
void Marble(int x, int y, int col);
//Function to create background
void Background();
//Function to draw board
void DrawBoard();
//Fnction to get board
int GetBoard(int X, int Y);
//Function to set board
void SetBoard(int X, int Y, int element);
//Function for intro screen
void Intro();
//Function for creating shadows
void winp(int sx, int sy, int ex, int ey, int state);
//Function for creating dialog boxes with title bar
void win(char *text, int sx, int sy, int ex, int ey, int ck);
//Function to draw border
void DrawBorder(int x, int y);
//Function to generate LCD style numbers
void LCD(int left, int top, int NUM);
void Lcd(int x, int y, int n);
//Function to perform blink action
void Blink(int x, int y, int c);
//Function which handles all functions and perform moves
void Init();
//Function to get current coordinates
int GetXY(int X, int Y);
//Function to check for valid moves
int check();
//Function to make a move
int MakeMove(int X, int Y);
//Funtion to display finish page
int finish();

//----------------------------------------------------
//DECLARING FUNCTIONS
//----------------------------------------------------

//1. To open Graph
void Graph()
{
	int gDriver = DETECT;
	int gMode;
	int errorcode;

	//Initialising the graph
	initgraph(&gDriver, &gMode, "C:\\TC\\BGI");
	errorcode = graphresult();
	if(errorcode != grOk)
	{
		cout<<"Graphics Error : "<<grapherrormsg(errorcode);
		exit(1);
	}

	area = imagesize(150, 70, 240, 180);
	p =  new size_t;
	p = &area;
	if(p == NULL)
	{
		closegraph();
		exit(1);
	}
}
//.................end of Graph()................

//2. To create marble
void Marble(int x, int y, int col)
{
	//To set the filling style of the marble
	setfillstyle(1, col);
	//To set the color
	setcolor(col);
	//To draw marble
	fillellipse(x, y, 8, 8);

	if(col != 0)
	{
		if(col == 15)
		{
			setcolor(7);
			setfillstyle(1, 7);
		}
		else
		{
			setcolor(15);
			setfillstyle(1, 15);
		}

		fillellipse(x + 3, y - 2, 1, 2);
	}
}
//.................end of Marble()...............

//3. To create Background
void Background()
{
	int i;

	setfillstyle(1, 6);
	bar(0, 0, 640, 480);

	win("PEG SOLITAIRE", 145, 45, 505, 400, 1);

	win("Keys", 24, 45, 135, 250, 1);

	win("Help !", 510, 45, 625, 250, 1);

	setfillstyle(1, 0);
	bar(35, 75, 125, 240);
	bar(520, 75, 618, 240);
	winp(35, 75, 125, 240, 1);
	winp(520, 75, 618, 240, 1);

	setcolor(14);
	settextstyle(2, 0, 4);
	outtextxy(42, 80, "Keys used");

	setcolor(15);
	outtextxy(42, 100, "+ or - : color");
	outtextxy(47, 120, "\xB3  : Up");
	outtextxy(47, 140, "\xB3  : Down");
	outtextxy(42, 160, "<- : Left");
	outtextxy(42, 180, "-> : Right");
	outtextxy(42, 200, "Enter : Pick");
	outtextxy(42, 220, "Esc : Exit");

	line(47, 120, 50, 123);
	line(47, 120, 43, 123);
	line(47, 154, 50, 151);
	line(47, 154, 43, 151);

	outtextxy(523, 80, "Use Arrow Keys");
	outtextxy(523, 100, "to move around");
	outtextxy(523, 120, "then press enter");
	outtextxy(523, 140, "to select any");
	outtextxy(523, 160, "marble,then jump");
	outtextxy(523, 180, "over another to");
	outtextxy(523, 200, "remove it.");

	win("", 190, 410, 480, 460, 0);

	setfillstyle(1, 0);
	bar(200, 420, 470, 450);

	settextstyle(1, 0, 3);
	setcolor(10);
	outtextxy(220, 420, "Marbles :");

}

//-----------------end of Background()...........

//4. To draw Board
void DrawBoard()
{
    int i, j, x, y;

    //Centre coordinates
	x = 200;
	y = 100;

    //Main Board
	setfillstyle(1, 1);
	//Blue Cross in Middle
    bar(x - 40, y - 20, x + 290, y + 280);

	setfillstyle(1, 7);
	//Left Grey Box(Upper)
    bar(x - 41, y - 21, x + 60, y + 60);
	//Right Grey Box(Upper)
    bar(x + 180, y - 21, x + 290, y + 60);
	//Left Grey Box(Lower)
    bar(x - 41, y + 180, x + 60, y + 290);
	//Right Grey Box(Lower)
    bar(x + 180, y + 180, x + 290, y + 290);

    //Borders of Cross
    DrawBorder(x, y);
    DrawBorder(x + 1, y + 1);

    //Marbles
    for(i = 0; i < 7; i++)
    {
		for(j = 0; j < 7; j++)
		{
		    if(board[j][i] != -1)
		    {
			    if(board[j][i] == 1)
				Marble(x, y, m_color);
			    //Generates black spot after new game
			    if(board[j][i] == 0)
				Marble(x, y, 0);
		    }
		    x += 40;
		}
		x = 200;
		y += 40;
    }
  //  settextstyle(1, 0, 3);
}

//-----------------end of DrawBoard()------------

//5. To get Board
int GetBoard(int X, int Y)
{
    int i, j, x, y, f = -1;

    //Centre coordinates
    x = 200;
    y = 100;
    for(i = 0; i < 7; i++)
    {
		for(j = 0; j < 7; j++)
		{
		    if(board[j][i] != -1)
		    {
			if(x == X && y == Y)
			f = board[j][i];
		    }
		    x += 40;
		}
		x = 200;
		y += 40;
    }
    return f;
}

//-----------------end of GetBoard()-------------

//6. To set Board
void SetBoard(int X, int Y, int element)
{
   int i, j, x, y;

   //Centre coordinates
   x = 200;
   y = 100;
   for(i = 0; i < 7; i++)
   {
		for(j = 0; j < 7; j++)
		{
	    if(board[j][i] != -1)
		{
		if(x == X && y == Y)
			board[j][i] = element;
		}
		    x += 40;
		}
		x = 200;
		y += 40;
    }
}

//-----------------end of SetBoard()-------------

//7. Introduction page
void Intro()
{
	int i;
	char pattern[8] ={0xfe, 0xbc, 0xda, 0xe4, 0xe2, 0xc0, 0x88, 0x00};

	setfillpattern(pattern, 8);
	bar(0, 0, 640, 480);

	settextstyle(1, 0, 5);
	setcolor(10);

	getch();

	setcolor(0);

	for(i = 0; i <= 320; i++)
	{
		rectangle(0 + i, 0, 640 - i, 480);
		delay(5);
	}

	for(i=0;i<=15;i++)
	{
		setcolor(i);
		rectangle(0+i,0+i,640-i,480-i);
		delay(200);
	}

	settextstyle(1,HORIZ_DIR,5);
	setcolor(4);
	outtextxy(20,10,"SYMBIOSIS");
	delay(1000);
	outtextxy(285,10,"INSTITUTE");
	delay(1000);
	outtextxy(550,10,"OF");
	delay(1000);
	outtextxy(200,60,"TECHNOLOGY");
	delay(1000);
	settextstyle(BOLD_FONT,HORIZ_DIR,5);
	setcolor(YELLOW);
	outtextxy(240,110,"PEG");
	outtextxy(150,210,"SOLITAIRE");
	setusercharsize(130,70,130,90);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	setcolor(GREEN);

	setfillstyle(LTBKSLASH_FILL,GREEN);

	circle(180,160,10);
	circle(430,160,10);
	circle(110,270,10);
	circle(510,270,10);
	circle(60,160,10);
	circle(560,160,10);
	circle(468,207,10);
	circle(150,207,10);
	circle(85,207,10);
	circle(540,207,10);
	circle(120,160,10);
	circle(495,160,10);
	circle(150,330,10);
	circle(480,330,10);
	circle(275,330,10);
	circle(380,330,10);
	floodfill(180,160,GREEN);
	floodfill(430,160,GREEN);
	floodfill(110,270,GREEN);
	floodfill(510,270,GREEN);
	floodfill(60,160,GREEN);
	floodfill(560,160,GREEN);
	floodfill(468,207,GREEN);
	floodfill(150,207,GREEN);
	floodfill(85,207,GREEN);
	floodfill(540,207,GREEN);

	setcolor(15);
	settextstyle(1,HORIZ_DIR,2);
	outtextxy(430,370,"NEHA YADAV");
	outtextxy(430,390,"PRASHANT MALL");
	outtextxy(430,410,"RAJESHWAR SINGH");
	outtextxy(430,430,"YAMINI GAHLOT");
	delay(2000);
	for(i=0;i<=15;i++)
	{
		cleardevice();
		setcolor(i);
		setfillstyle(SOLID_FILL,i);
		fillellipse(10,20+i*25,9,9);
		fillellipse(100,20+i*25,9,9);
		fillellipse(200,20+i*25,9,9);
		fillellipse(300,20+i*25,9,9);
		fillellipse(400,20+i*25,9,9);
		fillellipse(500,20+i*25,9,9);
		fillellipse(600,20+i*25,9,9);
		fillellipse(700,20+i*25,9,9);
		fillellipse(800,20+i*25,9,9);
		fillellipse(900,20+i*25,9,9);
		delay(300);
	}
	getch();
}

//-----------------end of Intro()----------------

//8. To create dialog and message box
void win(char *text, int sx, int sy, int ex, int ey, int ck)
{

	//For Grey pane (Centre One)
	setfillstyle(1, 7);
	bar(sx, sy, ex, ey);

	//Outside of all 3 boxes
	setfillstyle(1, 7);

	//Black Border lines (Shadow)
	setcolor(15);
	line(sx, sy, sx, ey);
	line(sx, sy, ex, sy);
	line(sx, sy, sx, ey);
	line(sx, sy, ex, sy);

	//White Border lines (Shadow)
	setcolor(0);
	line(ex, sy, ex, ey);
	line(ex, sy, ex, ey);
	line(sx, ey, ex, ey);
	line(sx, ey, ex, ey);

	if(ck == 1)
	{
		//Green Bar
		settextstyle(0, 0, 0);
		setfillstyle(1, 2);
		bar(sx + 2, sy + 2, ex - 2, sy + 17);

		//To print Text
		setcolor(15);
		outtextxy(sx + 4, sy + 4, text);
	}
}

//-----------------endl of win()-----------------

//9. To create title bar
void winp(int sx, int sy, int ex, int ey, int state)
{
    if(state == 1)
    {
	//To provide Black lines(Shadow) Horizontal
	    setcolor(0);
	    line(sx, sy, sx, ey);
	    line(sx, sy, ex, sy);

		//To provide White lines(Shadow) Vertical
		setcolor(15);
	    line(ex, sy, ex, ey);
	    line(sx, ey, ex, ey);
   }
   else
   {
		//To provide White lines(Shadow) Horizontal
	    setcolor(15);
	    line(sx, sy, sx, ey);
	    line(sx, sy, ex, sy);

	    //To provide Black lines(Shadow) Vertical
		setcolor(0);
	    line(ex, sy, ex, ey);
	    line(sx, ey, ex, ey);
   }
}

//-----------------end of winp()-----------------

//10. To draw border
void DrawBorder(int x, int y)
{
    setwritemode(COPY_PUT);

    setcolor(0);
    line(x + 60, y - 20, x + 180, y - 20);		//       __
    line(x + 60, y + 60, x + 60, y - 20);		//      |
    line(x - 40, y + 60, x + 60, y + 60);		//   __
    line(x - 40, y + 60, x - 40, y + 180);		// |

    setcolor(15);
    line(x - 40, y + 180, x + 60, y + 180);	// __

    setcolor(0);
    line(x + 60, y + 180, x + 60, y + 280);	//   |

    setcolor(15);
    line(x + 180, y - 20, x + 180, y + 60);	//        |

    setcolor(0);
    line(x + 180, y + 60, x + 290, y + 60);	//         __

    setcolor(15);
    line(x + 290, y + 60, x + 290, y + 180);	//          |
    line(x + 180, y + 180, x + 290, y + 180);	//       __
    line(x + 180, y + 180, x + 180, y + 280);	//      |
    line(x + 180, y + 280, x + 60, y + 280);	//    __

    setwritemode(XOR_PUT);
}

//-----------------end of DrawBorder-------------

//11. To draw LCD numbers
void LCD(int left, int top, int NUM)
{
	int i;

	setcolor(10);

	//To draw LCD numbers
	switch(NUM)
	{
	    case 1:
				line(left + 11, top + 2, left + 11, top + 9);	//  |
				line(left + 11, top + 11, left + 11, top + 18);	//  |
				break;
		case 2:
				line(left, top, left + 10, top);		//--
				line(left + 11, top + 2, left + 11, top + 9);	//  |
				line(left + 1, top + 10, left + 9, top + 10);	//--
				line(left - 1, top + 11, left - 1, top + 18);	//|
				line(left, top + 20, left + 10, top + 20);	//--
				break;
		case 3:
			    line(left, top, left + 10, top);		//--
				line(left + 11, top + 2,left + 11, top + 9);	//  |
				line(left + 1, top + 10, left + 9, top + 10);	//--
				line(left + 11, top + 11, left + 11, top + 18);	//  |
				line(left, top + 20, left + 10, top + 20);	//--
				break;
		case 4:
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 11, top + 2, left + 11, top + 9);	//  |
			    line(left + 1, top + 10, left + 9, top + 10);	//--
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    break;
		case 5:
			    line(left, top, left + 10, top);		//--
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 1, top + 10, left + 9, top + 10);	//--
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    line(left, top + 20, left + 10, top + 20);	//--
			    break;
		case 6:
			    line(left, top, left + 10, top);		//--
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 1, top + 10, left + 9, top + 10);	//--
			    line(left - 1, top + 11, left - 1, top + 18);	//|
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    line(left, top + 20, left + 10, top + 20);	//--
			    break;
		case 7:
			    line(left, top, left + 10, top);		//--
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 11, top + 2, left + 11, top + 9);	//  |
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    break;
		case 8:
			    line(left, top, left + 10, top);		//--
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 11, top + 2, left + 11, top + 9);	//  |
			    line(left + 1, top + 10, left + 9, top + 10);	//--
			    line(left - 1, top + 11, left - 1, top + 18);	//|
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    line(left, top + 20, left + 10, top + 20);	//--
			    break;
		case 9:
			    line(left, top, left + 10, top);		//--
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 11, top + 2, left + 11, top + 9);	//  |
			    line(left + 1, top + 10, left + 9, top + 10);	//--
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    line(left, top + 20, left + 10, top + 20);	//--
			    break;
		case 0:
			    line(left, top, left + 10, top);		//--
			    line(left - 1, top + 2, left - 1, top + 9);	//|
			    line(left + 11, top + 2, left + 11, top + 9);	//  |
			    line(left - 1, top + 11, left - 1, top + 18);	//|
			    line(left + 11, top + 11, left + 11, top + 18);	//  |
			    line(left, top + 20, left + 10, top + 20);	//--
			    break;
	}
}

//-----------------end of LCD()------------------

//12. To check the LCD numbers
void Lcd(int x, int y, int n)
{
	int a, b;

	if(n < 10)
	{
		LCD(x, y, 0);
		LCD(x + 15, y, n);
	}
	else if(n < 100)
	{
		a = n / 10;
		b = n % 10;

		LCD(x, y, a);
		LCD(x + 15, y, b);
	}
}

//-----------------end of Lcd()------------------

//13. This Function make the box around marble blink
void Blink(int x, int y, int c)
{
	int i;

	setcolor(c);

	do
	{
		rectangle(x - 10, y - 10, x + 10, y + 10);
		rectangle(x - 11, y - 11, x + 11, y + 11);
		delay(100);
		rectangle(x - 10, y - 10, x + 10, y + 10);
		rectangle(x - 11, y - 11, x + 11, y + 11);
		delay(100);
	}while(!kbhit());
}

//-----------------end of blink()----------------

//14. Handles all the functions and performs desired move
void Init()
{
	int i, j, e = 1;
	char ch;

	setwritemode(XOR_PUT);
	setcolor(15);

	while(e)
	{
		setfillstyle(1,11);

		Lcd(360,425,marbles);

		Blink(x,y,11);

		ch=getch();

		Lcd(360,425,marbles);

		if(ch == ESC)
			e = 0;
		if(GetXY(x, y) == 1)
		{
			switch(ch)
			{
				case UP:	if(GetXY(x, y - 40) == 1)
								if(y > 100)
									y -= 40;
						break;
				case DOWN:	if(GetXY(x, y + 40) == 1)
								if(y < 340)
									y += 40;
						break;
				case LEFT:	if(GetXY(x - 40, y) == 1)
								if(x > 200)
									x -= 40;
						break;
				case RIGHT:	if(GetXY(x + 40, y) == 1)
								if(x < 440)
									x += 40;
						break;
				case ENTER:	if(GetBoard(x, y) == 1)
						{
							MakeMove(x, y);
						}
						break;
				case ESC:	e = 0;
						break;
				case '+':	m_color++;
							if(m_color > 15)
								m_color = 2;
							DrawBoard();
						break;
				case '-':	m_color--;
							if(m_color < 2)
								m_color = 15;
							DrawBoard();
						break;
			}//switch
		}//if

		if(check() == 0)
			e = finish();
	}//while
  setwritemode(COPY_PUT);
}

//-----------------end of Init()-----------------

//15.Gives current x, y position and find if it is valid or not
int GetXY(int X, int Y)
{
	int i, j, x, y, flag = 0;

	x = 200;
	y = 100;

	for(i = 0; i < 7; i++)
	{
		for(j = 0; j < 7; j++)
		{
		if(board[j][i] != -1)
		{
			if(x == X && y == Y)
				flag = 1;
		}
			x += 40;
		}
		x = 200;
		y += 40;
	}
	return flag;
}

//-----------------end of GetXY()----------------

//16. Check the board if any move is possible
int check()
{
   int i, j, flag;

   flag = 0;

   for(i = 0; i < 7; i++)
   {
		for(j = 0; j < 7; j++)
		{
		
			if(board[j][i] != -1)
			{
				if(board[j][i] == 1)
				{
					if(board[j + 1][i] == 1)
					{
						if(board[j + 2][i] == 0)
							flag++;
					}
					if(board[j - 1][i] == 1)
					{
						if(board[j - 2][i] == 0)
							flag++;
					}
		
					if(board[j][i + 1] == 1)
					{
						if(board[j][i + 2] == 0)
							flag++;
					}
					if(board[j][i - 1] == 1)
					{
						if(board[j][i - 2] == 0)
							flag++;
					}
				}
			}
	   }
	}

   //count number of marbles
   marbles = 0;

   for(i = 0; i < 7; i++)
   {
    for(j = 0; j < 7; j++)
	if(board[j][i] == 1)
		marbles++;
   }

   return flag;
}

//-----------------end of check()----------------

//17. Checks for conditions and perform task
int MakeMove(int X,int Y)
{
	int flag, key;

	flag = NO;

	//to change the color of selected marble
	if(m_color == 11)
		Marble(X, Y, 9);
	else
		Marble(X, Y, 11);

	//take the keystroke and compare
	key = bioskey(0);

	//checking for empty space around selected marble
	if(key == 0x4800)	//up key
	{
		if(GetBoard(X, Y - 80) == 0 && GetBoard(X, Y - 40) == 1)
		{
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			Y -= 40;
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			Y -= 40;
			SetBoard(X, Y, 1);
			y = Y;
			
			flag = YES;
		}
	}

	if(key == 0x5000)	//down key
	{
		if(GetBoard(X, Y + 80) == 0 && GetBoard(X, Y + 40) == 1)
		{
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			Y += 40;
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			Y += 40;
			SetBoard(X, Y, 1);
			y = Y;
			
			flag = YES;
		}
	}
	if(key == 0x4b00) //left key
	{
		if(GetBoard(X - 80, Y) == 0 && GetBoard(X - 40, Y) == 1)
		{
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			X -= 40;
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			X -= 40;
			SetBoard(X, Y, 1);
			x = X;
			
			flag = YES;
		}
	}
	if(key == 0x4d00)	//right key
	{
		if(GetBoard(X + 80, Y) == 0 && GetBoard(X + 40, Y) == 1)
		{
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			X += 40;
			Marble(X, Y, 0);
			SetBoard(X, Y, 0);
			X += 40;
			SetBoard(X, Y, 1);
			x = X;
			
			flag = YES;
		}
	}
	if(kbhit())
		getch();

	setcolor(11);

	if(flag == YES)
	{
		Marble(X, Y, m_color);
	}
	else				//if invalid key is pressed
	{
		Marble(X, Y, m_color);
		sound(800);
		delay(100);
		nosound();
	}

	  return flag;
}

//-----------------end of MakeMove()-------------

//18. Display the final screen
int finish()
{
    int i, j, f;
    char opt = 0;

	setwritemode(COPY_PUT);

	f = 0;

	for(i = 0; i < 7; i++)
    {
	for(j = 0; j < 7; j++)
		if(board[j][i] == 1)
			f++;
    }

	Lcd(360, 425, marbles);

    win("Done !",220, 155, 425, 240, 1);

	setcolor(0);
    settextstyle(1, 0, 1);

	switch(f)
    {
		case 1:	outtextxy(230, 180, "You Are Intelligent !");
				break;
		case 2:	outtextxy(255, 180,"    Wonderful !");
				break;
		case 3:	outtextxy(255, 180,"  Good Job !");
				break;
		case 4:	outtextxy(255, 180,"  Can be better !");
				break;
		case 5:	outtextxy(230, 180," You Need Practice !");
				break;
		case 6:	outtextxy(230, 180,"   Very Poor !");
				break;
		case 7:	outtextxy(230, 180," Very Very Poor !");
				break;
		default:outtextxy(255, 180," Try Again !");
				break;
    }

    getch();

	win("Exit ?", 220, 155, 425, 240, 1);

	settextstyle(1, 0, 1);
    setcolor(1);

	outtextxy(240, 180, "Play Again [y/n] :");

	opt = getch();

	setfillstyle(1, 3);
    bar(17, 402, 624, 464);

    //Restarting the Game
	if(opt == 'y' || opt == 'Y')
    {
	for(i = 0; i < 7; i++)
	{
			for(j = 0; j < 7; j++)
				if(board[j][i] != -1)
					board[j][i] = 1;
	}

	//Making all marbles
	Marble(320, 220, 0);

	//Reseting board
	board[3][3] = 0;

	//Reseting number of marbles
	marbles = 32;

	//Reseting background and drawing board
	Background();
	DrawBoard();

	f = 1;
    }
    else
	f = 0;

	setwritemode(XOR_PUT);

	return f;
}

//-----------------end of finish()---------------

//19.

//MAIN FUNCTION
int main()
{
	int i;

	//Opening the Graph
	Graph();

	//Intro page
	Intro();

	//Constucting Background
	Background();

	//Drawing the Board for Gameplay
	DrawBoard();

	//Setting up the Marbles
	Marble(320, 220, 0);

	//Initialising the Board
	board[3][3] = 0;

	//Starting the Game
	Init();

	setcolor(0);

	//For Animation at exit
	for(i = 0; i <= 220; i++)
	{
		rectangle(0 + i, 0 + i, 640 - i, 480 - i);
		delay(10);
	}

	for(i = 0; i <= 220; i++)
	{
		rectangle(100 + i, 100, 540 - i, 380);
		delay(8);
	}

	closegraph();

	getch();

	return 0;
}

