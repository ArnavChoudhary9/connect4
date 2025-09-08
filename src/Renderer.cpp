#include "Renderer.h"
#include "Shader.h"
#include <cmath>
#include <vector>

Renderer::Renderer() : m_quadVAO(0), m_quadVBO(0), m_circleVAO(0), m_circleVBO(0) {
    m_viewMatrix = glm::mat4(1.0f);
    m_projectionMatrix = glm::mat4(1.0f);
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize() {
    m_shader = std::make_unique<Shader>();
    if (!m_shader->LoadFromSource(
        // Vertex shader
        R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
        )",
        // Fragment shader
        R"(
        #version 330 core
        out vec4 FragColor;
        
        uniform vec3 color;
        
        void main() {
            FragColor = vec4(color, 1.0);
        }
        )"
    )) {
        return false;
    }

    CreateQuadGeometry();
    CreateCircleGeometry();
    
    return true;
}

void Renderer::Shutdown() {
    if (m_quadVAO) {
        glDeleteVertexArrays(1, &m_quadVAO);
        glDeleteBuffers(1, &m_quadVBO);
    }
    if (m_circleVAO) {
        glDeleteVertexArrays(1, &m_circleVAO);
        glDeleteBuffers(1, &m_circleVBO);
    }
    m_shader.reset();
}

void Renderer::SetViewMatrix(const glm::mat4& view) {
    m_viewMatrix = view;
}

void Renderer::SetProjectionMatrix(const glm::mat4& projection) {
    m_projectionMatrix = projection;
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color) {
    m_shader->Use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
    
    m_shader->SetMat4("model", model);
    m_shader->SetMat4("view", m_viewMatrix);
    m_shader->SetMat4("projection", m_projectionMatrix);
    m_shader->SetVec3("color", color);
    
    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::DrawCircle(const glm::vec3& position, float radius, const glm::vec3& color) {
    m_shader->Use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
    
    m_shader->SetMat4("model", model);
    m_shader->SetMat4("view", m_viewMatrix);
    m_shader->SetMat4("projection", m_projectionMatrix);
    m_shader->SetVec3("color", color);
    
    glBindVertexArray(m_circleVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
}

void Renderer::CreateQuadGeometry() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);

    glBindVertexArray(m_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::CreateCircleGeometry() {
    std::vector<float> vertices;
    vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); // Center
    
    const int segments = 30;
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        vertices.push_back(cos(angle));
        vertices.push_back(sin(angle));
        vertices.push_back(0.0f);
    }

    glGenVertexArrays(1, &m_circleVAO);
    glGenBuffers(1, &m_circleVBO);

    glBindVertexArray(m_circleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_circleVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
