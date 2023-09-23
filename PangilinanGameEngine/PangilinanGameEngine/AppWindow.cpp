#include "AppWindow.h"
#include <Windows.h>>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
}; 

__declspec(align(16))
struct constant
{
	float m_time;
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

	vertex quadList1[] = {
		{ -0.5f, -0.5f,	0.0f,  -0.32f, -0.11f, 0.0f,   0, 0, 0,   0, 1, 0}, // POS1
		{ -0.5f,  0.5f,	0.0f,  -0.11f,  0.78f, 0.0f,   1, 1, 0,   1, 1, 0}, // POS2
		{  0.5f, -0.5f,	0.0f,   0.75f, -0.73f, 0.0f,   0, 0, 1,   1, 0, 0}, // POS3
		{  0.5f,  0.5f,	0.0f,   0.88f,  0.77f, 0.0f,   1, 1, 1,   0, 0, 1}, // POS4
	};

	//vertex quadList2[] = {
	//	{ -0.1f, -0.1f,	0.0f,  -0.2f, -0.2f, 0.0f,   1, 0, 0,   0, 1, 1}, // POS1
	//	{ -0.1f,  0.1f,	0.0f,  -0.2f,  0.2f, 0.0f,   0, 1, 1,   0, 1, 0}, // POS2
	//	{  0.1f, -0.1f,	0.0f,   0.2f, -0.2f, 0.0f,   1, 0, 1,   0, 0, 1}, // POS3
	//	{  0.1f,  0.1f,	0.0f,   0.2f,  0.2f, 0.0f,   0, 1, 0,   0, 0, 1}, // POS4
	//};

	//vertex quadList3[] =
	//{
	//	//	//X - Y - Z
	//	{ -0.8f, -1.0f,	0.0f,  -0.7f, -0.6f, 0.0f,   1, 0, 0,   0, 1, 1}, // POS1
	//	{ -0.8f,  0.2f, 0.0f,  -0.5f,  0.3f, 0.0f, 0, 1, 1, 0, 1, 0}, // POS2
	//	{ 0.8f, -0.1f,	0.0f,  -0.5f, -0.2f, 0.0f,   1, 0, 1,   0, 0, 1 }, // POS3
	//	{ 0.8f,  0.1f,	0.0f,  -0.5f,  0.2f, 0.0f,   0, 1, 0,   0, 0, 1 }, // POS4
	//};

	// CREATE VERTEX BUFFER FOR THE TRIANGLE
	//m_vb = GraphicsEngine::get()->createVertexBuffer();



	UINT size_quadList1 = ARRAYSIZE(quadList1);
	//UINT size_quadList2 = ARRAYSIZE(quadList2);
	//UINT size_quadList3 = ARRAYSIZE(quadList3);


	/*void* shader_byte_code = nullptr;
	size_t size_shader = 0;*/
	//GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	//m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);


	// INITIALIZE QUADS
	quad1 = new Quad(quadList1, sizeof(vertex), size_quadList1);
	//quad2 = new Quad(quadList2, sizeof(vertex), size_quadList2);
	//quad3 = new Quad(quadList3, sizeof(vertex), size_quadList3);

	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
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

	constant cc;
	cc.m_time = ::GetTickCount64();

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	// DRAW QUADS
	quad1->drawQuad(m_cb);
	//quad2->drawQuad(m_cb);
	//quad3->drawQuad(m_cb);

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	//m_vb->release();
	quad1->release();
	//quad2->release();
	//quad3->release();
	GraphicsEngine::get()->release();
}