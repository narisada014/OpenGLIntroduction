#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
  if (glfwInit() == GL_FALSE)
  {
    std::cerr << "Cant initialize GLFW" << std::endl;
    return 1;
  } else {
    std::cout << "ok!";
  }
}