/*
    grim_gl.h - Single-header multi-platform OpenGL function loader
    ----------------------------------------------------------------------------
    LICENSE
    ----------------------------------------------------------------------------
    This software is in the public domain. Where that dedication is not
    recognized, you are granted a perpetual, irrevocable license to copy,
    distribute, and modify this file as you see fit.
*/
#ifndef GRIM_INCLUDE_GL_H
#define GRIM_INCLUDE_GL_H

/*
 * ---------------------------
 * Required includes
 * ---------------------------
 */

#include <stdint.h>
/*
 * ---------------------------
 * Types
 * ---------------------------
 */
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef char GLchar;
typedef char GLcharARB;
typedef unsigned short GLhalf;
typedef GLint GLfixed;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef struct __GLsync *GLsync;

/*
 * ---------------------------
 * Enums
 * ---------------------------
 */
#define GL_ARRAY_BUFFER 0x8892
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_COMPILE_STATUS 0x8B81
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_FALSE 0
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_FRAMEBUFFER 0x8D40
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_FUNC_ADD 0x8006
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_LINK_STATUS 0x8B82
#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C
#define GL_STATIC_DRAW 0x88E4
#define GL_STREAM_DRAW 0x88E0
#define GL_TEXTURE0 0x84C0
#define GL_VERTEX_SHADER 0x8B31

#if defined(__linux__) || defined(__APPLE__)
#define GLDECL  // Empty define
#endif          // __linux__

#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define GLDECL WINAPI
#endif

#define GRIM_GL_LIST                                                           \
  /* ret, name, params */                                                      \
  GLE(void, AttachShader, GLuint program, GLuint shader)                       \
  GLE(void, BindBuffer, GLenum target, GLuint buffer)                          \
  GLE(void, BindFramebuffer, GLenum target, GLuint framebuffer)                \
  GLE(void, BufferData, GLenum target, GLsizeiptr size, const GLvoid *data,    \
      GLenum usage)                                                            \
  GLE(void, BufferSubData, GLenum target, GLintptr offset, GLsizeiptr size,    \
      const GLvoid *data)                                                      \
  GLE(GLenum, CheckFramebufferStatus, GLenum target)                           \
  GLE(void, ClearBufferfv, GLenum buffer, GLint drawbuffer,                    \
      const GLfloat *value)                                                    \
  GLE(void, CompileShader, GLuint shader)                                      \
  GLE(GLuint, CreateProgram, void)                                             \
  GLE(GLuint, CreateShader, GLenum type)                                       \
  GLE(void, Clear, GLbitfield mask)                                            \
  GLE(void, DeleteBuffers, GLsizei n, const GLuint *buffers)                   \
  GLE(void, DeleteFramebuffers, GLsizei n, const GLuint *framebuffers)         \
  GLE(void, DeleteProgram, GLuint program)                                     \
  GLE(void, DeleteShader, GLuint shader)                                       \
  GLE(void, DetachShader, GLuint program, GLuint shader)                       \
  GLE(void, EnableVertexAttribArray, GLuint index)                             \
  GLE(void, DrawBuffers, GLsizei n, const GLenum *bufs)                        \
  GLE(void, FramebufferTexture2D, GLenum target, GLenum attachment,            \
      GLenum textarget, GLuint texture, GLint level)                           \
  GLE(void, GenBuffers, GLsizei n, GLuint *buffers)                            \
  GLE(void, GenFramebuffers, GLsizei n, GLuint *framebuffers)                  \
  GLE(GLint, GetAttribLocation, GLuint program, const GLchar *name)            \
  GLE(void, GetProgramiv, GLuint program, GLenum name, GLint *params)          \
  GLE(void, GetProgramInfoLog, GLuint program, GLsizei maxLength,              \
      GLsizei *length, GLchar *infoLog)                                        \
  GLE(void, GetShaderInfoLog, GLuint shader, GLsizei bufSize, GLsizei *length, \
      GLchar *infoLog)                                                         \
  GLE(void, GetShaderiv, GLuint shader, GLenum pname, GLint *params)           \
  GLE(GLint, GetUniformLocation, GLuint program, const GLchar *name)           \
  GLE(void, LinkProgram, GLuint program)                                       \
  GLE(void, ShaderSource, GLuint shader, GLsizei count,                        \
      const GLchar *const *string, const GLint *length)                        \
  GLE(void, Uniform1i, GLint location, GLint v0)                               \
  GLE(void, Uniform1f, GLint location, GLfloat v0)                             \
  GLE(void, Uniform2f, GLint location, GLfloat v0, GLfloat v1)                 \
  GLE(void, Uniform4f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2,     \
      GLfloat v3)                                                              \
  GLE(void, UniformMatrix4fv, GLint location, GLsizei count,                   \
      GLboolean transpose, const GLfloat *value)                               \
  GLE(void, UseProgram, GLuint program)                                        \
  GLE(void, VertexAttribPointer, GLuint index, GLint size, GLenum type,        \
      GLboolean normalized, GLsizei stride, const GLvoid *pointer)             \
