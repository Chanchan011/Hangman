#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

using namespace std;

string chooseWord(const char* fileName);
string initialGuessWord(string secretWord);
void getGameData(string &secretWord, string &guessWord, const char* DATA_FILE);
void getPosibility(string guessWord);
void getHint(string &guessWord, string secretWord);
void renderGame(SDL_Renderer* renderer, vector <SDL_Texture*> background, vector <SDL_Texture*> letters,
                vector <SDL_Texture*> figures, string &guessWord, int badGuessCount, int &mess);
void renderAnimations(SDL_Renderer* renderer, vector <SDL_Texture*> background, vector <SDL_Texture*> animations, bool &win, int &mess);
bool getPlayerGuess(char &c, SDL_Event &e, bool &runGame, map <char, int> &havePressed, string &guessWord, string &secretWord, bool &useHint);
bool containLetter(string secretWord, char playerGuess);
string updateWord(string &guessWord, string secretWord, char &playerGuess);
string toLowerCase(const string& s);
void askForReplay(SDL_Event &e, bool &runGame, bool &win, map<char, int> &havePressed,
                  int &badGuessCount, bool &useHint, int &mess, string &secretWord, string &guessWord, const char* DATA_FILE);
void unload_SDL(vector <SDL_Texture*> background, vector <SDL_Texture*> letters, vector <SDL_Texture*> animations,
                vector <SDL_Texture*> figures, SDL_Window* window, SDL_Renderer* renderer);

#endif // INIT_H_INCLUDED
