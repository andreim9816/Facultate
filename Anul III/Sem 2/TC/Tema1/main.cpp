#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include<bits/stdc++.h>

using namespace std;

const int SPACE_STATE = 3;
const int ERROR_LITERAL = 80;
const int ERROR_OPERATOR = 81;
const int COMMENT_MULTI_LINE = 103;
const int COMMENT_ONE_LINE = 104;

class Token {
private:
    int tipToken;
    int valoareToken;
    int linErr, colErr;

    static map<int, string> tokenFinalStates;

public:
    Token() {
        tipToken = valoareToken = -1;
    }

    Token(int tipToken, int valoareToken) {
        this->tipToken = tipToken;
        this->valoareToken = valoareToken;
    }

    void setLinErr(int lin) {
        linErr = lin;
    }

    void setColErr(int col) {
        colErr = col;
    }

    static Token createToken(int tip, string token, vector<string> &tokensArray) {
        /* creates a token, checks if the string already exists */
        if (tokensArray.empty()) {
            tokensArray.push_back(token);
            return Token(tip, 0);
        } else {
            int dim = tokensArray.size();
            for (int i = 0; i < dim; i++)
                if (tokensArray.at(i) == token)
                    return Token(tip, i);

            tokensArray.push_back(token);
            return Token(tip, dim);
        }
    }

    string getTokenType() {
        return tokenFinalStates.at(tipToken);
    }

    int getTokenValue() {
        return valoareToken;
    }

    int getLinErr() {
        return linErr;
    }

    int getColErr() {
        return colErr;
    }
};

int KEYWORD = 100;

map<int, string> Token::tokenFinalStates = {
        make_pair(0, "eroare lexicala"),
        make_pair(1, "literal gresit formatat"),
        make_pair(2, "literal string"),
        make_pair(4, "operator +"),
        make_pair(5, "operator ++"),
        make_pair(6, "operator +="),
        make_pair(7, "operator -"),
        make_pair(8, "operator --"),
        make_pair(9, "operator -="),
        make_pair(10, "operator *"),
        make_pair(11, "operator *="),
        make_pair(12, "operator /"),
        make_pair(13, "operator /="),
        make_pair(14, "operator <"),
        make_pair(15, "operator <<"),
        make_pair(16, "operator <="),
        make_pair(17, "operator >"),
        make_pair(18, "operator >>"),
        make_pair(19, "operator >="),
        make_pair(20, "operator ="),
        make_pair(21, "operator =="),
        make_pair(22, "operator *"),
        make_pair(23, "operator *="),
        make_pair(24, "operator <<="),
        make_pair(25, "operator >>="),
        make_pair(26, "operator &"),
        make_pair(27, "operator &&"),
        make_pair(28, "operator &="),
        make_pair(29, "operator |"),
        make_pair(30, "operator ||"),
        make_pair(31, "operator |="),
        make_pair(32, "operator ^"),
        make_pair(33, "operator ^="),
        make_pair(34, "operator %"),
        make_pair(35, "operator %="),
        make_pair(36, "operator !"),
        make_pair(37, "operator !="),
        make_pair(38, "identificator"),
        make_pair(39, "constanta intreaga"),
        make_pair(43, "constanta flotanta"),
        make_pair(47, "constanta hexa"),
        make_pair(50, "literal caracter"),
        make_pair(51, "separator {"),
        make_pair(52, "separator }"),
        make_pair(53, "operator ."),
        make_pair(55, "operator ->"),
        make_pair(56, "operator ["),
        make_pair(57, "operator ]"),
        make_pair(58, "operator ("),
        make_pair(59, "operator )"),
        make_pair(60, "operator :"),
        make_pair(61, "operator ;"),
//        make_pair(62, "comentariu /*"),
//        make_pair(63, "comentariu */"),
//        make_pair(64, "comentariu //"),
        make_pair(65, "eroare la literalul string"),
        make_pair(66, "separator ,"),
        make_pair(COMMENT_MULTI_LINE, "comentariu /* */"),
        make_pair(COMMENT_ONE_LINE, "comentariu //"),
        make_pair(ERROR_LITERAL, "eroare literal!"),
        make_pair(ERROR_OPERATOR, "eroare operator!"),
        make_pair(KEYWORD, "keyword")
};

