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
#include "SphereShape.h"
#include "RigidBody.h"
#include "Light.h"
#include "ConeShape.h"
#include "CylinderShape.h"

Application* Application::m_application = nullptr;
float counter = 0;
float counter2 = 0;
float counter3 = 0;

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

void Application::WallInit(float xPos, float zPos, float xScale, float zScale)
{

	Entity* a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("cube.obj"),
			Resources::GetInstance()->GetShader("multiLight"),
			Resources::GetInstance()->GetTexture("floorTile.jpg"))
	);
	MeshRenderer* m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(xPos, -5.f, zPos));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(xScale, 100.f, zScale)));
	a->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	a->GetTransform()->SetScale(glm::vec3(xScale, 100.f, zScale));
}

void Application::MapInit()
{
	//The ground!
	Entity* a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("cube.obj"),
			Resources::GetInstance()->GetShader("multiLight"),
			Resources::GetInstance()->GetTexture("floorTile.jpg"))
	);
	MeshRenderer* m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(0, -5.f, 0.f));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)));
	a->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	a->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 100.f));

	//The ground!
	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("cube.obj"),
			Resources::GetInstance()->GetShader("multiLight"),
			Resources::GetInstance()->GetTexture("floorTile.jpg"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(0, -10.f, 200.f));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)));
	a->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	a->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 100.f));

	WallInit(-100.f, 0.f, 1.f, 100.f);
	WallInit(100.f, 0.f, 1.f, 100.f);
	WallInit(0.f, 300.f, 100.f, 1.f);
	WallInit(0.f, -100.f, 100.f, 1.f);
	WallInit(-100.f, 200.f, 1.f, 100.f);
	WallInit(100.f, 200.f, 1.f, 100.f);
}

void Application::CreateLight(glm::vec3 position, glm::vec3 colour)
{
	Entity* a = new Entity();
	m_entities.push_back(a);
	m_lights.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("cube.obj"),
			Resources::GetInstance()->GetShader("source"),
			Resources::GetInstance()->GetTexture("penguinTex.png"))
	);
	a->GetTransform()->SetPosition(position);
	a->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	a->AddComponent(new Light(a->GetTransform()->GetPosition(), colour));
}

