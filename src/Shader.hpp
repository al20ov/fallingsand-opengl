#include <iostream>

class Shader {
  public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);

  uint32_t getProgram();

  private:
  uint32_t _program;
  std::string _readFile(const std::string &filePath);
};