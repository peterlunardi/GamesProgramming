#include "pch.h"
#include "Log.h"

void Log::Debug(const std::string& msg, const char* file, int line)
{
	std::cout << "LOG DEBUG(" << file << ", " << line << "): " << msg <<
		std::endl;
}
bool Log::CheckGLError(const char* file, int line)
{
	GLenum err;
	bool errorFound = false;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "GL ERROR(" << file << ", " << line << "): " <<
			glewGetErrorString(err) << std::endl;
		errorFound = true;
	}
	return errorFound;
}