void Application::GameInit()
{
	//loading all resources
	Resources::GetInstance()->AddModel("cube.obj");
	Resources::GetInstance()->AddModel("penguin.obj");
	Resources::GetInstance()->AddModel("turkey.obj");
	Resources::GetInstance()->AddModel("cone.obj");
	Resources::GetInstance()->AddModel("ball.obj");
	Resources::GetInstance()->AddModel("barrel.obj");
	Resources::GetInstance()->AddModel("plane.obj");
	Resources::GetInstance()->AddTexture("barrel.jpg");
	Resources::GetInstance()->AddTexture("ball.jpg");
	Resources::GetInstance()->AddTexture("penguinTex.png");
	Resources::GetInstance()->AddTexture("turkey.jpg");
	Resources::GetInstance()->AddTexture("Wood.jpg");
	Resources::GetInstance()->AddTexture("floorTile.jpg");
	Resources::GetInstance()->AddTexture("cone.jpg");
	Resources::GetInstance()->AddShader(new ShaderProgram(ASSET_PATH + "simple_VERT.glsl", ASSET_PATH + "simple_FRAG.glsl"), "simple");
	Resources::GetInstance()->AddShader(new ShaderProgram(ASSET_PATH + "lighting_VERT.glsl", ASSET_PATH + "lighting_FRAG.glsl"), "lighting");
	Resources::GetInstance()->AddShader(new ShaderProgram(ASSET_PATH + "multipleLight_VERT.glsl", ASSET_PATH + "multipleLight_FRAG.glsl"), "multiLight");
	Resources::GetInstance()->AddShader(new ShaderProgram(ASSET_PATH + "lightSource_VERT.glsl", ASSET_PATH + "lightSource_FRAG.glsl"), "source");
	Resources::GetInstance()->AddShader(new ShaderProgram(ASSET_PATH + "water_VERT.glsl", ASSET_PATH + "water_FRAG.glsl", ASSET_PATH + "water_GEOM.glsl"), "water");

	MapInit();

	//turkey!!------------------------------------------------
	Entity* a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("turkey.obj"),
			Resources::GetInstance()->GetShader("multiLight"),
			Resources::GetInstance()->GetTexture("turkey.jpg"))
	);
	MeshRenderer* m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(-50, 5, 5));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new SphereShape(5.f), 30.0f);
	a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	//SPAWN CUBES!!!------------------------------
	for (int x = 0; x < 4; x++) {
		for (int z = 0; z < 4; z++) {
			for (int i = 0; i < 4; i++)
			{
				Entity* a = new Entity();
				m_entities.push_back(a);
				m_boxes.push_back(a);
				a->AddComponent(
					new MeshRenderer(
						Resources::GetInstance()->GetModel("cube.obj"),
						Resources::GetInstance()->GetShader("multiLight"),
						Resources::GetInstance()->GetTexture("Wood.jpg"))
				);
				a->GetTransform()->SetPosition(glm::vec3(50 - 2*x, 1 * i, -40 + 2*z));
				a->AddComponent<RigidBody>();
				a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 1.f)), 0.2f);
				a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
			}
		}
	}

	//penguin!!-----------------------------------------
	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("penguin.obj"),
			Resources::GetInstance()->GetShader("lighting"),
			Resources::GetInstance()->GetTexture("penguinTex.png"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(10, 5, -10));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 0.5f, 0.5f)));
	a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("ball.obj"),
			Resources::GetInstance()->GetShader("multiLight"),
			Resources::GetInstance()->GetTexture("ball.jpg"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(-40, 5, 50));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new SphereShape(3.5f));
	a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("barrel.obj"),
			Resources::GetInstance()->GetShader("multiLight"),
			Resources::GetInstance()->GetTexture("barrel.jpg"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(80, 5, 50));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new CylinderShape(glm::vec3(2.f, 3.f, 0.8f)), 0.2f);
	a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	a = new Entity();
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("plane.obj"),
			Resources::GetInstance()->GetShader("water"),
			Resources::GetInstance()->GetTexture("barrel.jpg"))
	);
	m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(0, -5, 200));

	//CONES---------------------------------------------
	for (int x = 1; x < 5; x++) {
		for (int y = 1; y < 2 * x; y++) {
			a = new Entity();
			m_entities.push_back(a);
			a->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("cone.obj"),
					Resources::GetInstance()->GetShader("multiLight"),
					Resources::GetInstance()->GetTexture("cone.jpg"))
			);
			m = a->GetComponent<MeshRenderer>();
			a->GetTransform()->SetPosition(glm::vec3(5 * x, 1, 5*y));
			a->AddComponent<RigidBody>();
			a->GetComponent<RigidBody>()->Init(new ConeShape(4.f, 11.f), 0.1f);
		}
	}

	//LIGHT ENTITIES---------------------
	CreateLight(glm::vec3(20.0f, 20.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	CreateLight(glm::vec3(-10.0f, 1.0f, -50.0f), glm::vec3(1.f, 0.0f, 0.1f));
	CreateLight(glm::vec3(-10.0f, 1.0f, 20.0f), glm::vec3(0.1f, 0.1f, 1.f));
	CreateLight(glm::vec3(-20.0f, 1.0f, 0.0f), glm::vec3(0.1f, 1.f, 0.1f));

	a = new Entity();
	m_entities.push_back(a);
	a->GetTransform()->SetPosition(glm::vec3(-50, 25, -5));
	CameraComp* cc = new CameraComp();
	a->AddComponent(cc);
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(5.f, 5.f, 5.f)), 0.f);
	cc->Start();


}

