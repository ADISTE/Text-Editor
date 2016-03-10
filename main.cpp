#include <curses.h>
#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
//Cursor moving function prototypes
using namespace std;


int moveRight(int x);
int moveLeft(int x);
int moveDown(int y);
int moveUp(int y);
void reBuild();

int xCounter = 0;
int yCounter = 0;
int x=0;
int y=0;
vector<string> strVec;
WINDOW* macWin;
ofstream ofs;

int main()
{
    initscr();//initializes screen

    WINDOW *getwin(FILE *MacroFile);
    std::vector<char> charVec;
    string fName;
    char cLine;
    macWin = newwin(180, 40, y, x);
    //vector<string> strVec;
    std::cout<< "Enter a file name: ";
    cin>>fName;
    //string  fName = "MacroFile";
    string line;//line by line
    string pLine; //print line
    char quit;//determines whether to quit the program or not
    ifstream iData;
    ofstream oName;
    int cursPos; //cursor movement
    int scrollW;//scrolling





    iData.open(fName.c_str());


    if (iData.good())
    {
        while(iData.good()) //writes file to screen
        {
            getline(iData, line);
            strVec.push_back(line);
            //charVec.push_back(cLine);

        }//end while
    }
    else
    {
        strVec.push_back("");
    }
    for(int i = 0; i < strVec.size(); i++)
    {


        copy(strVec[i].c_str(), strVec[i].c_str() + strVec[i].length(), back_inserter(charVec));
        charVec.push_back(' ');

    }



    //Set the heigh and width of the window






    int scr_set(const char *fName);
    int scr_init(const char *fName); //reads in the contents of the filename




    keypad(macWin, TRUE);
    wrefresh(stdscr);

    for(int i = 0; i<charVec.size(); i++)
    {
        // pLine = charVec[i];
        char cLine = charVec[i];

        waddch(macWin, cLine);

        // waddstr(macWin, const_cast<char *>(pLine.c_str()));
        // charVec.pop_back();

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
            y = moveDown(y);



        }
        else if(cursPos == KEY_UP)
        {
            y = moveUp(y);



        }
        else if(cursPos == KEY_LEFT)
        {
            x = moveLeft(x);
            if (x == 0)
            {
                x = strVec[y-1].length();
            }
        }

        else if(cursPos == KEY_RIGHT)
        {
            x = moveRight(x);
              if (x > strVec[y].length())
            {
            y = moveDown(y);
            x = 0;
            }
        }

        else if(cursPos == KEY_BACKSPACE)
        {

            //take char at x,y cood and replace with ""
            strVec[y].erase(x,1);
            //wrefresh(macWin);
            reBuild();
            x = moveLeft(x);



            //x = moveLeft(x);
        }
        else if (cursPos == '!')
        {
            break;
        }
        else if (cursPos == '5')
        {
            for (int i = 0; i< strVec.size(); i++)
            {

                ofs.open("output.txt");
                if(ofs.is_open())
                {
                    ofs << strVec[i];
                    ofs << '\n';
                }

            }
            break;
        }
        else

            //int t = strVec.size();
        {
            //    if (strVec[y+1].length() < strVec.size())
            //      {
//       strVec.push_back(" ");
//        }
            if (strVec.size() < y+1)
            {
                strVec.push_back("");
            }
            if (x > 40)
            {
                strVec.push_back("");
                y = moveDown(y);
                x = 0;
            }

            strVec.at(y).insert(x, 1, cursPos);

            if (cursPos == '\n')
            {

                y = moveDown(y);
                x = 0;
                wclear(macWin);
                reBuild();
            }
            else
            {
                wclear(macWin);
                reBuild();
                x = moveRight(x);
            }


        }//end long else if statement



    }

    //printw("Hello World");

    //wgetch(macWin);//waits for character input



//end WHILE


    endwin();
    return 0;
}//end main


void reBuild()
{

    wclear(macWin);

    for(int i = 0; i<strVec.size(); i++)
    {

        for (int j = 0; j<strVec.at(i).length(); j++)
        {

            mvwaddch(macWin, i, j, strVec.at(i).at(j));
            wrefresh(macWin);



        }
    }
}//end reBuild

//Cursor moving functions
int moveRight(int x)
{
    int temp = x;
    if(temp + 1 < 180)
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
int moveDown(int y)
{
    int temp = y;
    if(temp + 1 < 180)
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





