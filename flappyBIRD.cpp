#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
#include<time.h>

using namespace std;
void LoadData(char arena[37][136]);
void gotoxy(int x, int y);
void map(char arena[37][136]);

void bird(int X,int Y,char arena[37][136]);
void move(int &X, int n, char arena[37][136]);

void Pillars(char arena[37][136]);
void movingPillars(char arena[37][136]);
bool line(char arena[37][136]);
void createPillar(char arena[37][136]);
void displayPillar(char arena[37][136]);
void makeGap(char arena[37][136],int n, int y);
bool running = true;

main()
{
    char arena[37][136];
    int X = 17,Y = 7;
    
    srand(time(0));
    LoadData(arena);
    system("cls");
    Pillars(arena);
    map(arena);
    
    getch();

    while(!GetAsyncKeyState(VK_ESCAPE) && running == true)
    {
        // Sleep(100);
        movingPillars(arena);

        if(GetAsyncKeyState(VK_UP))
        {
            move(X,-1,arena);
            bird(X,Y,arena);
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            move(X,1,arena);
            bird(X,Y,arena);
        }
        else
        {
            bird(X,Y,arena);
        }
    }
}

void LoadData(char arena[37][136])
{
    int c;
    fstream file;
    file.open("map.txt",ios::in);

    for(int i=0; i<37; i++)
    {
        for(int j=0; j<136; j++)
        {
            file >> c;
            arena[i][j] = char(c);
        }
    }
    file.close();

    arena[17][7] = char(218);
    arena[17][8] = char(2);
    arena[17][9] = char(191);
}

void gotoxy(int x, int y)
{
COORD coordinates;
coordinates.X = x;
coordinates.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void map(char arena[37][136])
{
    gotoxy(0,0);
    for(int i=0; i<37; i++)
    {
        for(int j=0; j<136; j++)
        {
            cout << arena[i][j];
        }
        cout << endl;
    }
}

void bird(int X,int Y, char arena[37][136])
{
    if(arena[X][7] != char(219) && arena[X][8] != char(219) && arena[X][9] != char(219))
    {
        arena[X][7] = char(218);
        arena[X][8] = char(2);
        arena[X][9] = char(191);
    }
    else{
        running = false;
    }

    gotoxy(Y,X);
    cout << char(218) << char(2) << char(191);
}

void move(int &X, int n, char arena[37][136])
{
    if((n == -1 && X > 2) || (n == 1 && X < 34))
    {
        arena[X][7] = arena[X][8] = arena[X][9] = ' ';
        gotoxy(7,X);
        cout << "   ";
        X = X + n;
    }
}

void Pillars(char arena[37][136])
{
    int Y = 19, s = 23, n;
    for(int i=2; i<35; i++)
    {
        for(int j=0;j<7;j++)
        {
            arena[i][Y+j] = char(219);
            arena[i][Y+1*s+j] = char(219);
            arena[i][Y+2*s+j] = char(219);
            arena[i][Y+3*s+j] = char(219);
            arena[i][Y+4*s+j] = char(219);        
        }
    }

    makeGap(arena,2,19);
    makeGap(arena,rand()%5,19+23);
    makeGap(arena,rand()%5,19+2*23);
    makeGap(arena,rand()%5,19+3*23);
    makeGap(arena,rand()%5,19+4*23);
}

void movingPillars(char arena[37][136])
{
    int Y = 19, s = 23;

    for(int j=3;j<132;j++)
    {
        if(arena[2][j] == char(219))
        {
            for(int i=2; i<35; i++)
            {
                if(arena[i][j]!=' ')
                {
                    arena[i][j-1] = arena[i][j];
                    gotoxy(j-1,i);
                    cout << arena[i][j-1];

                    arena[i][j+6] = ' ';
                    gotoxy(j+6,i);
                    cout << ' ';
                }
                
            }
            j+=23;
        }
    }

    if(line(arena))
    {
        for(int i=2; i<35; i++)
        {
            for(int j=3; j<10; j++)
            {
                arena[i][j] = ' ';
                gotoxy(j,i);
                cout << ' ';
            }
        }
        createPillar(arena);
    }
}

bool line(char arena[37][136])
{
    for(int i=2;i<35;i++)
    {
        if(arena[i][3] == char(219))
        return 1;
    }
    return 0;
}

void createPillar(char arena[37][136])
{
    int Y = 19, s = 23, n = rand()%5;
    for(int i=2; i<35; i++)
    {
        for(int j=0;j<7;j++)
        {
            arena[i][117+j] = char(219);
        }
    }

    makeGap(arena,rand()%5,117);
    displayPillar(arena);
}

void displayPillar(char arena[37][136])
{
    for(int i=2; i<35; i++)
    {
        gotoxy(117,i);
        for(int j=0;j<7;j++)
        {
            cout << arena[i][j];
        }
        cout << endl;
    }
}

void makeGap(char arena[37][136],int n, int y)
{
    n = n*6 + 3;
    for(int i = n; i<n+6;i++)
    {
        for(int j = y; j<y+7; j++)
        {
            arena[i][j] = ' ';
        }
        cout << endl;
    }
}

