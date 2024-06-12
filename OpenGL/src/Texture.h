#pragma once

#include "Renderer.h"

class Texture{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Widht, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot) const;
	void UnBind() const;

	inline int GetWidth() const { return m_Widht; }
	inline int GetHeight() const { return m_Height; }

};

