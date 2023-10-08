#include <format>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "ball.h"
#include "constants.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool game_is_running = true;

Ball *ball;

const static int FPS = 30;
const static int FRAME_TARGET_TIME = 1000 / FPS;
int last_frame_time = 0;

bool initialize_window() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << std::format("could not initialize sdl2: {0}\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, 
		SCREEN_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		std::cerr << std::format("could not create window: {0}\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		std::cerr << std::format("Error creating renderer {0}\n", SDL_GetError());
		return false;
	}

	return true;
}

void setup() {
	ball = new Ball(20.0, 20.0, 10.0);
}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		game_is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			game_is_running = false;
		}
	}
}

void update() {
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

	last_frame_time = SDL_GetTicks();

	ball->update(delta_time);
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw game objects
	filledCircleRGBA(renderer, ball -> x, ball -> y, ball -> radius, 255, 255, 255, 255);

	SDL_RenderPresent(renderer);
}

void cleanup() {
	SDL_DestroyWindow(window);
}

int main(int argc, char* args[]) {
	bool result = initialize_window();

	if (!result) {
		return -1;
	}

	setup();

	while (game_is_running) {
		process_input();
		update();
		render();
	}

	cleanup();

	return 0;
}
