#include "GraphicsEngine.h"
#include "Renderer.h"
#include <iostream>

GraphicsEngine::GraphicsEngine() 
    : m_window(nullptr), m_width(0), m_height(0), m_initialized(false) {
}

GraphicsEngine::~GraphicsEngine() {
    Shutdown();
}

bool GraphicsEngine::Initialize(int width, int height, const std::string& title) {
    if (m_initialized) return true;

    glfwSetErrorCallback(ErrorCallback);
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    m_width = width;
    m_height = height;
    
    glViewport(0, 0, width, height);
    // Disable depth testing for 2D rendering
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->Initialize(width, height)) {
        std::cerr << "Failed to initialize renderer\n";
        return false;
    }

    m_initialized = true;
    return true;
}

void GraphicsEngine::Shutdown() {
    if (!m_initialized) return;
    
    m_renderer.reset();
    
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    
    glfwTerminate();
    m_initialized = false;
}

bool GraphicsEngine::IsRunning() const {
    return m_initialized && !glfwWindowShouldClose(m_window);
}

void GraphicsEngine::BeginFrame() {
    glfwPollEvents();
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::EndFrame() {
    glfwSwapBuffers(m_window);
}

void GraphicsEngine::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    GraphicsEngine* engine = static_cast<GraphicsEngine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->m_width = width;
        engine->m_height = height;
        glViewport(0, 0, width, height);
        // Update renderer's projection matrix for new size
        if (engine->m_renderer) {
            engine->m_renderer->UpdateProjection(width, height);
        }
    }
}

void GraphicsEngine::ErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}
