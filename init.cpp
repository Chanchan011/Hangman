#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "util.h"
#include "init.h"
using namespace std;

vector <string> wordList;

string chooseWord(const char* fileName) {
    ifstream file(fileName);
    if(file.is_open()) {
        string word;
        while(file >> word) {
            wordList.push_back(word);
        }
        file.close();
    }
    if (wordList.size() > 0) {
        srand(time(0));
        int randomIndex = rand() % wordList.size();
        return toLowerCase(wordList[randomIndex]);
    }
    else return "";
}

string initialGuessWord(string secretWord) {
    string blankWord = "";
    int lengthOfWord = secretWord.length();
    for(int i = 0; i < lengthOfWord; i++)
        blankWord += '_';
    return blankWord;
}

void getGameData(string &secretWord, string &guessWord, const char* DATA_FILE) {
    srand(time(0));
    secretWord = chooseWord(DATA_FILE);
    if (secretWord.length() < 1) {
        cout << "Error reading vocabulary file " << DATA_FILE;
        return ;
    }
    guessWord = initialGuessWord(secretWord);
}

bool sortWay(pair<int, int> c1, pair<int, int> c2) {
    return c1.second > c2.second;
}

void getPosibility(string guessWord) {
    pair<int, int> c[26];
    for(int i=0; i<26; i++)
        c[i] = {i, 0};
    for(int vt=0; vt<int(guessWord.length()); vt++) {
        if(guessWord[vt] == '_') {
            for(int j=0; j<int(wordList.size()); j++) {
                if(wordList[j].length() != guessWord.length()) {
                    continue;
                }
                string s = wordList[j];
                bool able = 0;
                for(int pos=0; pos<int(s.length()); pos++) {
                    if(s[pos] != guessWord[pos] && guessWord[pos] != '_') {
                        break;
                    }
                    else if(pos == int(s.length()-1))
                        able = 1;
                }
                if(able) c[s[vt] - 'a'].second++;
            }
        }
    }
    sort(c, c+26, sortWay);
    for(int i=0; i<26; i++) {
        cout << char(c[i].first + 'a') << " " << c[i].second << '\n';
    }
    cout << "End of hint" << '\n';
}

void getHint(string &guessWord, string secretWord, map <char, int> &havePressed) {
    if(guessWord == secretWord)
        return ;
    vector <int> blank;
    for(int i=0; i<int(guessWord.length()); i++) {
        if(guessWord[i] == '_') blank.push_back(i);
    }
    int id = rand() % blank.size();
    char c = secretWord[blank[id]];
    for(int i=0; i < int(blank.size()); i++) {
        if(secretWord[blank[i]] == c)
            guessWord[blank[i]] = c;
    }
    havePressed[secretWord[blank[id]]] = 1;
    getPosibility(guessWord);
}

void renderGame(SDL_Renderer* renderer, vector <SDL_Texture*> background, vector <SDL_Texture*> letters,
                vector <SDL_Texture*> figures, string &guessWord, int badGuessCount, int &mess) {
    SDL_RenderClear(renderer);
    renderTexture(background[2], renderer, 0, 0, 800, 600);
    renderTexture(background[mess], renderer, 150, 28, 500, 122);
    renderTexture(background[3], renderer, 50, 361, 150, 39);
    int wordLength = guessWord.length();
    for(int i = 400 - 30*wordLength; i < 400 + 30*wordLength; i += 60) {
        int orderOfLetter = guessWord[(i - (400 - 30*wordLength)) / 60] - 97;
        if(orderOfLetter < 0)
            renderTexture(letters[0], renderer, i, 475, 60, 65);
        else renderTexture(letters[orderOfLetter + 1], renderer, i, 475, 60, 65);
    }
    renderTexture(figures[badGuessCount], renderer, 275, 200, 250, 250);
    SDL_RenderPresent(renderer);
}

