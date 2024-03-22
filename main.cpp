/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL and standard IO
// #include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

// stores an BMP image
SDL_Surface *image = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Window *window = NULL;

bool init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  } else {
    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
                << std::endl;
      return false;
    } else {
      // Get window surface
      screenSurface = SDL_GetWindowSurface(window);
      return true;
      // Fill the surface white
      // SDL_FillRect(screenSurface, NULL,
      //              SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    }
  }

  return true;
}

bool loadImage() {
  // Load image
  image = SDL_LoadBMP("example.bmp");

  if (image == NULL) {
    std::cout << "Unable to load BPM. Error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void close() {
  // Deallocate surface
  SDL_FreeSurface(image);
  image = NULL;

  // Destroy window
  SDL_DestroyWindow(window);
  window = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[]) {

  if (!init()) {
    std::cout << "Failed to initialize" << std::endl;
  } else {
    // Load image
    if (!loadImage()) {
      std::cout << "Failed to load image" << std::endl;
    } else {
      // SDL_BlitSurface(image, NULL, screenSurface, NULL);
      // // Update the surface
      // SDL_UpdateWindowSurface(window); // Hack to get window to stay up
      // Hack to stay the window opened
      SDL_Event e;
      bool quit = false;
      // While the application is running = main loop
      while (!quit) {
        // While has inputs in the queue that is not quit the window
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT)
            quit = true;
        }

        SDL_BlitSurface(image, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
      }
    }
  }

  close();

  return 0;
}
