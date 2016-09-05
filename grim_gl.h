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

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#elif
#error "Platform not supported"
#endif

GLuint grim_gl_vertex_shader_create(char const *src);
GLuint grim_gl_fragment_shader_create(char const *src);
void grim_gl_shader_delete(GLuint shader);
GLuint grim_gl_program_create(GLuint vert, GLuint frag);
void grim_gl_program_delete(GLuint program);

#endif  // GRIM_INCLUDE_GL_H

// =============================================================================

#ifdef GRIM_GL_IMPLEMENTATION

#include <stdio.h>

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

void grim_gl_shader_delete(GLuint shader) { glDeleteShader(shader); }

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

void grim_gl_program_delete(GLuint program) { glDeleteProgram(program); }

#endif  // GRIM_GL_IMPLEMENTATION
