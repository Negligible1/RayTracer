// This is the main SDL include file
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
// iostream is so we can output error messages to console
#include <iostream>
#include <thread>
#include <mutex>

#include "Camera.h"
#include "Ray.h"
#include "Tracer.h"

std::mutex mtx;

void TopLeft(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer);
void TopRight(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer);
void BottomLeft(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer);
void BottomRight(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer);
void DrawPoint(SDL_Renderer* renderer, glm::vec3 colour, int x, int y);
void ThreadHandler(int winX, int winY, SDL_Renderer* renderer, int NoOfThreads, Tracer* fuckTracer, Camera* camGirlNo1);
void ScreenSegment(int startX, int endX, int startY, int endY, SDL_Renderer* renderer, Tracer* fuckTracer, Camera* camGirlNo1);

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
	int winX = 640;
	int winY = 480;
	SDL_Window *window = SDL_CreateWindow("RayTracer?", winPosX, winPosY, winX, winY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	//Init end

	//Making stuff
	Camera camGirlNo1;
	Tracer fuckTracer;
	Sphere mySphere = Sphere(glm::vec3(winX / 2, winY / 2, -1000), 100);
	Sphere mySphere3 = Sphere(glm::vec3(20, 20, -1000), 9);
	mySphere.colour = glm::vec3(0, 0, 1);
	mySphere3.colour = glm::vec3(1, 0, 0);
	fuckTracer.AddObject(&mySphere);
	fuckTracer.AddObject(&mySphere3);


	//Unthreaded
	/*
	for (size_t x = 0; x < winX; x++)
	{
		for (size_t y = 0; y < winY; y++)
		{
			glm::vec3 col = fuckTracer.TraceRay(camGirlNo1.ReturnRay(x, y, winX, winY));
			SDL_SetRenderDrawColor(renderer, (col.x * 255), (col.y * 255), (col.z * 255), 0);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	*/

	bool left = false;
	bool right = true;

	

	//This may return 0 if it cannot detect, so we'll manually set it to one in that case because there will probably be one core
	unsigned noOfThreadsSupported = std::thread::hardware_concurrency();
	if (noOfThreadsSupported == 0)
	{
		noOfThreadsSupported = 1;
	}

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

		//Clear the screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);

		// Update
		if (mySphere.GetPos().x > winX)
		{
			left = true;
			right = false;
		}

		if (mySphere.GetPos().x < 0)
		{
			left = false;
			right = true;
		}

		if (right)
		{
			mySphere.UpdatePosition(glm::vec3(10, 0, 0));
		}

		if (left)
		{
			mySphere.UpdatePosition(glm::vec3(-10, 0, 0));
		}
		
		std::thread BL(BottomLeft, winX, winY, &fuckTracer, &camGirlNo1, renderer);
		std::thread BR(BottomRight, winX, winY, &fuckTracer, &camGirlNo1, renderer);
		std::thread TL(TopLeft, winX, winY, &fuckTracer, &camGirlNo1, renderer);
		std::thread TR(TopRight, winX, winY, &fuckTracer, &camGirlNo1, renderer);

		BL.join();
		BR.join();
		TL.join();
		TR.join();

		// Draw our world
		SDL_RenderPresent(renderer);
	}

	//Cleanup
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void TopLeft(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer)
{
	for (size_t x = 0; x < winX / 2; x++)
	{
		for (size_t y = 0; y < winY / 2; y++)
		{
			glm::vec3 col = fuckTracer->TraceRay(camGirlNo1->ReturnRay(x, y, winX, winY));
			DrawPoint(renderer, col, x, y);
		}
	}
}

void ThreadHandler(int winX, int winY, SDL_Renderer* renderer, int NoOfThreads, Tracer* fuckTracer, Camera* camGirlNo1)
{
	std::vector<std::thread> threads;
	int winXDiv = winX / NoOfThreads;
	int winYDiv = winY / NoOfThreads;

	for (size_t i = 0; i < NoOfThreads; i++)
	{
		threads.push_back(std::thread(ScreenSegment, (winXDiv * i), winXDiv * (i+1), (winYDiv * i), winYDiv * (i + 1), renderer, fuckTracer, camGirlNo1));
	}

	for (size_t i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}
}

void ScreenSegment(int startX, int endX, int startY, int endY, SDL_Renderer* renderer, Tracer* fuckTracer, Camera* camGirlNo1)
{
	for (size_t x = startX; x < endX; x++)
	{
		for (size_t y = startY; y < endY; y++)
		{
			DrawPoint(renderer, (fuckTracer->TraceRay(camGirlNo1->ReturnRay(x, y, 0, 0))), x ,y);
		}
	}
}

void TopRight(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer)
{
	for (size_t x = winX / 2; x < winX; x++)
	{
		for (size_t y = 0; y < winY / 2; y++)
		{
			glm::vec3 col = fuckTracer->TraceRay(camGirlNo1->ReturnRay(x, y, winX, winY));
			DrawPoint(renderer, col, x, y);
		}
	}
}

void BottomLeft(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer)
{
	for (size_t x = 0; x < winX / 2; x++)
	{
		for (size_t y = winY / 2; y < winY; y++)
		{
			glm::vec3 col = fuckTracer->TraceRay(camGirlNo1->ReturnRay(x, y, winX, winY));
			DrawPoint(renderer, col, x, y);
		}
	}
}

void BottomRight(int winX, int winY, Tracer* fuckTracer, Camera* camGirlNo1, SDL_Renderer* renderer)
{
	for (size_t x = winX / 2; x < winX; x++)
	{
		for (size_t y = winY / 2; y < winY; y++)
		{
			glm::vec3 col = fuckTracer->TraceRay(camGirlNo1->ReturnRay(x, y, winX, winY));
			DrawPoint(renderer, col, x, y);
		}
	}
}

void DrawPoint(SDL_Renderer* renderer, glm::vec3 colour, int x, int y)
{
	mtx.lock();
	SDL_SetRenderDrawColor(renderer, (colour.x * 255), (colour.y * 255), (colour.z * 255), 0);
	SDL_RenderDrawPoint(renderer, x, y);
	mtx.unlock();
}