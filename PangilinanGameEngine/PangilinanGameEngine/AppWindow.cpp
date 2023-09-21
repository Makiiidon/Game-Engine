#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		//X - Y - Z
		{ -0.1f,	-0.1f,	0.0f }, // POS1
		{  0.0f,	 0.1f,	0.0f }, // POS2
		{  0.1f,	-0.1f,	0.0f },
	};

	vertex quadList1[] = {
		{ -0.1f - .4f,	-0.1f - .4f,	0.0f }, // POS1
		{ -0.1f - .4f,	 0.1f - .4f,	0.0f }, // POS2
		{  0.1f - .4f,	-0.1f - .4f,	0.0f }, // POS3
		{  0.1f - .4f,	 0.1f - .4f,	0.0f }, // POS4
	};

	vertex quadList2[] = {
		{ -0.1f + .4f,	-0.2f + .4f,	0.0f }, // POS1
		{ -0.1f + .4f,	 0.2f + .4f,	0.0f }, // POS2
		{  0.1f + .4f,	-0.2f + .4f,	0.0f }, // POS3
		{  0.1f + .4f,	 0.2f + .4f,	0.0f }, // POS4
	};

	vertex quadList3[] =
	{
		//X - Y - Z
		{ -0.1f,	-0.1f + 0.5f,	0.0f }, // POS1
		{ -0.1f,	 0.1f + 0.5f,	0.0f }, // POS2
		{  0.1f,	-0.1f + 0.5f,	0.0f },
		{  0.1f,	 0.1f + 0.5f,	0.0f },
	};

	// CREATE VERTEX BUFFER FOR THE TRIANGLE
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	// 
	UINT size_list = ARRAYSIZE(list);

	UINT size_quadList1 = ARRAYSIZE(quadList1);
	UINT size_quadList2 = ARRAYSIZE(quadList2);
	UINT size_quadList3 = ARRAYSIZE(quadList3);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	// INITIALIZE QUADS
	quad1 = new Quad(quadList1, sizeof(vertex), size_quadList1);
	quad2 = new Quad(quadList2, sizeof(vertex), size_quadList2);
	quad3 = new Quad(quadList3, sizeof(vertex), size_quadList3);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	// DRAW QUADS
	quad1->drawQuad();
	quad2->drawQuad();
	quad3->drawQuad();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vb->release();
	quad1->release();
	quad2->release();
	quad3->release();
	GraphicsEngine::get()->release();
}