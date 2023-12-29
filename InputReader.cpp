#include "InputReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

void InputReader::readInputFromFile(const std::string& filename,
                                    int& alphabetSize,
                                    std::unordered_set<std::string>& alphabet,
                                    std::unordered_set<int>& states,
                                    int& initialState,
                                    int& outputState,
                                    std::unordered_map<int, std::unordered_map<std::string, int> >& transitionTable,
                                    std::vector<std::string>& testInput) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        // Обработка ошибки, если файл не удалось открыть
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    // Чтение размера алфавита и символов алфавита
    inputFile >> alphabetSize;
    std::string symbolsInput;
    inputFile >> symbolsInput;
    for (size_t i = 0; i < symbolsInput.length(); ++i) {
        std::string symbolStr(1, symbolsInput[i]);
        alphabet.insert(symbolStr);
    }

    // Создание множества состояний
    for (int i = 1; i <= alphabetSize; ++i) {
        states.insert(i);
    }

    // Чтение начального и конечного состояний
    inputFile >> initialState >> outputState;

    // Чтение таблицы переходов
    int state, nextState;
    for (int it : states) {
        for (const std::string& it2 : alphabet) {
            inputFile >> state >> nextState;
            transitionTable[state][it2] = nextState;
        }
    }

    // Чтение строки для тестирования
    std::string testString;
    inputFile.ignore(); // Очистка символа перевода строки
    std::getline(inputFile, testString);
    for (size_t i = 0; i < testString.length(); ++i) {
        std::string symbolStr(1, testString[i]);
        testInput.push_back(symbolStr);
    }

    inputFile.close();
}
