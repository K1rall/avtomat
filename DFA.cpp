#include "DFA.h"
#include <stdexcept>

template <typename State, typename Symbol>
bool DFA<State, Symbol>::checkAlphabetConsistency(const std::unordered_set<Symbol>& alphabet) const {
    for (typename std::unordered_map<State, std::unordered_map<Symbol, State> >::const_iterator stateMap = transitions.begin(); stateMap != transitions.end(); ++stateMap) {
        const std::unordered_map<Symbol, State>& stateTransitions = stateMap->second;
        for (typename std::unordered_map<Symbol, State>::const_iterator symbolStatePair = stateTransitions.begin(); symbolStatePair != stateTransitions.end(); ++symbolStatePair) {
            const Symbol& symbol = symbolStatePair->first;
            if (alphabet.find(symbol) == alphabet.end()) {
                return false;
            }
        }
    }
    return true;
}

template <typename State, typename Symbol>
DFA<State, Symbol>::DFA(const std::unordered_set<State>& states,
                        const std::unordered_set<Symbol>& alphabet,
                        const State& initial,
                        const State& output,
                        const std::unordered_map<State, std::unordered_map<Symbol, State> >& transitionTable)
    : initialState(initial), outputState(output), transitions(transitionTable) {

    if (states.find(initial) == states.end() ||
        states.find(output) == states.end() ||
        !checkAlphabetConsistency(alphabet)) {
        throw std::invalid_argument("Неверные параметры DFA");
    }
}

template <typename State, typename Symbol>
bool DFA<State, Symbol>::checkString(const std::vector<Symbol>& input) {
    State currentState = initialState;

    for (size_t i = 0; i < input.size(); ++i) {
        const Symbol& symbol = input[i];

        if (transitions[currentState].find(symbol) == transitions[currentState].end()) {
            return false;
        }

        currentState = transitions[currentState][symbol];
    }

    return currentState == outputState;
}

template class DFA<int, std::string>; 
