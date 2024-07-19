#include "CubeMap.h"
#include "stb_image/stb_image.h"
#include <iostream>

CubeMap::CubeMap(std::string path) : m_filepath(path), m_rendererID(0) {
    std::string faces[6] = {
        "/right.jpg", "/left.jpg",
        "/top.jpg", "/bottom.jpg",
        "/back.jpg", "/front.jpg"
    };
    GLCall(glGenTextures(1, &m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererID));

    int width, height, nrChannels;
    for (unsigned int i = 0; i < 6; i++) {
        std::string fullPath = m_filepath + faces[i];
        unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
        
        if (data) {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            GLCall(glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                format,
                width,
                height,
                0,
                format,
                GL_UNSIGNED_BYTE,
                data 
            ));
            std::cout << "Loaded cubemap texture: " << fullPath << " (" << width << "x" << height << ", " << nrChannels << " channels)" << std::endl;
            stbi_image_free(data);
        }
        else {
            std::cerr << "Cubemap texture failed to load at path: " << fullPath << std::endl;
            stbi_image_free(data);
        }
    }
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

}

CubeMap::~CubeMap() {
    GLCall(glDeleteTextures(1, &m_rendererID));
}

void CubeMap::Bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererID));
}

void CubeMap::UnBind() const {
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}
