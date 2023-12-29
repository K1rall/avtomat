#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

class InputReader {
public:
    static void readInputFromFile(const std::string& filename,
                                  int& alphabetSize,
                                  std::unordered_set<std::string>& alphabet,
                                  std::unordered_set<int>& states,
                                  int& initialState,
                                  int& outputState,
                                  std::unordered_map<int, std::unordered_map<std::string, int> >& transitionTable,
                                  std::vector<std::string>& testInput);
};

#endif // INPUT_READER_H
