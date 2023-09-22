#include "Quad.h"


Quad::Quad(void* list, UINT size_vertex, UINT size_list)
{
	// Create a vertex buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	// load vertex shader
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// Get the shader data
	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

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
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertextShader(m_vs);

	// Draw Quad
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStip(m_vb->getSizeVertexList(), 0);
}

void Quad::release()
{
	m_vb->release();
}
