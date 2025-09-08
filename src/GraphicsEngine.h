#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

class Shader;
class Renderer;

class GraphicsEngine {
public:
    GraphicsEngine();
    ~GraphicsEngine();

    bool Initialize(int width, int height, const std::string& title);
    void Shutdown();
    bool IsRunning() const;
    
    void BeginFrame();
    void EndFrame();
    
    GLFWwindow* GetWindow() const { return m_window; }
    Renderer* GetRenderer() const { return m_renderer.get(); }
    
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    GLFWwindow* m_window;
    std::unique_ptr<Renderer> m_renderer;
    int m_width, m_height;
    bool m_initialized;
    
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void ErrorCallback(int error, const char* description);
};
