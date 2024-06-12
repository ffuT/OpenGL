#include "Renderer.h"
#include <iostream>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
    GLCall(glClearColor(0, 0, 0, 1));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}