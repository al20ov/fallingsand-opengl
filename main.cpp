#include <iostream>
#include <array>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Map.hpp>

int windowWidth = 1600;
int windowHeight = 900;

double mouseX, mouseY;

void glfw_window_size_callback(GLFWwindow * window, int width, int height) {
  windowWidth = width;
  windowHeight = height;
  /* update any perspective matrices used here */
}

static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
  mouseX = xpos;
  mouseY = ypos;
}

std::string readFile(const char * filePath) {
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

GLuint LoadShader(const char * vertex_path,
  const char * fragment_path) {
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders

  std::string vertShaderStr = readFile(vertex_path);
  std::string fragShaderStr = readFile(fragment_path);
  const char * vertShaderSrc = vertShaderStr.c_str();
  const char * fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int logLength;

  // Compile vertex shader

  std::cout << "Compiling vertex shader." << std::endl;
  glShaderSource(vertShader, 1, & vertShaderSrc, NULL);
  glCompileShader(vertShader);

  // Check vertex shader

  glGetShaderiv(vertShader, GL_COMPILE_STATUS, & result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, & logLength);
  std::vector < GLchar > vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, & vertShaderError[0]);
  std::cout << & vertShaderError[0] << std::endl;

  // Compile fragment shader

  std::cout << "Compiling fragment shader." << std::endl;
  glShaderSource(fragShader, 1, & fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader

  glGetShaderiv(fragShader, GL_COMPILE_STATUS, & result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, & logLength);
  std::vector < GLchar > fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, & fragShaderError[0]);
  std::cout << & fragShaderError[0] << std::endl;

  std::cout << "Linking program" << std::endl;
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, & result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, & logLength);
  std::vector < char > programError((logLength > 1) ? logLength : 1);
  glGetProgramInfoLog(program, logLength, NULL, & programError[0]);
  std::cout << & programError[0] << std::endl;

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);

  return program;
}





void compute_round(GLFWwindow *window, Map &map)
{
  int lClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  int rClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

  if (glfwGetWindowAttrib(window, GLFW_HOVERED)) {
    if (lClick == GLFW_PRESS) {
      map.paintSmallBrush(windowWidth, windowHeight, mouseX, mouseY, SAND);
    } else if (rClick == GLFW_PRESS) {
      map.paintSmallBrush(windowWidth, windowHeight, mouseX, mouseY, STONE);
    }
  }
}


int main(int argc, char ** argv) {
  GLFWwindow * window;

  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW3, exiting" << std::endl;
    return 1;
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  window = glfwCreateWindow(windowWidth, windowHeight, "coucouuu", NULL, NULL);
  if (!window) {
    std::cerr << "Could not open window with GLFW3" << std::endl;
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, glfw_window_size_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte * renderer = glGetString(GL_RENDERER);
  const GLubyte * version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Other stuff goes here

  float points[] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 1.0f
  };

  GLuint vbo = 0;
  glGenBuffers(1, & vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // eighteen being the number of individual floats in the array
  glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, & vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  // three attributes referring to the three values we're passing per point
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  // texture initialization code goes here
  GLuint texture;
  glGenTextures(1, & texture);

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  Map map = Map();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Map::mapWidth, Map::mapHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, map.getMap());
  // Shader code here

  GLuint shader_program = LoadShader("shaders/vertex.shader", "shaders/fragment.shader");

  // Drawing loop here

  while (!glfwWindowShouldClose(window)) {
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);
    glBindVertexArray(vao);

    map.computePhysics();
    compute_round(window, map);


    // glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Map::mapWidth, Map::mapHeight, GL_RGB, GL_UNSIGNED_BYTE, map.getMap());

    // how many triangles we are drawing
    glDrawArrays(GL_TRIANGLES, 0, sizeof points / 4);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // End drawing loop

  // Other stuff ends here
  glfwTerminate();
  return 0;
}