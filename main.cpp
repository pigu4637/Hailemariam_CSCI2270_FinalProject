#include "FinalProject.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
/*
Welcome to QAnswer! usage of this program is minimal, all you have to do is to compile it.
It was tested on codeblocks IDE using GNU compiler, so it should work with the same environment with no prob.
This program requires c++11 compiler.
The data.txt file contains a question and 4 multiple choice answers, so if you want to add another question you
can do that by following the below format:
    <your question> ? <4 multple answers separated by comma>
*/
int main()
{
    //the constructor takes the max number of questions
    QAnswer q(10);
    bool open = q.readFile("data.txt");
    if(!open)
        return 0;
    bool playagain = false;
    string tmpchoice;
    while(playagain == false)
    {
        while((tmpchoice != "1") && (tmpchoice != "2") && (tmpchoice != "3"))
        {
            q.menu(1);
            getline(cin, tmpchoice);
        }
        istringstream buffer(tmpchoice);
        buffer >> q.difficulty;
        while(!q.missCount())
        {
            if(!q.lastQuestion())
            {
                int rand = q.randomInt(0,49);
                q.loadQuestion(rand);
                string answer;
                getline(cin, answer);
                q.answerQuestion(answer);
            }
            else
            {
                break;
            }
        }
        q.gameOver(q.lastQuestion());
        tmpchoice = "";
        while((tmpchoice != "1") && (tmpchoice != "2"))
        {
            q.menu(2);
            getline(cin, tmpchoice);
        }
        if(tmpchoice == "1")
            playagain = true;
        else
            playagain = false;
    }
    return 0;
}
/*
You did not upload the question file (data.txt) to GitHub! It was difficult evaluating your project without the basis of it.
Knowing that, I could not contribute much to your project.
I cleaned up some of your functions, as some were redundant or just unused (removed timeleft and getscore, combined the different game over options (win and lost) ect.
I added an option to play the game again (mostly untested due to the lack of the data file), which resets everything but the open file as it would be redundant.
I also added a difficulty setting where the player can choose between not being able to get a single answer wrong to being able to get two answers wrong.
For simplicity I used iostream and namespace std, and instead of causing the program to crash, the program will tell you if you are missing the question file.
I did not dare trying to fix the problem you are having of having the same questions show up multiple times, as I would probably break something and not be able to test
it due to the lack of the question file.
*/