class Analyzer {
    /* array for keyWords */
    static vector<string> keyWords;

    static vector<char> characters;

    /* pointer to input/ output files */
    ifstream fin;
    ofstream fout;

    /* pointer to the file that holds the DFA data */
    ifstream finStates;

    /* hashmap for transitions*/
    map<pair<int, char>, int> transitions;

    /* array of tokens in the file */
    vector<string> tokensArray;

    /* number of states */
    int noOfStates;

    /* array for states */
    vector<int> states;

    /* number of final states */
    int noOfFinalStates;

    /* array for finalStates*/
    vector<int> finalStates;

    /* current line */
    int currLine = 1;

    /* current column */
    int currCol = 0;

    /* current character */
    char currCh;

public:
    Analyzer(const string &inputAutomat, const string &inputFile, const string &outputFile) {
        fin.open(inputFile);
        fout.open(outputFile);
        finStates.open(inputAutomat);
        noOfFinalStates = noOfStates = 0;
        currCh = readCharacter();
    }

    ~Analyzer() {
        fin.close();
        fout.close();
        finStates.close();
    }

    void generateDFA() {
        finStates >> noOfStates;
        int i;

        for (i = 0; i < noOfStates; i++) {
            states.push_back(i);
        }

        finStates >> noOfFinalStates;
        for (i = 0; i < noOfFinalStates; i++) {
            int state;
            finStates >> state;
            finalStates.push_back(state);
        }

        int state1, state2;
        char ch;

        while (finStates >> state1 >> ch >> state2) {
            transitions.insert(makeTransitionPair(state1, state2, ch));
        }
    }

    Token getToken() {
        /* generates the current Token*/
        char currChar = getCurrCharacter();
        int currState = 0; // starting state
        int lastState = currState;

        /* current token */
        string token = "";

        /* check if transaction */
        while ((currState = transitionExists(currState, currChar)) != -1) {
            /* newline character should never be added */
            lastState = currState;
            if (currChar != '\n' && currChar != -1)
                token += currChar;

            if (currChar == '\n') {
                currLine++;
                currCol = 0;
            }
            currChar = readCharacter();
            currCol++;
        }

        /* encountered only space and \n */
        if (lastState == SPACE_STATE || lastState == COMMENT_ONE_LINE || lastState == COMMENT_MULTI_LINE)
            return getToken();
        else if (isFinalState(lastState)) {
            if (isKeyword(token))
                return Token::createToken(KEYWORD, token, tokensArray);
            else return Token::createToken(lastState, token, tokensArray);
        } else {
            Token myToken(lastState, -1);
            myToken.setColErr(currCol);
            myToken.setLinErr(currLine);
            return myToken;
        }
    }

    bool isFinalState(int state) {
        return binary_search(finalStates.begin(), finalStates.end(), state);
    }

    bool isKeyword(string token) {
        return binary_search(keyWords.begin(), keyWords.end(), token);
    }

    void addAllTransitionsForLetters(int state1, int state2) {
        /* function that adds letter (a-z A-Z) transitions between 2 given states */

        for (char ch = 'a'; ch <= 'z'; ch++)
            transitions.insert(makeTransitionPair(state1, state2, ch));

        for (char ch = 'A'; ch <= 'Z'; ch++)
            transitions.insert(makeTransitionPair(state1, state2, ch));
    }

    void addAllTransitionsForDigits(int state1, int state2) {
        /* function that adds digit transitions between 2 given states */
        for (char ch = '0'; ch <= '9'; ch++)
            transitions.insert(makeTransitionPair(state1, state2, ch));
    }

    void addAllTransitionsForCharacters(int state1, int state2) {
        /* function that adds all the characters between 2 given states*/
        for (char ch : Analyzer::characters)
            transitions.insert(makeTransitionPair(state1, state2, ch));
    }

