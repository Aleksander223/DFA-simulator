#include <iostream>
#include <fstream>
#include <string>
#include <set>

class DFA{
private:
    std::set<char> states;
    std::set<char> alphabet;
    int transitionTable[256][256];
    char startState;
    std::set<char> finalStates;

    int numberOfStates;
    int numberOfLetters;
    int numberOfFinalStates;
    int numberOfTransitions;
public:
    DFA(std::string filePath){
        // we initialize the transition table with -1 (transition not possible)
        for(int i = 0; i < 256; i++)
            for(int j = 0; j < 256; j++)
                transitionTable[i][j] = -1;


        std::ifstream f(filePath);

        // we begin by reading the number of states
        f >> numberOfStates;

        for(int i = 0; i < numberOfStates; i++){
            char x;
            f >> x;
            states.insert(x);
        }

        // we read the alphabet of the automata
        f >> numberOfLetters;

        for(int i = 0; i < numberOfLetters; i++){
            char x;
            f >> x;
            alphabet.insert(x);
        }

        // we read the starting state
        f >> startState;

        // we read the set of final states
        f >> numberOfFinalStates;

        for(int i = 0; i < numberOfFinalStates; i++){
            char x;
            f >> x;
            finalStates.insert(x);
        }

        // finally, we read the the transitions
        f >> numberOfTransitions;

        for(int i = 0; i < numberOfTransitions; i++){
            char x, z;
            char y;
            f >> x >> y >> z;

            transitionTable[(int)x][(int)y] = (int) z;
        }
    }

    bool tryWord(std::string word){
        const bool isFirstFinal = finalStates.find(startState) != finalStates.end();
        if(word=="$$LAMBDA$$" && isFirstFinal){
            return true;
        }
        else if(word=="$$LAMBDA$$")
            return false;
        /*
        for(int i = 0; i < 128; i++){
            for(int j = 0; j < 128; j++)
                std::cout<<transitionTable[i][j]<<" ";
            std::cout<<std::endl;
        }
*/
        // the current state is the starting state
        char currentState = startState;
        // we parse each letter through the automata
        for(int i = 0; i < word.length(); i++){
            currentState = (char) transitionTable[(int)currentState][(int)word[i]];
            if(currentState == -1){
                // if we make an impossible transition then we reject it
                return false;
            }
        }
        // we check if the state we are in is final
        const bool isFinal = finalStates.find(currentState) != finalStates.end();
        if(isFinal){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(){
    DFA test("automata.in");
    DFA test2("automata2.in");
    std::ifstream f("words.in");
    std::ofstream g("words.out");

    std::string word;
    // read all the words from the file
    // NOTE: if you put a space then it will count as 2 words
    while(f>>word){
        g<<word<<"\t\t";
        // test if a word is accepted or not
        if(test.tryWord(word) == true)
            g<<"ACCEPTED\n";
        else
            g<<"REJECTED\n";
    }
    return 0;
}
