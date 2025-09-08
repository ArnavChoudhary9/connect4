#include "GraphicsEngine.h"
#include "Renderer.h"
#include <iostream>

int main() {
    GraphicsEngine engine;
    
    if (!engine.Initialize(800, 600, "Connect4")) {
        std::cerr << "Failed to initialize graphics engine\n";
        return -1;
    }

    auto* renderer = engine.GetRenderer();

    while (engine.IsRunning()) {
        engine.BeginFrame();
        
        // Draw a red quad
        renderer->DrawQuad({ 100, 100, 0 }, { 100, 100 }, { 1.0f, 0.0f, 0.0f });
        renderer->DrawQuad({ 0, 0, 0 }, { 100, 100 }, { 1.0f, 0.0f, 0.0f });
        
        // Draw a green circle
        renderer->DrawCircle({ 300, 150, 0 }, 50, { 0.0f, 1.0f, 0.0f });

        // Draw a blue triangle
        renderer->DrawTriangle(
            { 500, 100, 0 },
            { 450, 200, 0 },
            { 550, 200, 0 },
            { 0.0f, 0.0f, 1.0f }
        );
        
        // Draw yellow lines
        renderer->DrawLine({ 100, 300, 0 }, { 300, 350, 0 }, 5.0f, { 1.0f, 1.0f, 0.0f });
        renderer->DrawLine({ 400, 300, 0 }, { 600, 400, 0 }, 3.0f, { 1.0f, 0.5f, 0.0f });

        engine.EndFrame();
    }

    engine.Shutdown();
    return 0;
}
