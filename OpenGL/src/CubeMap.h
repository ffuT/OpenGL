#pragma once
#include "Renderer.h"

class CubeMap{
public:
	CubeMap(std::string path);
	~CubeMap();

	void Bind(unsigned int slot) const;
	void UnBind() const;

private:
	unsigned int m_rendererID;
	std::string m_filepath;

};
