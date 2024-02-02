#include <SDL.h>
#include <vector>
#include <map>
#include "Renderer/Renderer.h"
#include "SimpleWorld/SimpleWorld.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int GRID_ROWS = 50;
const int GRID_COLS = 50;
const int SQUARE_SIZE = 10; // Stellen Sie sicher, dass WINDOW_WIDTH und WINDOW_HEIGHT ein Vielfaches von GRID_ROWS bzw. GRID_COLS plus Rand sind


int main(int argc, char* argv[]) {
    SimpleWorld world = SimpleWorld();
    world.run();
    return 0;
}


