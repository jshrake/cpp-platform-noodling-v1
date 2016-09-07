/* grim_surface - v1.0.0-alpha - public domain pixel painting library
 *
 *  Usage:
 *  #include ..
 *  #include <OpenGL/gl3.h>
 *  #define GRIM_SURFACE_IMPLEMENTATION
 *  #include "grim_surface.h"
 *  ...
 *  grim_surface surface = grim_surface_create(10, 10);
 *  grim_surface_begin(&surface);
 *  grim_surface_blit(&surface, 0, 0, 10, 10, pixel_data);
 *  grim_surface_render(&surface);
 *  grim_surface_end(&surface);
 *  ...
 *
 *  TODO
 *    - Implement a ping-pong PBO and compare performance
 *
 * LICENSE
 * This software is dual-licensed to the public domain and under the following
 * license: you are granted a perpetual, irrevocable license to copy, modify,
 * publish, and distribute this file as you see fit.
 */
#ifndef GRIM_SURFACE_INCLUDE_H_
#define GRIM_SURFACE_INCLUDE_H_

#ifdef GRIM_SURFACE_STATIC
#define GRIMDEF static
#else
#define GRIMDEF extern
#endif

typedef struct grim_surface {
  unsigned int program;
  unsigned int texture;
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
  // texture parameters
  int internal_format;
  int format;
  int type;
} grim_surface;

GRIMDEF grim_surface grim_surface_create(int pixel_width, int pixel_height);
GRIMDEF grim_surface grim_surface_create_with_format(int pixel_width,
                                                     int pixel_height,
                                                     int internal_format,
                                                     int format, int type);
GRIMDEF void grim_surface_destroy(grim_surface *surface);
GRIMDEF void grim_surface_resize(grim_surface *surface, int pixel_width,
                                 int pixel_height);
GRIMDEF void grim_surface_begin(grim_surface *surface);
GRIMDEF void grim_surface_blit(grim_surface *surface, int x, int y, int width,
                               int height, void *pixels);
GRIMDEF void grim_surface_render(grim_surface *surface);
GRIMDEF void grim_surface_end(grim_surface *surface);

#endif  // GRIM_SURFACE_INCLUDE_H_

/****************************
 *
 *      IMPLEMENTATION
 *
 ****************************
*/
#ifdef GRIM_SURFACE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

#ifndef GRIM_SURFACE_TEXTURE_LOCATION
#define GRIM_SURFACE_TEXTURE_LOCATION 0
#endif

#define GRIM_SURFACE_VERTEX_POSITION_LOCATION 0
#define GRIM_SURFACE_VERTEX_TEX_COORD_LOCATION 1

static char const *grim__surface_vertex_shader =
    "#version 330\n"
    "layout(location = 0) in vec2 position;"
    "layout(location = 1) in vec2 tex_coord;"
    "out vec2 frag_tex_coord;"
    "void main()"
    "{"
    "    frag_tex_coord = tex_coord;"
    "    gl_Position = vec4(position, 0.0, 1.0);"
    "}";

static char const *grim__surface_fragment_shader =
    "#version 330\n"
    "in vec2 frag_tex_coord;"
    "out vec4 out_color;"
    "uniform sampler2D pixels;"
    "void main() {"
    " out_color = texture(pixels, frag_tex_coord);"
    "}";

grim_surface grim_surface_create(int pixel_width, int pixel_height) {
  return grim_surface_create_with_format(pixel_width, pixel_height, GL_RGB,
                                         GL_RGB, GL_FLOAT);
}

grim_surface grim_surface_create_with_format(int pixel_width, int pixel_height,
                                             int internal_format, int format,
                                             int type) {
  grim_surface surface;
  surface.internal_format = internal_format;
  surface.format = format;
  surface.type = type;
  // vertex shader
  GLuint const vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &grim__surface_vertex_shader, NULL);
  glCompileShader(vs);
  // fragment shder
  GLuint const fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &grim__surface_fragment_shader, NULL);
  glCompileShader(fs);
  // program
  {
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    surface.program = program;
  }
  glDeleteShader(vs);
  glDeleteShader(fs);

  GLuint const texture_uniform_location =
      glGetUniformLocation(surface.program, "pixels");
  glUseProgram(surface.program);
  glUniform1i(texture_uniform_location, GRIM_SURFACE_TEXTURE_LOCATION);
  glUseProgram(0);

  glGenVertexArrays(1, &surface.vao);
  glBindVertexArray(surface.vao);

  // Populate the vertex array buffer
  glGenBuffers(1, &surface.vbo);
  GLfloat const vertices[] = {
      //  Position      Texcoords
      -1.0f, 1.0f,  0.0f, 0.0f,  // Top-left
      1.0f,  1.0f,  1.0f, 0.0f,  // Top-right
      1.0f,  -1.0f, 1.0f, 1.0f,  // Bottom-right
      -1.0f, -1.0f, 0.0f, 1.0f   // Bottom-left
  };
  glBindBuffer(GL_ARRAY_BUFFER, surface.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Populate the element array buffer
  glGenBuffers(1, &surface.ebo);
  GLbyte const elements[] = {0, 1, 2, 2, 3, 0};
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surface.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
               GL_STATIC_DRAW);

  // Specify the layout of the vertex array buffer
  glEnableVertexAttribArray(GRIM_SURFACE_VERTEX_POSITION_LOCATION);
  glVertexAttribPointer(GRIM_SURFACE_VERTEX_POSITION_LOCATION, 2, GL_FLOAT,
                        GL_FALSE, 4 * sizeof(float), 0);
  glEnableVertexAttribArray(GRIM_SURFACE_VERTEX_TEX_COORD_LOCATION);
  glVertexAttribPointer(GRIM_SURFACE_VERTEX_TEX_COORD_LOCATION, 2, GL_FLOAT,
                        GL_FALSE, 4 * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // texture initialization
  glGenTextures(1, &surface.texture);
  glActiveTexture(GL_TEXTURE0 + GRIM_SURFACE_TEXTURE_LOCATION);
  glBindTexture(GL_TEXTURE_2D, surface.texture);
  grim_surface_resize(&surface, pixel_width, pixel_height);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);
  return surface;
}

void grim_surface_resize(grim_surface *surface, int pixel_width,
                         int pixel_height) {
  glTexImage2D(GL_TEXTURE_2D, 0, surface->internal_format, pixel_width,
               pixel_height, 0, surface->format, surface->type, 0);
}

GRIMDEF void grim_surface_blit(grim_surface *surface, int x, int y, int width,
                               int height, void *pixels) {
  glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, surface->format,
                  surface->type, pixels);
}

void grim_surface_begin(grim_surface *surface) {
  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glUseProgram(surface->program);
  glBindVertexArray(surface->vao);
  glActiveTexture(GL_TEXTURE0 + GRIM_SURFACE_TEXTURE_LOCATION);
  glBindTexture(GL_TEXTURE_2D, surface->texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void grim_surface_render(grim_surface *) {
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void grim_surface_end(grim_surface *) {
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(0);
  glUseProgram(0);
  glEnable(GL_BLEND);
}

void grim_surface_destroy(grim_surface *surface) {
  glDeleteProgram(surface->program);
  glDeleteTextures(1, &surface->texture);
  glDeleteVertexArrays(1, &surface->vao);
  glDeleteBuffers(1, &surface->vbo);
  glDeleteBuffers(1, &surface->ebo);
  surface->program = 0;
  surface->texture = 0;
  surface->vao = 0;
  surface->vbo = 0;
  surface->ebo = 0;
}

#endif  // #ifdef GRIM_SURFACE_IMPLEMENTATION
