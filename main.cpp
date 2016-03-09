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
int moveRight(int x);
int moveLeft(int x);
int moveDown(int y);
int moveUp(int y);

int xCounter = 0;
int yCounter = 0;


int main()
{
    initscr();//initializes screen

    WINDOW* macWin = NULL;

    WINDOW *getwin(FILE *MacroFile);
    int xWin = 260;
    int yWin = 180;







    using namespace std;
    std::vector<char> charVec;
    string fName;
    char cLine;

    vector<string> strVec;
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
    int x=0;
    int y=0;




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
    macWin = newwin(180, 180, y, x);





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
        }
        else if(cursPos == KEY_RIGHT)
        {
            x = moveRight(x);
        }
        else if(cursPos == KEY_BACKSPACE)
        {


            for(int i = 0; i<strVec.size(); i++)
            {

                for (int j = 0; j<strVec.at(i).length(); j++)
                {

                    strVec[i] = " ";
                    wrefresh(macWin);
                    x = moveLeft(x);
                    //x = moveRight(x);
                }
            }
            //x = moveLeft(x);
        }
        else if (cursPos == '!')
        {
            break;
        }
        else if (cursPos == '5')
        {
            for (int i = 0; i<= strVec.size(); i++)
            {

                ofstream ofs("output.txt", ofstream::app);
                ofs << strVec[i];
            }
            break;
        }
        else if (cursPos == '\n')
        {
            waddch(macWin,'\n');
            charVec.push_back(cursPos);
            y = moveDown(y);
            x = 0;
        }
        else
        {



            strVec.at(y).insert(x, 1, cursPos);
            wclear(macWin);
            for(int i = 0; i<strVec.size(); i++)
            {

                for (int j = 0; j<strVec.at(i).length(); j++)
                {

                    mvwaddch(macWin, i, j, strVec.at(i).at(j));
                    wrefresh(macWin);
                    //x = moveRight(x);
                }

                // pLine = charVec[i];



                // waddstr(macWin, const_cast<char *>(pLine.c_str()));
                // charVec.pop_back();


            }



        }

        //printw("Hello World");

        //wgetch(macWin);//waits for character input


    }


    endwin();
    return 0;
}//end main


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





