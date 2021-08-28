
#include <Shader.hpp>

#include <vector>
#include <fstream>

#include <GL/glew.h>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders
  std::string vertShaderStr = this->_readFile(vertexPath);
  std::string fragShaderStr = this->_readFile(fragmentPath);
  const char *vertShaderSrc = vertShaderStr.c_str();
  const char *fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int32_t logLength;

  // Compile vertex shader
  std::cout << "Compiling vertex shader." << std::endl;
  glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(vertShader);

  // Check vertex shader

  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
  std::cout << &vertShaderError[0] << std::endl;

  // Compile fragment shader

  std::cout << "Compiling fragment shader." << std::endl;
  glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader

  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
  std::cout << &fragShaderError[0] << std::endl;

  std::cout << "Linking program" << std::endl;
  this->_program = glCreateProgram();
  glAttachShader(this->_program, vertShader);
  glAttachShader(this->_program, fragShader);
  glLinkProgram(this->_program);

  glGetProgramiv(this->_program, GL_LINK_STATUS, &result);
  glGetProgramiv(this->_program, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> programError((logLength > 1) ? logLength : 1);
  glGetProgramInfoLog(this->_program, logLength, NULL, &programError[0]);
  std::cout << &programError[0] << std::endl;

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
}

uint32_t Shader::getProgram()
{
  return this->_program;
}

std::string Shader::_readFile(const std::string &filePath)
{
  std::string content;
  std::ifstream fileStream(filePath, std::ios:: in );

  if (!fileStream.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
    return "";
  }

  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  return content;
}