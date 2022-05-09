#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "init.h"
#include "util.h"
#include "game.h"
using namespace std;

string secretWord = "";
string guessWord = "";

const char DATA_FILE[] = "data/words.txt";
const int MAX_BAD_GUESS = 7;
int badGuessCount = 0;
SDL_Event e;
bool runGame = true;
bool win = 0;
bool useHint = 0;
char playerGuess = '1';
int mess = 4;
map <char, int> havePressed;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string TITLE = "Hangman in SDL";

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    initSDL(window, renderer, TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    vector <SDL_Texture*> background = loadBackground(renderer);
    vector <SDL_Texture*> letters = loadLetters(renderer);
    vector <SDL_Texture*> animations = loadAnimations(renderer);
    vector <SDL_Texture*> figures = loadFigures(renderer);

    mainMenu(window, renderer, background, letters, animations, figures);
    getGameData(secretWord, guessWord, DATA_FILE);
    while(runGame) {
        SDL_Delay(50);
        renderGame(renderer, background, letters, figures, guessWord, badGuessCount, mess);
        if(getPlayerGuess(playerGuess, e, runGame, havePressed, guessWord, secretWord, useHint)) {
            if (havePressed[playerGuess]) {
                mess = 7;
                continue;
            }
            havePressed[playerGuess] = 1;
            if (containLetter(secretWord, playerGuess)) {
                guessWord = updateWord(guessWord, secretWord, playerGuess);
                mess = 5;
            }
            else {
                badGuessCount++;
                mess = 6;
            }
            getPosibility(guessWord);
        }
        if(badGuessCount == MAX_BAD_GUESS || guessWord == secretWord) {
            if (guessWord == secretWord) {
                renderGame(renderer, background, letters, figures, guessWord, badGuessCount, mess);
                win = 1;
                mess = 8;
            }
            else if (badGuessCount == MAX_BAD_GUESS) {
                renderGame(renderer, background, letters, figures, secretWord, badGuessCount - 1, mess);
                win = 0;
                mess = 9;
            }
            renderAnimations(renderer, background, animations, win, mess);
            askForReplay(e, runGame, win, havePressed, badGuessCount, useHint, mess, secretWord, guessWord, DATA_FILE);
        }
    }
    unload_SDL(background, letters, animations, figures, window, renderer);
    return 0;
}

