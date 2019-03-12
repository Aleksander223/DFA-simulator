#include <iostream>
#include <fstream>
#include <string>
#include <set>

class DFA{
private:
    std::set<int> states;
    std::set<char> alphabet;
    int transitionTable[256][256];
    int startState;
    std::set<int> finalStates;

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
            int x;
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
            int x;
            f >> x;
            finalStates.insert(x);
        }

        // finally, we read the the transitions
        f >> numberOfTransitions;

        for(int i = 0; i < numberOfTransitions; i++){
            int x, z;
            char y;
            f >> x >> y >> z;

            transitionTable[x][(int)y] = z;
        }
    }

    bool tryWord(std::string word){
        // the current state is the starting state
        int currentState = startState;
        // we parse each letter through the automata
        for(int i = 0; i < word.length(); i++){
            currentState = transitionTable[currentState][word[i]];
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
