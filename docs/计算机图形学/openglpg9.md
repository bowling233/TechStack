# OpenGL Programming Guide: The Official Guide to Learning OpenGL, Version 4.5 with SPIR-V

## 附录 A：第三方支持库

!!! quote

    - [What are GLAD, GLFW and OpenGL?. What is OpenGL? - Medium](https://matt-pinch.medium.com/what-are-glad-glfw-and-opengl-569136024c87)

简单来说，GLWF 负责管理窗口和处理输入，OpenGL 负责绘制图形。

## 附录 B：OpenGL ES 与 WebGL

- 在大多数系统中 OpenGL ES 命名为 EGL。

## 第一章：OpenGL 简介

- OpenGL 是什么
    - 与硬件、操作系统和窗口系统独立，也不提供这些服务。
    - 不提供三维模型描述、读取图片等功能，需要自己使用点、线、面等基本图元描述。
    - 实现为 C/S 架构。
- 基本概念
    - 着色器：为 GPU 编译的小程序。
    - OpenGL 有六个着色器阶段，顶点（vertex）和片段（fragment）着色器是最常见的。
    - 像素存储在 framebuffer 中，这是由图形硬件管理的内存区域，用于给显示器显示。
- 基本程序框架：
    - `init()`：准备数据
        - 顶点信息
        - shader plumbing
    - `display()`：执行渲染
        - 使用 `glClearBuffer()` 清空 framebuffer
        - 绘制图形
        - 交换缓冲区
    - `main()`：主程序
        - 初始化
        - 创建窗口
        - 进入主循环
- OpenGL 语法
    - 所有 OpenGL 函数以 `gl` 开头，后接驼峰命名。如 `glBindBuffer()`。
    - 常量以 `GL_` 开头。如 `GL_COLOR_BUFFER_BIT`。
    - 为了可移植性，OpenGL 为函数定义各种数据类型，以 `GL` 开头。如 `GLint`、`GLfloat`。

        ![table_1.1](openglpg9.assets/table_1.1.png)

    - 因为 OpenGL 是 C 库，没有重载，所以函数名后缀表示参数类型。如 `glUniform1f()`、`glUniform3fv()`。

- OpenGL 渲染管线：

    ![figure_1.2](openglpg9.assets/figure_1.2.png)

    - 顶点和片段着色器必须被包含。
    - 传送给 OpenGL 的数据应当存放在 **buffer object** 中，这是 OpenGL 管理的一块内存。常用 `glNamedBufferStorage()` 指定缓冲区大小和数据。
    - 调用 `glDrawArrays()` 等命令意味着将顶点数据传送给 OpenGL。
    - 绘制命令的每个顶点都会执行**顶点着色器**，有可能会使用变换矩阵计算该顶点在屏幕上的位置等。
    - **曲面细分着色器（tessellation）**使用**面片（patch）**来描述对象，作用是细分、增加图元数量以提供更好的模型。
    - 几何着色器对几何图元进行处理。
    - 图元装配（primitive assembly）
    - 裁剪（clipping）自动进行，视口（viewport）
    - 光栅化（rasterizer）生成片元（fragment）。它确定屏幕的位置被哪个几何图元覆盖，结合输入的顶点数据，为片元着色器中的变量进行**线性插值**。这一阶段的实现与平台有关（platform-dependent）。
    - 片元着色器修改颜色和**深度**信息，执行**纹理映射**，丢弃（discard）不可见的片元。
    - 逐片元操作：使用深度检测（z-buffering）和模板测试（stencil testing）决定片元的**可见性**。
    - 如果开启了混合（blending），则与当前片元的颜色叠加写入 framebuffer。
    - 总体理解：顶点着色器负责图元在屏幕的哪个位置，片元着色器负责颜色。
- 解剖程序：
    - 应用的每个线程都有一个**当前上下文**，OpenGL 指令发送到当前上下文。应用可以有多个上下文和多个窗口，`glfwCreateWindow()` 将上下文和窗口关联起来。
    - `glCreate*()` 分配一些**对象名**。对象名有点像指针，使用 `glBind*()` 将对象名绑定到上下文，使它成为**当前对象**，后续的操作都是对当前对象的。一般有两种情况要做绑定操作：创建并初始化对象（`init()` 中），使用对象（`display()` 中）。
    - buffer 有不同地方可以存储，称为**绑定目标（binding target）**。如 `GL_ARRAY_BUFFER`、`GL_ELEMENT_ARRAY_BUFFER`。
    - `glNamedBufferStorage()` 为 buffer 分配内存，并将数据复制到 buffer 中。
- GLSL
    - 指定版本。
    - 分配着色器变量，这是它与外界通信的方式。布局限定符（layout qualifier）提供变量的元数据，其中有些与不同着色器阶段有关。
    - `gl_` 开头的内建变量。
- 连接管道
    - `glVertextAttribPointer()` 将顶点着色器的 `in` 变量连接到顶点属性数组（vertex-attribute array）。

## 第二章：着色器基础

## 在本书中学习到的 API

### OpenGL

```c
// glCreate*, glBind*, glDelete*, glIs*
void glCreateVertexArrays(GLsizei n, GLuint *arrays);
void glBindVertexArray(GLuint array);
void glDeleteVertexArrays(GLsizei n, const GLuint *arrays);
GLboolean glIsVertexArray(GLuint array);

void glCreateBuffers(GLsizei n, GLuint *buffers);
void glBindBuffer(GLenum target, GLuint buffer);
void glDeleteBuffers(GLsizei n, const GLuint *buffers);
GLboolean glIsBuffer(GLuint buffer);
// load data
void glNamedBufferStorage(GLuint buffer, GLsizeiptr size,
    const void *data, GLbitfield flags);
// Vertex Attribute Array (apply to bounded VAO)
void glVertexAttribPointer(GLuint index, GLint size,
    GLenum type, GLboolean normalized, GLsizei stride,
    const GLvoid *pointer);
void glEnableVertexAttribArray(GLuint index);
void glDisableVertexAttribArray(GLuint index);
// direct stats access
glEnableVertexArrayAttrib
glVertexArrayAttribFormat
glVertexArrayVertexBuffer

// rendering
void glClearBufferfv(GLenum buffer, GLint drawbuffer,
    const GLfloat *value);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);

// Operations
void glEnable(GLenum capability);
void glDisable(GLenum capability);
GLboolean glIsEnabled(GLenum capability);
```

### GLSL

```glsl
#version 450 core
layout(location = 0) in vec4 vPosition;
```

### GLFW

```c
void glfwInit(void);
GLFWwindow* glfwCreateWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
void glfwMakeContextCurrent(GLFWwindow *window);
bool glfwWindowShouldClose(GLFWwindow *window);
void glfwSwapBuffers(GLFWwindow *window);
void glfwPollEvents(void);
void glfwDestroyWindow(GLFWwindow *window);
void glfwTerminate(void);
```

### GL3W

```c
int gl3wInit(void);
```