    void addAllTransitionsForCharactersWithoutSymbols(int state1, int state2, char sym1, char sym2) {
        /* function that adds characters transitions between 2 given states except 2 symbols */
        for (char i : characters)
            if (i != sym1 && i != sym2)
                addTransition(state1, state2, i);
    }

    void addTransition(int state1, int state2, char ch) {
        /* function that adds a transisiton */
        transitions.insert(makeTransitionPair(state1, state2, ch));
    }

    void addCustomTransitions() {
        /* function that adds custom transitions */
        addTransition(1, 1, ' ');
        addAllTransitionsForDigits(1, 1);
        addAllTransitionsForLetters(1, 1);
        addAllTransitionsForCharacters(1, 1);

        /* transition for space and \n handling */
        addTransition(0, 3, ' ');
        addTransition(0, 3, '\n');
        addTransition(3, 3, ' ');
        addTransition(3, 3, '\n');

        /* transition for identifiers */
        addAllTransitionsForLetters(0, 38);
        addTransition(0, 38, '_');

        addAllTransitionsForLetters(38, 38);
        addAllTransitionsForDigits(38, 38);
        addTransition(38, 38, '_');
        // error for abc"
        addTransition(38, ERROR_LITERAL, '"');


        /* transition for numbers */
        /* integer values */
        addAllTransitionsForDigits(0, 39);
        addAllTransitionsForDigits(39, 39);

        // -7.2 case
        addAllTransitionsForDigits(7, 39);

        /* float and exp values */
        addTransition(39, 40, '.');
        addAllTransitionsForDigits(40, 43);

        addTransition(39, 42, 'e');
        addAllTransitionsForDigits(42, 43);
        addAllTransitionsForDigits(43, 43);
        addTransition(42, 44, '+');
        addTransition(42, 44, '-');
        addAllTransitionsForDigits(44, 43);

        /* hexa values */
        addTransition(0, 45, '0');
        addTransition(45, 46, 'x');
        addTransition(45, 46, 'X');
        addAllTransitionsForDigits(46, 47);
        for (char i = 'a'; i <= 'f'; i++)
            addTransition(46, 47, i);
        for (char i = 'A'; i <= 'F'; i++)
            addTransition(46, 47, i);
        addAllTransitionsForDigits(47, 47);
        for (char i = 'a'; i <= 'f'; i++)
            addTransition(47, 47, i);
        for (char i = 'A'; i <= 'F'; i++)
            addTransition(47, 47, i);

        /* character */
        addTransition(0, 48, '\'');
        addTransition(49, 50, '\'');
        addAllTransitionsForDigits(48, 49);
        addAllTransitionsForLetters(48, 49);
        addAllTransitionsForCharacters(48, 49);

        addAllTransitionsForDigits(49, ERROR_LITERAL);
        addAllTransitionsForLetters(49, ERROR_LITERAL);
        addAllTransitionsForCharacters(49, ERROR_LITERAL);

        /* errors */
        addTransition(1, 65, '\n');
        addAllTransitionsForDigits(2, ERROR_LITERAL);
        addAllTransitionsForLetters(2, ERROR_LITERAL);
        addAllTransitionsForCharacters(2, ERROR_LITERAL);

        // + errors
        addAllTransitionsForCharactersWithoutSymbols(4, ERROR_OPERATOR, '+', '=');

        addAllTransitionsForDigits(5, ERROR_OPERATOR);
        addAllTransitionsForCharacters(5, ERROR_OPERATOR);

        addAllTransitionsForDigits(6, ERROR_OPERATOR);
        addAllTransitionsForCharacters(6, ERROR_OPERATOR);

        // - errors
        addAllTransitionsForCharactersWithoutSymbols(4, ERROR_OPERATOR, '-', '=');

        addAllTransitionsForDigits(8, ERROR_OPERATOR);
        addAllTransitionsForCharacters(8, ERROR_OPERATOR);

        addAllTransitionsForDigits(9, ERROR_OPERATOR);
        addAllTransitionsForCharacters(9, ERROR_OPERATOR);

        addAllTransitionsForCharactersWithoutSymbols(10, ERROR_OPERATOR, '*', 'a');

        addAllTransitionsForDigits(11, ERROR_OPERATOR);
        addAllTransitionsForCharacters(11, ERROR_OPERATOR);

        addAllTransitionsForDigits(13, ERROR_OPERATOR);
        addAllTransitionsForCharacters(13, ERROR_OPERATOR);

        // comentariu /* */
        for (char i : characters)
            if (i != '*')
                addTransition(62, 62, i);

        addAllTransitionsForLetters(62, 62);
        addAllTransitionsForDigits(62, 62);

        addTransition(62, 62, ' ');
        addTransition(62, 62, '\n');

        addTransition(62, 102, '*');
        addTransition(102, 102, '*');

        for (char i : characters)
            if (i != '/' && i != '*')
                addTransition(102, 62, i);

        addAllTransitionsForLetters(102, 62);
        addAllTransitionsForDigits(102, 62);
        addTransition(102, 62, ' ');
        addTransition(102, 62, '\n');

        addTransition(102, 103, '/');

        // comentariu one line
        addAllTransitionsForLetters(64, 64);
        addAllTransitionsForDigits(64, 64);
        addAllTransitionsForCharacters(64, 64);
        addTransition(64, 64, ' ');

        addTransition(64, 104, '\n');


        addAllTransitionsForDigits(64, ERROR_OPERATOR);
        addAllTransitionsForCharacters(64, ERROR_OPERATOR);

        addAllTransitionsForCharacters(21, ERROR_OPERATOR);

        addAllTransitionsForDigits(23, ERROR_OPERATOR);
        addAllTransitionsForCharacters(23, ERROR_OPERATOR);

        addAllTransitionsForDigits(24, ERROR_OPERATOR);
        addAllTransitionsForCharacters(24, ERROR_OPERATOR);
    }

