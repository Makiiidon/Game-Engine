#pragma once

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

class Quad
{
public:
	Quad(void* list, UINT size_vertex, UINT size_list);
	~Quad();

	void drawQuad();

	void release();

private:
	VertexBuffer* m_vb;

};

