#pragma once
enum AppState
{
	INITILISING, RUNNING, QUITTING
};

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

	//private functions
	Application();
	void Init();
	void OpenGlInit();
	void Loop();
	void Quit();

public:
	//public functions
	~Application();
	static Application* GetInstance();
	void Run();
};