    static pair<pair<int, char>, int> makeTransitionPair(int state1, int state2, char ch) {
        /* function that creates an element for the hash map*/
        return make_pair(make_pair(state1, ch), state2);
    }

    static pair<int, char> makePairStateCharacter(int state, char ch) {
        return make_pair(state, ch);
    }

    int transitionExists(int state, char ch) {
        pair<int, char> transition = makePairStateCharacter(state, ch);
        if (transitions.count(transition) > 0) {
            return transitions.at(transition);
        }
        return -1;
    }

    char readCharacter() {
        /* function that reads the current character */
        currCh = fin.get();
        return getCurrCharacter();
    }

    char getCurrCharacter() {
        /* function that returns the current character */
        return currCh;
    }

    void write(Token token, vector<string> tokensArray) {
        if (token.getTokenValue() == -1) {
            string errorMsg = token.getTokenType();
            int linErr = token.getLinErr();
            int colErr = token.getColErr();

            fout << errorMsg << " la linia=" << linErr << " coloana=" << colErr << '\n';
        } else {
            string tokenString = tokensArray.at(token.getTokenValue());
            fout << "Tokenul " << tokenString << " este de tip " << token.getTokenType() << '\n';
        }
    }

    vector<string> getTokensArray() {
        return tokensArray;
    }
};

vector<string> Analyzer::keyWords = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "inline", "int", "long",
        "register", "restrict", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"
};

vector<char> Analyzer::characters = {'!', '@', '#', '$', '%', '^', '&', '*', '`', '~',
                                     '(', ')', '_', '+', '-', '=', '{', '}', '[', ']',
                                     ';', '\'', ',', '.', '/', ':', '"', '<', '>', '?',
                                     '|', '\\'};

int main() {
    Analyzer analyzer("automat.txt", "input.txt", "output.txt");
    analyzer.generateDFA();
    analyzer.addCustomTransitions();

    while (analyzer.getCurrCharacter() != -1) {
        Token token = analyzer.getToken();
        analyzer.write(token, analyzer.getTokensArray());
        if (token.getTokenValue() == -1)
            break;
    }
}
