#include <SDL.h>
#include <stdio.h>

#include <stdint.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef size_t memory_index;

typedef float real32;
typedef double real64;

#define internal static
#define local_persist static
#define global_variable static


#include <math.h>

inline int32
RoundReal32ToInt32(real32 Real32)
{
    int32 Result = (int32)roundf(Real32);
    // TODO(casey): intrinsic?
    return Result;
}

inline uint32
RoundReal32ToUInt32(real32 Real32)
{
    uint32 Result = (uint32)roundf(Real32);
    // TODO(casey): intrinsic?
    return Result;
}

struct game_offscreen_buffer {
    // NOTE(steve): Pixels are always 32-bits wide, little endian: Memory Order 0x BB GG RR xx
    void *Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};

internal void
DrawRectangle(game_offscreen_buffer *Buffer, real32 rMinX, real32 rMaxX, 
              real32 rMinY, real32 rMaxY, real32 R, real32 G, real32 B) 
{
    int32 MinX = RoundReal32ToInt32(rMinX);
    int32 MinY = RoundReal32ToInt32(rMinY);
    int32 MaxX = RoundReal32ToInt32(rMaxX);
    int32 MaxY = RoundReal32ToInt32(rMaxY);

    if (MinX < 0) {
        MinX = 0;
    }

    if (MinY < 0) {
        MinY = 0;
    }

    if (MaxX > Buffer->Width) {
        MaxX = Buffer->Width;
    }

    if (MaxY > Buffer->Height) {
        MaxY = Buffer->Height;
    }

    uint32 Color = ((RoundReal32ToUInt32(R * 255.0f) << 16) |
                    (RoundReal32ToUInt32(G * 255.0f) << 8) |
                    (RoundReal32ToUInt32(B * 255.0f) << 0));
                   

    uint8 *Row = ((uint8 *)Buffer->Memory + 
                    (MinX * Buffer->BytesPerPixel) +
                    (MinY * Buffer->Pitch));
    for (int Y = MinY; Y < MaxY; Y++) {
        uint32 *Pixel = (uint32 *)Row;
        for (int X = MinX; X < MaxX; X++) {
            *Pixel++ = Color;
        }
        Row += Buffer->Pitch;
    }
}

int 
main(int argc, char **args) 
{
	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 768;

 	bool quit = false;
	SDL_Event e;
	SDL_Window* Window = NULL;
	SDL_Surface* screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else	{
		Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
								  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
								  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(Window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		} else {
			game_offscreen_buffer Buffer;
			Buffer.Width = SCREEN_WIDTH;
            Buffer.Height = SCREEN_HEIGHT;
			Buffer.Pitch = SCREEN_WIDTH;
			Buffer.BytesPerPixel = 4;

			screenSurface = SDL_GetWindowSurface(Window);
			Buffer.Memory = screenSurface->pixels;
			while(!quit) {
				while(SDL_PollEvent(&e) != 0) { 
					if(e.type == SDL_QUIT) { 
						quit = true;
					}

					SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
					
					DrawRectangle(&Buffer, 30, 90, 30, 90, 0xFF, 0x00, 0x00);

					SDL_UpdateWindowSurface(Window);
				}
			}
		}
	}

	SDL_DestroyWindow(Window);
	SDL_Quit();
	return 0;
}