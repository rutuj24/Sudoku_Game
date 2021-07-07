#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<iostream>
#include<time.h>
#include<windows.h>

using namespace std;

#define UNASSIGNED 0
#define N 9


void random()//changes the seed used by the rand function to get different rand values each time program is run
{
    srand((unsigned)time(0));
}

void grid(int midx, int midy)//prints title, yellow borders, and sudoku grid
{
    setcolor(YELLOW);
    setlinestyle(0,0,4);
    line(0,2,getmaxx(),2);
    rectangle(0,0,getmaxx(),getmaxy());
    setcolor(WHITE);
    setlinestyle(0,0,0);
    settextstyle(6,HORIZ_DIR,5);
    setcolor(9);
    outtextxy(midx+20,20,"SUDOKU");
    setcolor(WHITE);

    for(int i=midx,j=0; i<=midx+306; i=i+34,j++)//grid
    {
        if(j%3==0)
            setlinestyle(0,0,3);
        line(i,midy,i,midy+306);
        setlinestyle(0,0,0);
    }
    for(int i=midy,j=0; i<=midy+306; i=i+34,j++)
    {
        if(j%3==0)
            setlinestyle(0,0,3);
        line(midx,i,midx+306,i);
        setlinestyle(0,0,0);
    }
}

void interchange(int (*a)[9],int (*q)[9])//logic to change 2 nos in the grid
{
    int arr[9],i,j;
    for(i=0; i<9; i++)
    {
        do
        {
            arr[i]=rand()%9+1;
            for(j=0; j<i; j++)
            {
                if(arr[i]==arr[j])
                    break;
            }
        }
        while(j!=i);
    }

    for(i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            a[i][j]=arr[a[i][j]-1];
            if(q[i][j]!=0)
                q[i][j]=a[i][j];
        }
    }
    return;
}


void row(int (*a)[9],int (*q)[9])//swap 2 rows in the grid
{

    int principal=rand()%3;
    int sub=rand()%3;
    int sub1,temp;
    do
    {
        sub1=rand()%3;
    }
    while(sub1==sub);

    int row1=principal*3+sub;
    int row2=principal*3+sub1;

    for(int j=0; j<9; j++)
    {
        //for solution
        temp= a[row1][j];
        a[row1][j]=a[row2][j];
        a[row2][j]=temp;
        //for question
        temp= q[row1][j];
        q[row1][j]=q[row2][j];
        q[row2][j]=temp;
    }
    return;
}

void col(int (*a)[9],int (*q)[9])//swap 2 cols
{

    int principal=rand()%3;
    int sub=rand()%3;

    int sub1,temp;
    do
    {
        sub1=rand()%3;
    }
    while(sub1==sub);

    int col1=principal*3+sub;
    int col2=principal*3+sub1;

    for(int j=0; j<9; j++)
    {
        temp= a[j][col1];
        a[j][col1]=a[j][col2];
        a[j][col2]=temp;

        temp= q[j][col1];
        q[j][col1]=q[j][col2];
        q[j][col2]=temp;
    }
    return;
}


void rows3(int (*a)[9],int (*q)[9])
{
    int sub=rand()%3;
    int sub1;
    do
    {
        sub1=rand()%3;
    }
    while(sub1==sub);

    int temp,i,k;
    for( i=sub*3,k=sub1*3; i<sub*3+3&&k<sub1*3+3; i++,k++)
    {
        for(int j=0; j<9; j++)
        {
            temp=a[i][j];
            a[i][j]=a[k][j];
            a[k][j]=temp;
            temp=q[i][j];
            q[i][j]=q[k][j];
            q[k][j]=temp;

        }
    }

    return ;
}


void cols3(int (*a)[9],int (*q)[9])
{
    int sub=rand()%3;
    int sub1;
    do
    {
        sub1=rand()%3;
    }
    while(sub1==sub);
    int temp,i,k;
    for( i=sub*3,k=sub1*3; i<sub*3+3&&k<sub1*3+3; i++,k++)
    {
        for(int j=0; j<9; j++)
        {
            temp=a[j][i];
            a[j][i]=a[j][k];
            a[j][k]=temp;
            temp=q[j][i];
            q[j][i]=q[j][k];
            q[j][k]=temp;

        }
    }
}
//below functions for solving sudoku
bool UsedInBox(int grid[N][N], int boxStartRow,
               int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] ==
                    num)
                return true;
    return false;
}

bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool isSafe(int grid[N][N], int row,
            int col, int num)
{
    return !UsedInRow(grid, row, num)
           && !UsedInCol(grid, col, num)
           && !UsedInBox(grid, row - row % 3,
                         col - col % 3, num)
           && grid[row][col] == UNASSIGNED;
}