/* end */

#define GLE(ret, name, ...)                   \
  typedef ret GLDECL name##proc(__VA_ARGS__); \
  extern name##proc *gl##name;
GRIM_GL_LIST
#undef GLE

bool grim_gl_init();
#ifndef GRIM_NO_HELPERS
GLuint grim_gl_vertex_shader_create(char const *src);
GLuint grim_gl_fragment_shader_create(char const *src);
GLuint grim_gl_program_create(GLuint vert, GLuint frag);
#endif

#endif  // GRIM_INCLUDE_GL_H

// =============================================================================

#ifdef GRIM_GL_IMPLEMENTATION

#include <stdio.h>  // printf warnings

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif  // __linux__

#define GLE(ret, name, ...) name##proc *gl##name;
GRIM_GL_LIST
#undef GLE

bool grim_gl_init() {
#if defined(__linux__)

  void *libGL = dlopen("libGL.so", RTLD_LAZY);
  if (!libGL) {
    printf("ERROR: libGL.so couldn't be loaded\n");
    return false;
  }

#define GLE(ret, name, ...)                                            \
  gl##name = (name##proc *)dlsym(libGL, "gl" #name);                   \
  if (!gl##name) {                                                     \
    printf("Function gl" #name " couldn't be loaded from libGL.so\n"); \
    return false;                                                      \
  }
  GRIM_GL_LIST
#undef GLE

#elif defined(_WIN32)

  HINSTANCE dll = LoadLibraryA("opengl32.dll");
  typedef PROC WINAPI wglGetProcAddressproc(LPCSTR lpszProc);
  if (!dll) {
    OutputDebugStringA("opengl32.dll not found.\n");
    return false;
  }
  wglGetProcAddressproc *wglGetProcAddress =
      (wglGetProcAddressproc *)GetProcAddress(dll, "wglGetProcAddress");

#define GLE(ret, name, ...)                                        \
  gl##name = (name##proc *)wglGetProcAddress("gl" #name);          \
  if (!gl##name) {                                                 \
    OutputDebugStringA("Function gl" #name                         \
                       " couldn't be loaded from opengl32.dll\n"); \
    return false;                                                  \
  }
  GRIM_GL_LIST
#undef GLE

#elif defined(__APPLE__)

  void *libGL = dlopen(
      "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL",
      RTLD_LAZY);
  if (!libGL) {
    printf("ERROR: OpenGL.framework couldn't be loaded\n");
    return false;
  }

#define GLE(ret, name, ...)                                                    \
  gl##name = (name##proc *)dlsym(libGL, "gl" #name);                           \
  if (!gl##name) {                                                             \
    printf("Function gl" #name " couldn't be loaded from OpenGL.frameowrk\n"); \
    return false;                                                              \
  }
  GRIM_GL_LIST
#undef GLE

#else
#error "GL loading for this platform is not implemented yet."
#endif

  return true;
}

#ifndef GRIM_NO_HELPERS
#include <stdlib.h>  //malloc and free

static GLuint grim__create_shader(GLenum type, char const *source) {
  GLuint const shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  GLint ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (ok == GL_FALSE) {
    GLint log_len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
    char *const error_log = (char *)malloc((size_t)log_len * sizeof error_log);
    glGetShaderInfoLog(shader, log_len, &log_len, error_log);
    printf("[GL] Error compiling shader: %s\n", error_log);
    free(error_log);
    glDeleteShader(shader);
    return 0;
  } else {
    return shader;
  }
}

GLuint grim_gl_vertex_shader_create(char const *src) {
  return grim__create_shader(GL_VERTEX_SHADER, src);
}

GLuint grim_gl_fragment_shader_create(char const *src) {
  return grim__create_shader(GL_FRAGMENT_SHADER, src);
}

GLuint grim_gl_program_create(GLuint vert, GLuint frag) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);
  glDetachShader(program, vert);
  glDetachShader(program, frag);
  GLint link_ok = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (link_ok == GL_FALSE) {
    GLint log_len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
    char *const error_log = (char *)malloc((size_t)log_len * sizeof error_log);
    glGetProgramInfoLog(program, log_len, &log_len, error_log);
    printf("[GL] Error linking program: %s\n", error_log);
    free(error_log);
    glDeleteProgram(program);
    return 0;
  }
  return program;
}
#endif  // !GRIM_NO_HELPERS
#endif  // GRIM_GL_IMPLEMENTATION
