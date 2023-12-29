#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include "DFA.h" 

//   1)    g++ -std=c++11 -o output_filename main.cpp DFA.cpp InputReader.cpp
//   2)    ./output_filename                                                         вводить в терминал для компиляции 


int main() {
    std::ifstream inputFile("input.txt");

    int alphabetSize;
    inputFile >> alphabetSize;

    std::unordered_set<std::string> alphabet;
    std::string symbolsInput;
    inputFile >> symbolsInput;
    for (size_t i = 0; i < symbolsInput.length(); ++i) {
        std::string symbolStr(1, symbolsInput[i]);
        alphabet.insert(symbolStr);
    }

    std::unordered_set<int> states;
    for (int i = 1; i <= alphabetSize; ++i) {
        states.insert(i);
    }

    int initialState = 1;
    int outputState = alphabetSize;

    std::unordered_map<int, std::unordered_map<std::string, int> > transitionTable;
    int state, nextState;
    for (std::unordered_set<int>::iterator it = states.begin(); it != states.end(); ++it) {
        inputFile >> state;
        for (std::unordered_set<std::string>::iterator it2 = alphabet.begin(); it2 != alphabet.end(); ++it2) {
            std::string symbol = *it2;
            inputFile >> nextState;
            transitionTable[state][symbol] = nextState;
        }
    }

    DFA<int, std::string> dfa(states, alphabet, initialState, outputState, transitionTable);

    std::vector<std::string> testInput;
    std::string testString;
    inputFile.ignore();
    std::getline(inputFile, testString);
    for (size_t i = 0; i < testString.length(); ++i) {
        std::string symbolStr(1, testString[i]);
        testInput.push_back(symbolStr);
    }

    bool result = dfa.checkString(testInput);

    std::cout << "Строка " << (result ? "принята" : "отклонена") << " автоматом." << std::endl;

    inputFile.close();
    return 0;
}
