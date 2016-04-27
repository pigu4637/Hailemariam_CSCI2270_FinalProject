#include "FinalProject.h"

QAnswer::QAnswer(int l){
    for(int i = 0; i < tableSize;i++){
        hTable[i] = NULL;
    }
    missCountx = 0;
    questionCount = 1;
    tableSize = 50;
    questionLimit = l;
    score = 0;
    currentAnswer = "";
}

QAnswer::~QAnswer(){

}
//read the questions from the array and call build table method
void QAnswer::readFile(std::string fileName){
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line))
    {
        const char * c = line.c_str();
        std::vector <std::string> h = split(c,'?');
        const char * d = h[1].c_str();
        std::vector <std::string> m = split(d,',');
        std::string* mp = &m[0];
        buildTable(h[0], m[0],mp);
    }
}

//build the hashtable--this functions takes the question, the answer and the multiple choice
void QAnswer::buildTable(std::string q, std::string a,std::string m[]){
        int index = generateHash(q);

        if(hTable[index] == NULL){
            hTable[index] = new Question(q, a, m);
        }
        else{
            Question * current = hTable[index];
            while(current->next != NULL){
                current = current->next;
            }
            Question * temp = new Question(q,a,m);
            current->next = temp;
        }
}
/*display the random question to the user until he/she misses 3 questions or answers at least 8/10
display the score and question count along*/
void QAnswer::loadQuestion(int index){
    bool loaded = false;
    if(hTable[index] != NULL){
        Question *q = hTable[index];

        while(q->next != NULL){
            if(q->visited == false){
                break;
            }
            else{
                q  = q->next;
            }
        }
        std::srand(std::time(0));
        random_shuffle(std::begin(q->mchoice), std::end(q->mchoice));
        std::cout << "Score: "<< getScore() << " Question: " <<questionCount <<"/" <<questionLimit<<"\n";
        std::cout << q->question << "?\n";
        std::cout << "A. " << trim(q->mchoice[0]) << "\n";
        std::cout << "B. " << trim(q->mchoice[1]) << "\n";
        std::cout << "C. " << trim(q->mchoice[2]) << "\n";
        std::cout << "D. " << trim(q->mchoice[3]) << "\n";
        loaded = true;
        q->visited = true;
        for(int i = 0; i < 4;i++){

           if(trim(q->mchoice[i]) == trim(q->answer)){
                if(i==0){
                    currentAnswer = "a";
                }
                else if(i==1){
                    currentAnswer = "b";
                }
                else if(i==2){
                    currentAnswer = "c";
                }
                else if(i==3){
                    currentAnswer = "d";
                }
           }
        }
    }

    if(!loaded){
        loadQuestion(randomInt(0,tableSize-1));
    }
}

//check if the user has reached the last question
bool QAnswer::lastQuestion(){
    if(questionCount > questionLimit){
        return true;
    }
    return false;
}

//not implemented for now.
int QAnswer::getTimeLeft(){

}

//trim string from left and right to get rid of whitespace for comparison
std::string QAnswer::trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

//answer question: accepts the answer as multiple choice--update the score and question count
void QAnswer::answerQuestion(std::string choice){
    if(currentAnswer == ""){
        std::cout << "Questions not initialized.\n";
    }
    else{
        if(currentAnswer == choice){
            score += 100;
        }
        else{
            missCountx += 1;
        }
        questionCount += 1;
    }
}

//return current score
int QAnswer::getScore(){
    return score;
}

//check if the user has answered 3 questions already
bool QAnswer::missCount(){
    if(missCountx >= 3){
        return true;
    }
    return false;
}

//display menu
void QAnswer::menu(){
    std::cout << "=================================QAnswer========================================\n";
    std::cout << "Welcome to QAnswer! Answer 8/10 random questions to finish the game. Press 1 to continue.\n";
    std::cout << "================================================================================\n\n";
}

//display game over message
void QAnswer::gameOver(){
    std::cout << "Dayuum! Did you already answer 3 questions wrong? At least, you tried. See you next time.\n";
}

//generate random int between two numbers
int QAnswer::randomInt(int min, int max){
     std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

//helper function to ease spliting the data read from the file..very helpful
std::vector<std::string> QAnswer::split(const char *str, char c = ' '){
    std::vector<std::string> result;
    do{
        const char *begin = str;
        while(*str != c && *str)
            str++;
        result.push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}

//generate a hash based on the question
int QAnswer::generateHash(std::string question){
    int sum = 0;
    for(int i = 0; i < question.size();i++){
        if(i%2 == 0){
            sum += question[i];
        }
    }
    return sum%tableSize;
}
