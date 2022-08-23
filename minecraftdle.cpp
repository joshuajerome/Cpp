#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

string archive[100];// = {"clear","reaps","crawl"};
string backgrounds[] = {"\x1b[37;41m","\x1b[37;42m","\x1b[37;43m","\x1b[37;44m","\x1b[37;45m","\x1b[37;46m","\x1b[37;47m"};
string guessBoard[6][5];
string colorBoard[6][5];
string guess = "", word = "";
int turn = 0;

void randomBackground(string s);
string getRandom(string old);
void intro();
void showInstructions();
void pickWord();
int wordIsValid(string w);
void ask();
void printBoard();
void setColorBoard();
bool aContainsC(string a, char c);
void printArchive();
void emptyBoard();
void fileInput();
void game();

int main() {
  game();
  return 0;
}

void randomBackground(string s) {
  string last = "\x1b[37;40m";
  for (int i = 0; i < s.length(); i++) {
    if (!isspace(s[i])) {
      string random = getRandom(last);
      cout << random << " " << s[i] << " " << "\x1b[0m";
      last = random;

    } else {
      cout << "\x1b[37;40m" << " " << s[i] << " ";
    }
  }
  cout << endl;
}

string getRandom(string old) {
  int random;
  do {
    random = rand() % 6;
  } while (backgrounds[random] == old);
  return backgrounds[random];
}

void intro() {
  srand(time(NULL));
  // cout << "enter a phrase: ";
  // string input;
  // getline(cin, input);
  cout  << "_____________________________________________________________________\n\n" << endl;
  randomBackground("WELCOME TO MINECRAFTDLE");
  showInstructions();
}

void showInstructions() {
  cout  << "\n\n"
        << "Minecraftdle tests YOUR knowledge of minecraft! A random 5-letter"
        << " word is chosen at random and it is YOUR job to guess the word :D"
        << "\n\x1b[37;44m diamond \x1b[0m        : correct letter & correct position"
        << "\n\x1b[37;43m gold \x1b[0m           : correct letter & incorrect position"
        << "\n\x1b[37;41m redstone block \x1b[0m : incorrect letter"
        << "if you want to give up mid-game, press \"0\" to give up!"
        << endl;
}

void pickWord() {
  int random = rand() % (sizeof(archive) / sizeof(archive[0]));
  word = archive[random];
}

void ask() {
  cout << "\nmake a guess: ";
  getline(cin, guess);
  while (wordIsValid(guess) == 0) {
    cout << "\"" << guess << "\"" << " is not in minecraftdle archive." << endl;
    cout << "\nmake a guess: ";
    getline(cin, guess);
  }
  if (wordIsValid(guess) == 2) {
    cout << "\nthe word was: " << word << "!\n" << endl;
    emptyBoard();
    return;
  }
  for (int i = 0; i < 5; i++) {
    guessBoard[turn][i] = guess[i];
    if (guess[i] == word[i]) {
      colorBoard[turn][i] = "\x1b[37;44m";
    } else if (aContainsC(word,guess[i])) {
        colorBoard[turn][i] = "\x1b[37;43m";
    } else {
      colorBoard[turn][i] = "\x1b[37;41m";
    }
  }
  turn++;
}

void emptyBoard() {
  turn = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      guessBoard[i][j] = "";
      colorBoard[i][j] = "\x1b[0m";
    }
  }
}

bool aContainsC(string a, char c) {
  for (int i = 0; i < a.length(); i++) {
    if (a[i] - c == 0) {
      return 1;
    }
  }
  return 0;
}

void setColorBoard() {
  for (int i = 0 ; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      colorBoard[i][j] = "\x1b[0m";
    }
  }
}
void printBoard() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      if (j < 4) {
        cout << colorBoard[i][j] << " " << guessBoard[i][j] << " " << "\x1b[0m" << "|";
      } else {
        cout << colorBoard[i][j] << " " << guessBoard[i][j] << " " << "\x1b[0m";
      }
    }
    cout << endl;
  }
}

int wordIsValid(string w) {
  if (w == "0") return 2;
  for (int i = 0; i < sizeof(archive)/sizeof(archive[0]); i++) {
    if (w == archive[i]) return 1;
  }
  return 0;
}

void printArchive() {
  for (int i = 0; i < (sizeof(archive) / sizeof(archive[0])); i++) {
    cout << archive[i] << endl;
  }
}

void game() {
  intro();
  fileInput();
  string option = "";
  while (option != "e") {
    cout  << "\n" << endl
          << "press [p] to play\n"
          << "press [a] to go to archive\n"
          << "press [i] for instructions\n"
          << "press [c] for credits\n"
          << "press [e] for exit\n"
          << endl;
    while (option == "") {
      cout << ": ";
      getline(cin, option);
      if ((option != "p") && (option != "a") && (option != "i") && (option != "c") && (option != "e")) {
        option = "";
        continue;
      } else {
        if (option == "p") {
          pickWord();
          setColorBoard();
          while (guess != word) {
            ask();
            if (wordIsValid(guess) == 2) {
              option = "";
              emptyBoard();
              break;
            }
            printBoard();
          }
          emptyBoard();
        } else if (option == "a") {
          cout << "\narchive:\n" << endl;
          printArchive();
          cout << "\n";
        } else if (option == "i") {
          showInstructions();
        } else if (option == "c") {
          cout << "created by Reiko Shiraishi and Joshua Jerome\n" << endl;
        } else if (option == "e") {
          return;
        }
        option = "";
        break;
      }
    }
  }

}

void fileInput() {
  ifstream in_stream;
  in_stream.open("minecraft_terms.txt");
  if(in_stream.fail()){
    cout<<"Input file failed to open"<<endl;
    exit(1);
  }
  string s;
  for(int i=0; i<100; i++){
    in_stream>>s;
    archive[i] = s;
  }
  in_stream.close();
}

void comments() {

    // "\x1b[30m" sets only foreground color

    // "\x1b[40m" sets only background color

    // "\x1b[30;40m" to set foreground and background

    // "\x1b[0m" resets all color attributes back to normal

    /*
        +---------+------------+------------+
        |  color  | foreground | background |
        |         |    code    |    code    |
        +---------+------------+------------+
        | black   |     30     |     40     |
        | red     |     31     |     41     |
        | green   |     32     |     42     |
        | yellow  |     33     |     43     |
        | blue    |     34     |     44     |
        | magenta |     35     |     45     |
        | cyan    |     36     |     46     |
        | white   |     37     |     47     |
        +---------+------------+------------+
    */
}



