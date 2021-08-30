#include <iostream>
#include <array>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Map.hpp>
#include <Shader.hpp>

uint32_t windowWidth = 1600;
uint32_t windowHeight = 900;

double mouseX, mouseY;

void glfw_window_size_callback(GLFWwindow * window, int width, int height) {
  windowWidth = width;
  windowHeight = height;
}

static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
  mouseX = xpos;
  mouseY = ypos;
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


int main(int argc, char **argv) {
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW3, exiting" << std::endl;
    return 1;
  }
  window = glfwCreateWindow(windowWidth, windowHeight, "Falling sand", NULL, NULL);
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

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // this enables gamma correction
  glEnable(GL_FRAMEBUFFER_SRGB);



  float points[] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 1.0f
  };

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // eighteen being the number of individual floats in the array
  glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  // three attributes referring to the three values we're passing per point
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  // texture initialization code goes here
  GLuint texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  Map map = Map();
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Map::mapWidth, Map::mapHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, map.getBloomMap());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Map::mapWidth, Map::mapHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, map.getMap());

  // Shader code here

  Shader mainShader("shaders/vertex.shader", "shaders/fragment.shader");
  GLuint shaderProgram = mainShader.getProgram();

  // Drawing loop here

  while (!glfwWindowShouldClose(window)) {
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    map.computePhysics();
    compute_round(window, map);


    // glBindTexture(GL_TEXTURE_2D, texture);
    // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Map::mapWidth, Map::mapHeight, GL_RGBA, GL_UNSIGNED_BYTE, map.getBloomMap());
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Map::mapWidth, Map::mapHeight, GL_RGB, GL_UNSIGNED_BYTE, map.getMap());

    // how many triangles we are drawing
    glDrawArrays(GL_TRIANGLES, 0, sizeof points / 4);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}