bool FindUnassignedLocation(int grid[N][N],
                            int& row, int& col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

bool SolveSudoku(int grid[N][N])
{
    int row, col;

    if (!FindUnassignedLocation(grid, row, col))
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (SolveSudoku(grid))
                return true;

            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}



int main(void)
{
    random();
    int ne=1;
    int gdriver = DETECT, gmode, errorcode;//graphics code
    initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");

    errorcode = graphresult();
    if (errorcode != grOk)
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);
    }
    while(ne)
    {

        ShowWindow(FindWindow(NULL,"Windows BGI"),SW_MAXIMIZE);//full screen
        DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
        DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);

        int midx, midy;
        int fl=0,hint=0;
        int i,j;
        int activex=0,activey=0;
        char inp[5];
        char ch;
        int a[9][9],s[9][9];
        int q[9][9],cpy[9][9];
        int esc=0,ng=0;
        int cl=3 ;   //color for input



        FILE *fp;//take input from file
        if((fp=fopen("students.txt","r"))==NULL)
        {
            cout<<"error";
        }
        for(i=0; i<9; i++)
            for(j=0; j<9; j++)
            {
                fscanf(fp,"%d",&a[i][j]);
                s[i][j] = 0;
            }
        for(i=0; i<9; i++)
            for( j=0; j<9; j++)
            {
                fscanf(fp,"%d",&q[i][j]);
            }
        fclose(fp);




        for( j=0; j<10000; j++)//make the grid
        {
            interchange(a,q);
            row(a,q);
            col(a,q);
            rows3(a,q);
            cols3(a,q);
        }



        if((fp=fopen("students.txt","w"))==NULL)//return the new values of the grid to the file
        {
            cout<<"error";
        }
        for(i=0; i<9; i++)
        {
            for( j=0; j<9; j++)
                fprintf(fp,"%d ",a[i][j]);
        }
        for( i=0; i<9; i++)
        {
            for( j=0; j<9; j++)
                fprintf(fp,"%d ",q[i][j]);
        }
        fclose(fp);




        for(i=0; i<9; i++)//cpy will be used for comparison later as q will be edited in the process
            for( j=0; j<9; j++)
            {
                cpy[i][j]=q[i][j];
            }



        cleardevice();
        midx = getmaxx() /2-153;
        midy = getmaxy() / 2-153;

        grid(midx, midy);

        setcolor(WHITE);//prints q in the grid
        settextstyle(0,HORIZ_DIR,3);
        for(i=0; i<9; i++)
            for(j=0; j<9; j++)
            {

                if(q[i][j]==0)
                    continue;
                sprintf(inp,"%d",q[i][j]);
                outtextxy(midx+5+i*34,midy+5+j*34,inp);
            }


        settextstyle(0,HORIZ_DIR,2);
        outtextxy(10,200,"S-Submit");
        outtextxy(10,230,"N-New Game");
        outtextxy(10,260,"A-Answer");
        outtextxy(10,290,"C-Clue(3)");
        outtextxy(10,320,"Esc-Exit");
        outtextxy(1200,260,"X-Sudoku Solver");

        setcolor(WHITE);
        settextstyle(0,HORIZ_DIR,3);


        while (1)//inner while loop
        {
            if ( kbhit() )//khbit() checks if key is pressed , present in conio.h
            {
                ch = getch();
                if(int(ch)==0)
                    continue;

                if(ch=='s' || ch=='S')//Submit
                {
                    fl=0;
                    for(i=0; i<9; i++)
                        for(j=0; j<9; j++)
                        {
                            if(a[i][j]!=q[i][j])//checks if all values of q and a are equal and changes f1 accordingly
                            {
                                fl=1;
                                break;

                            }
                        }
                    if(fl==0)
                    {
                        setcolor(6);
                        settextstyle(1,HORIZ_DIR,2);
                        outtextxy(170,midy+330,"HURRAY!!!! YOU SOLVED IT");
                    }
                    else
                    {
                        setcolor(BLUE);
                        setlinestyle(0,0,4);
                        rectangle(90,midy+320,530,midy+360);
                        setcolor(RED);
                        settextstyle(0,HORIZ_DIR,2);
                        outtextxy(170,midy+330,"OOPS!!!! THAT'S WRONG");

                        setfillstyle(SOLID_FILL,BLACK);
                        delay(1000);
                        floodfill(100,midy+325,BLUE);
                        setcolor(GREEN);
                        outtextxy(180,midy+330,"KEEP TRYING!");
                        settextstyle(0,HORIZ_DIR,3);


                    }
                }

                if(ch=='a'||ch=='A')//Answer
                {
                    for(i=0; i<9; i++)
                        for(j=0; j<9; j++)
                        {
                            if(cpy[i][j]==0)//print a grid where the cpy grid has value 0 in yellow color
                            {
                                setcolor(YELLOW);
                                sprintf(inp,"%d",a[i][j]);
                                outtextxy(midx+5+i*34,midy+5+j*34,inp);
                            }
                        }
                    setcolor(GREEN);
                    outtextxy(180,midy+330,"PRESS N OR ESC");
                    settextstyle(0,HORIZ_DIR,3);

                }

                if(ch=='n'||ch=='N')//new grid
                {
                    hint = 0;
                    break;//ends the inner while loop, whole file process is started again
                }


                if (int(ch) == 27)//if escape button is pressed
                {
                    cleardevice();
                    setcolor(GREEN);
                    settextstyle(0,HORIZ_DIR,3);
                    outtextxy(midx-100,midy,"THANKYOU FOR PLAYING");
                    setcolor(RED);
                    settextstyle(0,0,3);
                    outtextxy(midx-30,midy+100,"Press any key");
                    ne=0;//ensures outer loop does not start another iteration
                    break;//ends inner loop
                }

                //tempx=activex;
                //tempy=activey;


                if(ch=='X' || ch=='x')//opens sudoku solver page
                {
                    cleardevice();
                    grid(midx, midy);
                    setcolor(WHITE);
                    settextstyle(0,HORIZ_DIR,2);
                    outtextxy(10,200,"Sudoku Solver");
                    outtextxy(10,230,"Enter the numbers in grid");
                    outtextxy(10,260,"Enter 0 for blank");
                    outtextxy(10,290,"Y-Solve");
                    outtextxy(10,320,"Esc-Exit");
                    outtextxy(1300,260,"Z-Sudoku Game");
                    for(i=0; i<9; i++)
                        for( j=0; j<9; j++)
                        {
                            cpy[i][j]=s[i][j];//all values of q and cpy = 0, so that q = input given by user only
                            q[i][j]=s[i][j];
                        }
                }

                if(ch=='Y' || ch=='y')//solves input sudoku
                {

                    if (SolveSudoku(q) == true)
                    {
                        for(i=0; i<9; i++)
                            for(j=0; j<9; j++)
                            {
                                setcolor(YELLOW);
                                sprintf(inp,"%d",q[i][j]);
                                outtextxy(midx+5+i*34,midy+5+j*34,inp);
                            }
                        setcolor(GREEN);
                        settextstyle(0,HORIZ_DIR,2);
                        outtextxy(170,midy+330,"YOUR SOLUTION");
                    }
                    else
                    {
                        setcolor(RED);
                        settextstyle(0,HORIZ_DIR,2);
                        outtextxy(170,midy+330,"NO SOLUTION EXISTS");
                    }
                }

                if(int(ch)==72)//up movement
                {
                    setfillstyle(SOLID_FILL,0);//last block is turned black from red
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }

                    if(activey==0)
                        activey=8;
                    else
                        activey--;
                    setfillstyle(SOLID_FILL,RED);//color of the current block
                    if(cpy[activex][activey]==0)
                        floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    sprintf(inp,"%d",q[activex][activey]);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }
                }
                if(int(ch)==80)//down
                {
                    setfillstyle(SOLID_FILL,0);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }

                    if(activey==8)
                        activey=0;
                    else
                        activey++;
                    setfillstyle(SOLID_FILL,RED);
                    if(cpy[activex][activey]==0)
                        floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }
                }
                if(int(ch)==75)//left
                {
                    setfillstyle(SOLID_FILL,0);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }

                    if(activex==0)
                        activex=8;
                    else
                        activex--;
                    setfillstyle(SOLID_FILL,RED);
                    if(cpy[activex][activey]==0)
                        floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }
                }
                if(int(ch)==77)//right all the movements have similar codes
                {
                    setfillstyle(SOLID_FILL,0);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }

                    if(activex==8)
                        activex=0;
                    else
                        activex++;
                    setfillstyle(SOLID_FILL,RED);
                    if(cpy[activex][activey]==0)
                        floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    if(q[activex][activey]!=0)
                    {
                        if(cpy[activex][activey]==0)
                            setcolor(cl);
                        else
                            setcolor(WHITE);
                        sprintf(inp,"%d",q[activex][activey]);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                    }
                }

                if(int(ch)>=int('1')&&int(ch)<=('9')&&cpy[activex][activey]==0)//input
                {
                    setfillstyle(SOLID_FILL,BLACK);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    q[activex][activey]=int(ch)-int('1')+1;//sets value of q with current index as input
                    sprintf(inp,"%d",q[activex][activey]);//convert to string
                    setcolor(cl);
                    outtextxy(midx+5+activex*34,midy+5+activey*34,inp);//print on screen

                }

                if(int(ch)==int('0') && cpy[activex][activey]==0)//remove input
                {
                    setfillstyle(SOLID_FILL,BLACK);
                    floodfill(midx+17+activex*34,midy+17+activey*34,WHITE);
                    q[activex][activey]=0;
                    sprintf(inp,"%d",q[activex][activey]);
                    setcolor(BLACK);
                    outtextxy(midx+5+activex*34,midy+5+activey*34,inp);

                }

                if(ch=='c' || ch=='C')//clue
                {
                    if(hint<3)
                    {
                        q[activex][activey]=a[activex][activey];//takes value of current block from the a grid
                        sprintf(inp,"%d",a[activex][activey]);
                        setcolor(RED);
                        outtextxy(midx+5+activex*34,midy+5+activey*34,inp);
                        hint++;
                    }
                    else
                    {
                        setcolor(RED);
                        settextstyle(0,0,3);
                        outtextxy(170,midy+330,"ALL HINTS USED");
                    }

                }

                if(ch=='z' || ch=='Z')//go from solver to game
                {
                    hint = 0;
                    break;
                }

                fl=0;//used in submit function to check if grids are equal
            }
        }
    }
    getch();
    closegraph();
    return 0;
}
