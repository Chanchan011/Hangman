#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "util.h"
#include "init.h"
using namespace std;

void mainMenu(SDL_Window* window, SDL_Renderer* renderer, vector <SDL_Texture*> background,
              vector <SDL_Texture*> letters, vector <SDL_Texture*> animations, vector <SDL_Texture*> figures);

vector <SDL_Texture*> loadBackground(SDL_Renderer* renderer) {
    vector <SDL_Texture*> v;
    v.push_back(loadTexture("images/mainmenu.bmp", renderer));
    v.push_back(loadTexture("images/info.bmp", renderer));
    v.push_back(loadTexture("images/background.bmp", renderer));
    v.push_back(loadTexture("images/hint.bmp", renderer));
    for(int i=0; i<7; i++) {
        string s = "mess";
        s += to_string(i);
        v.push_back(loadTexture("images/" + s + ".bmp", renderer));
    }
    return v;
}

vector <SDL_Texture*> loadLetters(SDL_Renderer* renderer) {
    vector <SDL_Texture*> v;
    v.push_back(loadTexture("images/-.bmp", renderer));
    char ch = 'a';
    string s = "";
    for(int i=0; i<26; i++) {
        ch = char('a' + i);
        s = "";
        s += ch;
        v.push_back(loadTexture("images/" + s + ".bmp", renderer));
    }
    return v;
}

vector <SDL_Texture*> loadAnimations(SDL_Renderer* renderer) {
    vector <SDL_Texture*> v;
    for(int i=0; i<18; i++) {
        string s = "ani";
        s += to_string(i);
        v.push_back(loadTexture("images/" + s + ".bmp", renderer));
    }
    return v;
}

vector <SDL_Texture*> loadFigures(SDL_Renderer* renderer) {
    vector <SDL_Texture*> v;
    for(int i=0; i<7; i++) {
        string s = "fig";
        s += to_string(i);
        v.push_back(loadTexture("images/" + s + ".bmp", renderer));
    }
    return v;
}

void getHelp(SDL_Window* window, SDL_Renderer* renderer, vector <SDL_Texture*> background,
             vector <SDL_Texture*> letters, vector <SDL_Texture*> animations, vector <SDL_Texture*> figures) {
    SDL_RenderClear(renderer);
    renderTexture(background[1], renderer, 0, 0, 800, 600);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            unload_SDL(background, letters, animations, figures, window, renderer);
            exit(1);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x = e.button.x;
            int y = e.button.y;
            if(x >= 0 && x <= 100) {
                if(y >= 0 && y <= 50) {
                    mainMenu(window, renderer, background, letters, animations, figures);
                    break;
                }
            }
        }
    }
}

void mainMenu(SDL_Window* window, SDL_Renderer* renderer, vector <SDL_Texture*> background,
              vector <SDL_Texture*> letters, vector <SDL_Texture*> animations, vector <SDL_Texture*> figures) {
    SDL_RenderClear(renderer);
    renderTexture(background[0], renderer, 0, 0, 800, 600);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            unload_SDL(background, letters, animations, figures, window, renderer);
            exit(1);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x = e.button.x;
            int y = e.button.y;
            if(x >= 300 && x <= 500) {
                if(y >= 200 && y <= 275) {
                    return ;
                }
                else if(y >= 300 && y <= 375)
                    getHelp(window, renderer, background, letters, animations, figures);
            }
        }
    }
}

