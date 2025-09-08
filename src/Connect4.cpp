#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Renderer.h"
#include <iostream>

int main() {
    const glm::vec3 clearColor = { 0.1f, 0.1f, 0.1f };
    const int rows = 5;
    const int cols = 7;
    const float cellSize = 100.0f;

    GraphicsEngine engine;
    
    if (!engine.Initialize(800, 600, "Connect4")) {
        std::cerr << "Failed to initialize graphics engine\n";
        return -1;
    }

    auto* renderer = engine.GetRenderer();

    while (engine.IsRunning()) {
        engine.BeginFrame(clearColor);

        // Draw grid lines
        for (int row = 0; row < rows; row++) {
            float y = (row - (rows - 1) / 2.0f) * cellSize;
            float startX = -(cols - 1) / 2.0f * cellSize;
            float endX = (cols - 1) / 2.0f * cellSize;
            renderer->DrawLine({ startX, y, 0.0f }, { endX, y, 0.0f }, 6.0f, { 0.4f, 0.4f, 0.4f });
        }

        for (int col = 0; col < cols; col++) {
            float x = (col - (cols - 1) / 2.0f) * cellSize;
            float startY = -(rows - 1) / 2.0f * cellSize;
            float endY = (rows - 1) / 2.0f * cellSize;
            renderer->DrawLine({ x, startY, 0.0f }, { x, endY, 0.0f }, 6.0f, { 0.4f, 0.4f, 0.4f });
        }

        // Draw circles at grid corners
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                float x = (col - (cols - 1) / 2.0f) * cellSize;
                float y = (row - (rows - 1) / 2.0f) * cellSize;
                renderer->DrawCircle({ x, y, 0.0f }, 10.0f, { 0.9f, 0.9f, 0.9f });
            }
        }

        engine.EndFrame();
    }

    engine.Shutdown();
    return 0;
}
