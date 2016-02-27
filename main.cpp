#include <curses.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

//Cursor moving function prototypes
int moveRight(int x, int maxX);
int moveLeft(int x);
int moveDown(int y, int maxY);
int moveUp(int y);

int main()
{
    initscr();//initializes screen
    WINDOW* macWin = NULL;

    WINDOW *getwin(FILE *MacroFile);

    //Scrolling mechanisms
    //int scroll(WINDOW *macwin);

    //int scrl(int n);

    int wscrl(WINDOW *macwin, int n);






    using namespace std;



    vector<string> strVec;

    string  fName = "MacroFile";
    string line;
    string pLine; //print line
    char quit;//determines whether to quit the program or not
    ifstream iData;
    ofstream oName;
    int cursPos; //cursor movement
    int x=0;
    int y=0;



    iData.open(fName.c_str());

    while(iData.good())
    {
        getline(iData, line);

        strVec.push_back(line);


    }//end while


    //Set the heigh and width of the window
    int nHeight = 0;
    int nWidth = 0;
    macWin = newwin(nHeight, nWidth, y, x);

    nHeight = getmaxy(stdscr);
    nWidth = getmaxx(stdscr);



    scrollok(macWin, TRUE);

    int scr_set(const char *fName);
    int scr_init(const char *fName); //reads in the contents of the filename


    keypad(macWin, TRUE);
    wrefresh(stdscr);

    for(int i = 0; i<strVec.capacity(); i++)
    {
        pLine = strVec[i];

        waddstr(macWin, const_cast<char *>(pLine.c_str()));
        strVec.pop_back();

        wrefresh(macWin);
    }

    //Moving the cursor in the cardinal directions
    while (true)
    {

        wmove(macWin, y, x);
        //quit = wgetch(macWin);

        cursPos = wgetch(macWin);
        wmove(macWin, y, x);
        if(cursPos == KEY_DOWN)
        {
            y = moveDown(y, nHeight);

        }
        else if(cursPos == KEY_UP)
        {
            y = moveUp(y);
        }
        else if(cursPos == KEY_LEFT)
        {
            x = moveLeft(x);
        }
        else if(cursPos == KEY_RIGHT)
        {
            x = moveRight(x, nWidth);
        }
        else if(cursPos == KEY_BACKSPACE)
        {
            x = moveLeft(x);
            wdelch(macWin);
            //x = moveLeft(x);
        }
        else if (cursPos == '!')
        {
            break;
        }
        else
        {
        waddch(macWin, cursPos);
        x = moveRight(x, nWidth);
        }

        wrefresh(macWin);

    }

    //printw("Hello World");

    //wgetch(macWin);//waits for character input
    endwin();
    return 0;



}//end main


//Cursor moving functions
int moveRight(int x, int MX)
{
    int temp = x;
    if(temp + 1 < MX)
    {
        x++;
    }
    return x;

}
int moveLeft(int x)
{
    int temp = x;
    if(temp - 1 >= 0)
    {
        x--;
    }

    return x;
}
int moveDown(int y, int MY)
{
    int temp = y;
    if(temp + 1 < MY)
    {
        y++;
    }
    return y;
}

int moveUp(int y)
{
    int temp = y;
    if(temp - 1 >= 0)
    {
        y--;
    }
    return y;

}





