#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize();
    void Shutdown();

    void SetViewMatrix(const glm::mat4& view);
    void SetProjectionMatrix(const glm::mat4& projection);
    
    void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
    void DrawCircle(const glm::vec3& position, float radius, const glm::vec3& color);

private:
    std::unique_ptr<Shader> m_shader;
    GLuint m_quadVAO, m_quadVBO;
    GLuint m_circleVAO, m_circleVBO;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    void CreateQuadGeometry();
    void CreateCircleGeometry();
};
