#pragma once
#include "Entity.h"
#include "Light.h"

#define WINDOW_W Application::GetInstance()->GetWindowWidth()
#define WINDOW_H Application::GetInstance()->GetWindowHeight()

enum AppState
{
	INITILISING, RUNNING, QUITTING
};

class Camera; //forward declaration

class Application
{
private:
	//private variables
	static Application* m_application;
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	AppState m_appState = AppState::INITILISING;
	float m_worldDeltaTime = 0.f;
	//float lastX;
	//float lastY;
	//bool firstMouse = true;
	bool boom = false;

	std::vector<Entity*> m_entities;
	
	Camera* m_mainCamera = nullptr;

	int MAX_LIGHTS = 4;
	std::vector<Entity*> m_lights;
	std::vector<Entity*> m_boxes;

	//private functions
	Application();
	void Init();
	void OpenGlInit();
	void GameInit();
	void MapInit();
	void WallInit(float xPos, float zPos, float xScale, float zScale);
	void CreateLight(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation);
	void Loop();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void ProcessInput(float deltaTime);

public:
	//public functions
	~Application();
	static Application* GetInstance();
	void Run();

	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }

	inline Camera* GetCamera() { return m_mainCamera; }
	void SetCamera(Camera* camera);
	void LoadLights(std::vector<Entity*> lights);
};

