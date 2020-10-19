#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint createProgram(const char *vsrc, const char *fsrc)
{
  const GLuint program(glCreateProgram());

  if (vsrc != NULL)
  {
    // 頂点シェーダーの準備
    const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
    glShaderSource(vobj, 1, &vsrc, NULL);
    glCompileShader(vobj);
    // 頂点シェーダーのオブジェクトをプログラムオブジェクトに組み込む
    glAttachShader(program, vobj);
    glDeleteShader(vobj);
  }

  if (fsrc != NULL)
  {
    // 頂点シェーダーの準備
    const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(fobj, 1, &fsrc, NULL);
    glCompileShader(fobj);
    // 頂点シェーダーのオブジェクトをプログラムオブジェクトに組み込む
    glAttachShader(program, fobj);
    glDeleteShader(fobj);
  }

  glBindAttribLocation(program, 0, "position");
  glBindFragDataLocation(program, 0, "fragment");
  glLinkProgram(program);

  return program;
}

int main()
{
  if (glfwInit() == GL_FALSE)
  {
    std::cerr << "Cant initialize GLFW" << std::endl;
    return 1;
  }

  atexit(glfwTerminate);

  //Setting window properties
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow *const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));
  if (window == NULL) {
    std::cerr << "Cant create GLFW window." << std::endl;
    return 1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Cant initialize GLEW" << std::endl;
    return 1;
  }

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // 頂点シェーダー
  static const GLchar vsrc[] =
    "#version 150 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    " gl_Position = position;\n"
    "}\n";

  // フラグメントシェーダー
  static const GLchar fsrc[] =
    "#version 150 core\n"
    "out vec4 fragment;\n"
    "void main()\n"
    "{\n"
    " fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

  // プログラムオブジェクトを生成する
  const GLuint program(createProgram(vsrc, fsrc));

  while (glfwWindowShouldClose(window) == GL_FALSE)
  {
    glClear(GL_COLOR_BUFFER_BIT);

    // シェーダプログラムの使用始める
    glUseProgram(program);

    glfwSwapBuffers(window);
    glfwWaitEvents();
  }

  const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version as a string
  std::cout<<"Renderer: "<< renderer <<std::endl;
  std::cout<<"OpenGL version supported "<< version <<std::endl;
}