#include "Debugger.h"

static void APIENTRY DebugCallbackAMD(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam);
static void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);
static std::string FormatDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, const char* msg);

Debugger::Debugger()
{
}

void Debugger::initDebugger() {
#if _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Query the OpenGL function to register your callback function.
	PFNGLDEBUGMESSAGECALLBACKPROC _glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)wglGetProcAddress("glDebugMessageCallback");
	PFNGLDEBUGMESSAGECALLBACKARBPROC _glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)wglGetProcAddress("glDebugMessageCallbackARB");
	PFNGLDEBUGMESSAGECALLBACKAMDPROC _glDebugMessageCallbackAMD = (PFNGLDEBUGMESSAGECALLBACKAMDPROC)wglGetProcAddress("glDebugMessageCallbackAMD");

	// Register your callback function.
	if (_glDebugMessageCallback != NULL) {
		_glDebugMessageCallback(DebugCallback, NULL);
	}
	else if (_glDebugMessageCallbackARB != NULL) {
		_glDebugMessageCallbackARB(DebugCallback, NULL);
	}
	else if (_glDebugMessageCallbackAMD != NULL) {
		_glDebugMessageCallbackAMD(DebugCallbackAMD, NULL);
	}

	// Enable synchronous callback. This ensures that your callback function is called
	// right after an error has occurred. This capability is not defined in the AMD
	// version.
	if ((_glDebugMessageCallback != NULL) || (_glDebugMessageCallbackARB != NULL)) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}
#endif
}

void APIENTRY Debugger::DebugCallbackAMD(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam) {
	std::string error = FormatDebugOutput(category, category, id, severity, message);
	std::cout << error << std::endl;
}

void APIENTRY Debugger::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam) {
	std::string error = FormatDebugOutput(source, type, id, severity, message);
	std::cout << error << std::endl;
}

std::string Debugger::FormatDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, const char* msg) {
	std::stringstream stringStream;
	std::string sourceString;
	std::string typeString;
	std::string severityString;

	// The AMD variant of this extension provides a less detailed classification of the error,
	// which is why some arguments might be "Unknown".
	switch (source) {
	case GL_DEBUG_CATEGORY_API_ERROR_AMD:
	case GL_DEBUG_SOURCE_API: {
								  sourceString = "API";
								  break;
	}
	case GL_DEBUG_CATEGORY_APPLICATION_AMD:
	case GL_DEBUG_SOURCE_APPLICATION: {
										  sourceString = "Application";
										  break;
	}
	case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: {
											sourceString = "Window System";
											break;
	}
	case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
	case GL_DEBUG_SOURCE_SHADER_COMPILER: {
											  sourceString = "Shader Compiler";
											  break;
	}
	case GL_DEBUG_SOURCE_THIRD_PARTY: {
										  sourceString = "Third Party";
										  break;
	}
	case GL_DEBUG_CATEGORY_OTHER_AMD:
	case GL_DEBUG_SOURCE_OTHER: {
									sourceString = "Other";
									break;
	}
	default: {
				 sourceString = "Unknown";
				 break;
	}
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR: {
								  typeString = "Error";
								  break;
	}
	case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: {
												typeString = "Deprecated Behavior";
												break;
	}
	case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: {
											   typeString = "Undefined Behavior";
											   break;
	}
	case GL_DEBUG_TYPE_PORTABILITY_ARB: {
											typeString = "Portability";
											break;
	}
	case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
	case GL_DEBUG_TYPE_PERFORMANCE: {
										typeString = "Performance";
										break;
	}
	case GL_DEBUG_CATEGORY_OTHER_AMD:
	case GL_DEBUG_TYPE_OTHER: {
								  typeString = "Other";
								  break;
	}
	default: {
				 typeString = "Unknown";
				 break;
	}
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: {
									 severityString = "High";
									 break;
	}
	case GL_DEBUG_SEVERITY_MEDIUM: {
									   severityString = "Medium";
									   break;
	}
	case GL_DEBUG_SEVERITY_LOW: {
									severityString = "Low";
									break;
	}
	default: {
				 severityString = "Unknown";
				 break;
	}
	}

	stringStream << "OpenGL Error: " << msg;
	stringStream << " [Source = " << sourceString;
	stringStream << ", Type = " << typeString;
	stringStream << ", Severity = " << severityString;
	stringStream << ", ID = " << id << "]";

	return stringStream.str();
}

Debugger::~Debugger()
{
}
