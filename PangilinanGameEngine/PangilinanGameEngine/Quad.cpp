#include "Quad.h"


Quad::Quad(void* list, UINT size_vertex, UINT size_list)
{
	// Create a vertex buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;

	// Get the shader data
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	// load the vertices
	m_vb->load(list, size_vertex, size_list, shader_byte_code, size_shader);

}

Quad::~Quad()
{
}

void Quad::drawQuad()
{
	// Set Vertex Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// Draw Quad
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStip(m_vb->getSizeVertexList(), 0);
}

void Quad::release()
{
	m_vb->release();
}
