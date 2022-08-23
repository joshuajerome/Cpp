#include <iostream>
using namespace std;

class Word{
private:
  string words[102];
  string current;
  string archive[102];
  string backgrounds[7];
  string guessBoard[6][5];
  string colorBoard[6][5];
  string guess;
  int turn;
public:
  Word();
  //visual displays
  //void introPage();
  void randomBackground(string s);
  string getRandom(string old);
  void displayCredits();
  void displayInstructions();
  //functions for game
  void setDailyWord();
  void checkWord(string guess);
  void ask();
  void emptyBoard();
  bool aContainsC(string a, char c);
  void setColorBoard();
  void printBoard();
  int wordIsValid(string w);
  void printArchive();
  void game();
};

#endif //MINECRAFTDLE_H
