#include <SDL.h>
#include <stdio.h>

int 
main(int argc, char **args) 
{
	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 768;

 	bool quit = false;
	SDL_Event e;
	SDL_Window* Window = NULL;
	SDL_Surface* screenSurface = NULL;

	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else	{
		Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
								  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
								  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(Window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		} else {
			while(!quit) {
				while(SDL_PollEvent(&e) != 0) { 
					if(e.type == SDL_QUIT) { 
						quit = true;
					}

					screenSurface = SDL_GetWindowSurface(Window);

					SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
					
					// screenSurface->pixels = ;

					SDL_UpdateWindowSurface(Window);
				}
			}
		}
	}

	SDL_DestroyWindow(Window);
	SDL_Quit();
	return 0;
}