#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

using namespace std;

vector <SDL_Texture*> loadBackground(SDL_Renderer* renderer);
vector <SDL_Texture*> loadLetters(SDL_Renderer* renderer);
vector <SDL_Texture*> loadAnimations(SDL_Renderer* renderer);
vector <SDL_Texture*> loadFigures(SDL_Renderer* renderer);
void mainMenu(SDL_Window* window, SDL_Renderer* renderer, vector <SDL_Texture*> background,
              vector <SDL_Texture*> letters, vector <SDL_Texture*> animations, vector <SDL_Texture*> figures);
void getHelp(SDL_Window* window, SDL_Renderer* renderer, vector <SDL_Texture*> background,
             vector <SDL_Texture*> letters, vector <SDL_Texture*> animations, vector <SDL_Texture*> figures);


#endif // GAME_H_INCLUDED