void renderAnimations(SDL_Renderer* renderer, vector <SDL_Texture*> background,  vector <SDL_Texture*> animations,
                      bool &win, int &mess) {
    renderTexture(background[mess], renderer, 150, 28, 500, 122);
    SDL_RenderPresent(renderer);
    int first, last;
    if (!win) {
        first = 0, last = 9;
    } else {
        first = 9, last = 18;
    }
    for(int times=0; times<5; times++) {
        for(int i=first; i<last; i++) {
            renderTexture(animations[i], renderer, 275, 200, 250, 250);
            SDL_RenderPresent(renderer);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    renderTexture(background[10], renderer, 150, 28, 500, 122);
    SDL_RenderPresent(renderer);
}

bool getPlayerGuess(char &c, SDL_Event &e, bool &runGame, map <char, int> &havePressed,
                       string &guessWord, string &secretWord, bool &useHint) {
    if ( SDL_WaitEvent(&e) == 0){
        return 0;
    }
    if (e.type == SDL_QUIT) {
        runGame = false;
        return 0;
    }
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
            runGame = false;
            return 0;
        }
        if (e.key.keysym.sym == SDLK_a) {
            c = 'a';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_b) {
            c = 'b';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_c) {
            c = 'c';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_d) {
            c = 'd';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_e) {
            c = 'e';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_f) {
            c = 'f';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_g) {
            c = 'g';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_h) {
            c = 'h';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_i) {
            c = 'i';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_j) {
            c = 'j';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_k) {
            c = 'k';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_l) {
            c = 'l';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_m) {
            c = 'm';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_n) {
            c = 'n';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_o) {
            c = 'o';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_p) {
            c = 'p';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_q) {
            c = 'q';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_r) {
            c = 'r';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_s) {
            c = 's';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_t) {
            c = 't';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_u) {
            c = 'u';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_v) {
            c = 'v';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_w) {
            c = 'w';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_x) {
            c = 'x';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_y) {
            c = 'y';
            return 0;
        }
        if (e.key.keysym.sym == SDLK_z) {
            c = 'z';
            return 0;
        }
        if(e.key.keysym.sym == SDLK_RETURN) {
            return 1;
        }
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (x >= 50 && x <= 200) {
            if (y >= 361 && y <= 400) {
                if(!useHint) {
                    getHint(guessWord, secretWord, havePressed);
                    useHint = 1;
                    if(guessWord == secretWord)
                        return 1;
                }
            }
        }
    }
    return 0;
}

bool containLetter(string secretWord, char guess) {
    for(char c : secretWord) {
        if(guess == c)
            return true;
    }
    return false;
}

string updateWord(string &guessWord, string secretWord, char &playerGuess) {
    int lengthOfWord = secretWord.length();
    for(int i = 0; i < lengthOfWord; i++) {
        if(secretWord[i] == playerGuess)
            guessWord[i] = playerGuess;
    }
    return guessWord;
}


string toLowerCase(const string& s) {
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

void askForReplay(SDL_Event &e, bool &runGame, bool &win, map<char, int> &havePressed, int &badGuessCount,
                  bool &useHint, int &mess, string &secretWord, string &guessWord, const char* DATA_FILE) {

    while (true) {
        SDL_Delay(20);
        if (SDL_WaitEvent(&e) == 0) {
            continue;
        }
        if (e.type == SDL_QUIT) {
            runGame = false;
            return;
        }
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_RETURN) {
                runGame = true;
                win = 0;
                for(char i = 'a'; i <= 'z'; i++) {
                    havePressed[i] = 0;
                }
                badGuessCount = 0;
                useHint = 0;
                mess = 4;
                getGameData(secretWord, guessWord, DATA_FILE);
                system("cls");
                return ;
            }
            else {
                runGame = false;
                return ;
            }
        }
    }
}

void unload_SDL(vector <SDL_Texture*> background, vector <SDL_Texture*> letters, vector <SDL_Texture*> animations,
                           vector <SDL_Texture*> figures, SDL_Window* window, SDL_Renderer* renderer) {
    for(int i = 0; i < int(background.size()); i++)
        SDL_DestroyTexture(background[i]);
    for(int i = 0; i < int(letters.size()); i++)
        SDL_DestroyTexture(letters[i]);
    for(int i = 0; i < int(animations.size()); i++)
        SDL_DestroyTexture(animations[i]);
    for(int i = 0; i < int(figures.size()); i++)
        SDL_DestroyTexture(figures[i]);
    quitSDL(window, renderer);
}
