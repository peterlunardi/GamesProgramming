#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "MeshRenderer.h"
#include "Quad.h"
#include "CameraComp.h"
#include "Input.h"
#include "Resources.h"
#include "Physics.h"
#include "BoxShape.h"
#include "RigidBody.h"

Application *Application::m_application = nullptr;
float counter = 0;

Application::Application()
{

}

void Application::Init()
{
	//performing initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG_DEBUG(SDL_GetError());
		exit(-1);
	}
	//setting openGL version to 4.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//setting openGL context to core, not compatibility
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//creating window
	m_window = SDL_CreateWindow(
		"GP3-GAME",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_windowWidth, m_windowHeight,
		SDL_WINDOW_OPENGL
	);
	SDL_CaptureMouse(SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	lastX = m_windowWidth / 2;
	lastY = m_windowHeight / 2;

	OpenGlInit();
	GameInit();
}

void Application::OpenGlInit()
{
	//creating context (our opengl statemachine in which all our GL calls will refer to)
	m_glContext = SDL_GL_CreateContext(m_window);
	CHECK_GL_ERROR();
	SDL_GL_SetSwapInterval(1);

	//initialsing glew (do this after establishing context!)
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}

	//Smooth shading
	//GL_ATTEMPT(glShadeModel(GL_SMOOTH));

	//enable depth testing
	GL_ATTEMPT(glEnable(GL_DEPTH_TEST));

	//set less or equal func for depth testing
	GL_ATTEMPT(glDepthFunc(GL_LEQUAL));

	//enabling blending
	glEnable(GL_BLEND);
	GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//turn on back face culling
	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));

	glViewport(0, 0, (GLsizei)m_windowWidth, (GLsizei)m_windowHeight);
}

void Application::GameInit()
{
	//loading all resources
	Resources::GetInstance()->AddModel("cube.obj");
	Resources::GetInstance()->AddModel("penguin.obj");
	Resources::GetInstance()->AddTexture("penguinTex.png");
	Resources::GetInstance()->AddModel("turkey.obj");
	Resources::GetInstance()->AddTexture("turkey.jpg");
	Resources::GetInstance()->AddTexture("Wood.jpg");
	Resources::GetInstance()->AddShader(new ShaderProgram(ASSET_PATH + "simple_VERT.glsl", ASSET_PATH + "simple_FRAG.glsl"), "simple");

	//The ground!
	Entity* a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("cube.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Wood.jpg"))
	);
	MeshRenderer* m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)));
	a->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	a->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 100.f));

	for (int i = 0; i < 100; i++)
	{
		Entity* a = new Entity();
		m_entities.push_back(a);
		a->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("cube.obj"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Wood.jpg"))
		);
		a->GetTransform()->SetPosition(glm::vec3(0, 5.f * i, -20.f));
		a->AddComponent<RigidBody>();
		a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 1.f)));
		a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	}

	//penguin!!
	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("penguin.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("penguinTex.png"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(10, 5, -10));

	//turkey!!
	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("turkey.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("turkey.jpg"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(15, 5, -10));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 1.f)));
	a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	a = new Entity();
	m_entities.push_back(a);
	CameraComp* cc = new CameraComp();
	a->AddComponent(cc);
	cc->Start();
}

void Application::Loop()
{
	m_appState = AppState::RUNNING;
	auto prevTicks = std::chrono::high_resolution_clock::now();
	
	while (m_appState != AppState::QUITTING)
	{
		auto currentTicks = std::chrono::high_resolution_clock::now();
		float deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - prevTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		prevTicks = currentTicks;

		ProcessInput(deltaTime);
		Physics::GetInstance()->Update(deltaTime);
		Update(deltaTime);
		Render();

		SDL_GL_SwapWindow(m_window);
	}
}

void Application::ProcessInput(float deltaTime)
{
	SDL_Event event;

	//poll SDL events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_appState = AppState::QUITTING;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			m_appState = AppState::QUITTING;
			break;
		case SDL_KEYDOWN:
			INPUT->SetKey(event.key.keysym.sym, true);
			break;
			//record when the user releases a key
		case SDL_MOUSEMOTION:
			INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));

			int xpos = event.motion.x;
			int ypos = event.motion.y;

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			m_mainCamera->ProcessMouseMovement(xoffset, yoffset);
		}
	}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_W])
	{
		m_mainCamera->ProcessKeyboard(FORWARD, deltaTime);

	}
	if (keystates[SDL_SCANCODE_A])
	{
		m_mainCamera->ProcessKeyboard(LEFT, deltaTime);
	}
	if (keystates[SDL_SCANCODE_S])
	{
		m_mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keystates[SDL_SCANCODE_D])
	{
		m_mainCamera->ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keystates[SDL_SCANCODE_LSHIFT])
	{
		m_mainCamera->ProcessKeyboard(UP, deltaTime);
	}
	if (keystates[SDL_SCANCODE_LCTRL])
	{
		m_mainCamera->ProcessKeyboard(DOWN, deltaTime);
	}
}

void Application::Update(float deltaTime)
{
	for (auto& a : m_entities)
	{
		a->OnUpdate(deltaTime);
	}
}
void Application::Render()
{
	/* Clear context */
	glClearColor(0.f, 0.25f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_mainCamera->Recalculate();

	for (auto& a : m_entities)
	{
		a->OnRender();
	}
}

void Application::SetCamera(Camera* camera)
{
	if (camera != nullptr)
		m_mainCamera = camera;
}

void Application::Quit()
{
	//Close SDL
	Physics::GetInstance()->Quit();
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

Application::~Application()
{
}

Application* Application::GetInstance()
{
	if (m_application == nullptr)
	{
		m_application = new Application();
	}
	return m_application;
}

void Application::Run()
{
	Init();
	Loop();
	Quit();
}


