// This is the main SDL include file
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
// iostream is so we can output error messages to console
#include <iostream>

#include "Camera.h"
#include "Ray.h"
#include "Tracer.h"


int main(int argc, char *argv[])
{
	//Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}


	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("RayTracer?", winPosX, winPosY, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//Image loading
	std::string filename("image.bmp");

	SDL_Surface * image = SDL_LoadBMP(filename.c_str());
	if (!image)
	{
		std::cout << "Oh dear, sorry but I can't find your image file. This brings me great sadness :(" << std::endl;
		SDL_Delay(100);
		SDL_Quit();
		return -1;
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);
	//Init end

	Camera camGirlNo1;
	Tracer fuckTracer;

	bool go = true;
	while (go)
	{
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
			{
				go = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				std::cout << "key pressed!" << std::endl;
				if (incomingEvent.key.keysym.sym == SDLK_LEFT)
				{
					std::cout << "Left key pressed!!!" << std::endl;
				}
				break;
			}
			}
		}


		// Update

		// Draw our world

		//Clear the screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);

		for (size_t x = 0; x < winWidth; x++)
		{
			for (size_t y = 0; y < winHeight; y++)
			{
				glm::vec3 col = fuckTracer.TraceRay(camGirlNo1.ReturnRay(x, y));
				SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 0);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_Rect destRect;
		destRect.x = 100;
		destRect.y = 100;

		SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

		//SDL_RenderCopy(renderer, texture, NULL, &destRect);
		SDL_RenderPresent(renderer);
	}

	//Cleanup
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}