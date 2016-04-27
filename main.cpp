#include "FinalProject.h"
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
    q.readFile("data.txt");
    q.menu();

    std::string choice;
    std::getline(std::cin, choice);

    if(choice == "1"){
        bool quit = false;
        while(!q.missCount() &&!quit){
            if(!q.lastQuestion()){
                int rand = q.randomInt(0,49);
                q.loadQuestion(rand);
                std::string answer;
                std::getline(std::cin, answer);
                q.answerQuestion(answer);
            }
            else{
                quit = true;
                std::cout << "Congratulations! You have finished the game. We estimate your IQ to be: " << q.randomInt(100,250)<<"\n";
            }
        }
        if(q.missCount()){
            q.gameOver();
        }
    }
    else{
        std::cout << "Wrong choice\n";
    }
    return 0;
}
