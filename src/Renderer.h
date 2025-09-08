#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(int width, int height);
    void Shutdown();
    
    void UpdateProjection(int width, int height);

    void SetViewMatrix(const glm::mat4& view);
    void SetProjectionMatrix(const glm::mat4& projection);
    
    // Basic shape drawing methods
    void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
    void DrawCircle(const glm::vec3& position, float radius, const glm::vec3& color);
    void DrawTriangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& color);
    void DrawLine(const glm::vec3& start, const glm::vec3& end, float thickness, const glm::vec3& color);

private:
    std::unique_ptr<Shader> m_shader;
    GLuint m_quadVAO, m_quadVBO;
    GLuint m_circleVAO, m_circleVBO;
    GLuint m_triangleVAO, m_triangleVBO;
    GLuint m_lineVAO, m_lineVBO;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    int m_screenWidth, m_screenHeight;
    
    void CreateQuadGeometry();
    void CreateCircleGeometry();
    void CreateTriangleGeometry();
    void CreateLineGeometry();
    void SetupOrthographicProjection();
};