void Application::LoadLights(std::vector<Entity*> lights)
{
	Resources::GetInstance()->GetShader("multiLight")->Use();
	Resources::GetInstance()->GetShader("multiLight")->setVec3("viewPos", m_mainCamera->GetParentTransform()->GetPosition());

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		std::string colourStr = std::string("lightColour[") + std::to_string(i) + std::string("]");
		std::string posStr = std::string("lightPos[") + std::to_string(i) + std::string("]");

		if (i < m_lights.size())
		{
			Resources::GetInstance()->GetShader("multiLight")->setVec3(colourStr, lights[i]->GetComponent<Light>()->GetColour());
			Resources::GetInstance()->GetShader("multiLight")->setVec3(posStr, lights[i]->GetTransform()->GetPosition());
		}
		else {
			Resources::GetInstance()->GetShader("multiLight")->setVec3(colourStr, glm::vec3(0, 0, 0));
			Resources::GetInstance()->GetShader("multiLight")->setVec3(posStr, glm::vec3(0, 0, 0));
		}
	}
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

		Resources::GetInstance()->GetShader("lighting")->Use();
		Resources::GetInstance()->GetShader("lighting")->setVec3("lightColour", m_lights[0]->GetComponent<Light>()->GetColour());
		Resources::GetInstance()->GetShader("lighting")->setVec3("lightPos", m_lights[0]->GetTransform()->GetPosition());
		Resources::GetInstance()->GetShader("lighting")->setVec3("viewPos", m_mainCamera->GetParentTransform()->GetPosition());

		Resources::GetInstance()->GetShader("water")->Use();
		Resources::GetInstance()->GetShader("water")->setVec3("cameraPosition", m_mainCamera->GetParentTransform()->GetPosition());
		Resources::GetInstance()->GetShader("water")->setFloat("time", counter * 0.1f);

		float X = 0 + cosf(counter) * 30;
		float Z = 0 + sinf(counter) * 30;
		m_lights[1]->GetTransform()->SetPosition(glm::vec3(X, 10, Z));

		X = 10 + cosf(counter3) * 50;
		Z = -10 + sinf(counter3) * 50;
		m_lights[2]->GetTransform()->SetPosition(glm::vec3(X, 10, Z));

		X = 20 + cosf(counter2) * 70;
		Z = -20 + sinf(counter2) * 70;
		m_lights[3]->GetTransform()->SetPosition(glm::vec3(X, 10, Z));

		LoadLights(m_lights);
		ProcessInput(deltaTime);
		counter += deltaTime * 0.6f;
		counter2 += deltaTime * 0.05f;
		counter3 += deltaTime * 0.3f;
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
	if (keystates[SDL_SCANCODE_UP])
	{
		m_entities.at(8)->GetComponent<RigidBody>()->ApplyForce(30);
	}
	if (keystates[SDL_SCANCODE_DOWN])
	{
		m_entities.at(8)->GetComponent<RigidBody>()->ApplyForce(-30);
	}
	if (keystates[SDL_SCANCODE_LEFT])
	{
		m_entities.at(8)->GetComponent<RigidBody>()->ApplyTorque(-30);
	}
	if (keystates[SDL_SCANCODE_RIGHT])
	{
		m_entities.at(8)->GetComponent<RigidBody>()->ApplyTorque(30);
	}
	if (keystates[SDL_SCANCODE_SPACE])
	{
		if (boom == false)
		{
			glm::vec3 explosionPoint = m_boxes[m_boxes.size() / 2]->GetTransform()->GetPosition();
			for (int i = 0; i < m_boxes.size(); i++)
			{
				glm::vec3 forceVector = glm::normalize(m_boxes[i]->GetTransform()->GetPosition() - explosionPoint);
				m_boxes[i]->GetComponent<RigidBody>()->ApplyForce(btVector3(forceVector.x, forceVector.y, forceVector.z) * 5);
			}
			boom = true;
		}

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
	glClearColor(0.f, 0.15f, 0.45f, 1.f);
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


