#include "GraphicsEngine.h"
#include <iostream>

int main() {
    GraphicsEngine engine;
    
    if (!engine.Initialize(800, 600, "Connect4 Game")) {
        std::cerr << "Failed to initialize graphics engine\n";
        return -1;
    }

    while (engine.IsRunning()) {
        engine.BeginFrame();
        
        // Game rendering code will go here
        
        engine.EndFrame();
    }

    engine.Shutdown();
    return 0;
}
