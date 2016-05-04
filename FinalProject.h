#ifndef FINALPROJECT_H
#define FINALPROJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <ctime>
#include <cctype>

struct Question{
    std::string question;
    std::string answer;
    bool visited;
    Question * next;
    std::string mchoice[4];

    Question(std::string q, std::string a, std::string c[]){
        question = q;
        answer = a;
        next = NULL;
        for(int i = 0; i < 4; i++){
             mchoice[i]= c[i];
        }
        visited = false;
    }
};

class QAnswer{
    public:
        QAnswer(int);
        ~QAnswer();
        void buildTable(std::string a, std::string b, std::string n[]);
        void loadQuestion(int);
        void answerQuestion(std::string);
        bool missCount();
        void gameOver(bool);
        void menu(int);
        bool readFile(std::string);
        std::string trim(std::string &);
        int randomInt(int,int);
        int questionLimit;
        bool lastQuestion();
        std::vector<std::string> split(const char *str, char c);
        int difficulty;

    private:
        std::string currentAnswer;
        int score;
        int missCountx;
        Question *hTable[50];
        int tableSize;
        int questionCount;
        int generateHash(std::string question);

};
#endif
