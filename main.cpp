/*
**
**
**
**
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int windowWidth = 1600;
int windowHeight = 900;

void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
  windowWidth = width;
  windowHeight = height;
  /* update any perspective matrices used here */
}

int main(int argc, char **argv)
{
  GLFWwindow *window;

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

  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  // glfwWindowHint(GLFW_SAMPLES, 16);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Other stuff goes here

  GLuint texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  char image[1280 * 720 * 3];
  for (int i = 0; i < (sizeof image) - 3; i += 3) {
    image[i] = i;
    image[i + 1] = 127;
    image[i + 2] = 255;
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, image);




  GLuint fbo = 0;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
  glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);


  // Drawing loop here

  int j = 0;
  while (!glfwWindowShouldClose(window)) {
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < (sizeof image) - 3; i += 3) {
      image[i] = i+j;
      image[i + 1] = 127;
      image[i + 2] = 255;
    }
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1280, 720, GL_RGB, GL_UNSIGNED_BYTE, image);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1600, 720, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glfwPollEvents();
    glfwSwapBuffers(window);
    j += 10;
  }

  // End drawing loop

  // Other stuff ends here
  glfwTerminate();
  return 0;
}
