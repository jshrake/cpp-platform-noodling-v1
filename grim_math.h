/* grim_math - v1.0.0-alpha - public domain GLSL-like C++ vector math library
 *
 * Do this:
 *    #define GRIM_MATH_IMPLEMENTATION
 * before you include this file in *one* C++ file to create the implementation.
 * It shoud look like:
 *  #include ..
 *  #define GRIM_MATH_IMPLEMENTATION
 *  #include "grim_math.h"
 *
 * TODO
 *  - Missing functions:
 *    - smoothstep
 *  - Tests
 *  - Inlining
 *  - SSE support
 *
 * LICENSE
 * This software is dual-licensed to the public domain and under the following
 * license: you are granted a perpetual, irrevocable license to copy, modify,
 * publish, and distribute this file as you see fit.
 */
#ifndef GRIM_MATH_INCLUDE_H_
#define GRIM_MATH_INCLUDE_H_

#ifdef GRIM_MATH_STATIC
#define GRIMDEF static
#else
#define GRIMDEF extern
#endif

union vec2 {
  struct {
    float x, y;
  };
  struct {
    float u, v;
  };
  float data[2];
};

union vec3 {
  struct {
    float x, y, z;
  };
  struct {
    float u, v, w;
  };
  struct {
    float r, g, b;
  };
  struct {
    vec2 xy;
    float _z;
  };
  struct {
    float _x;
    vec2 yz;
  };
  struct {
    vec2 uv;
    float _w;
  };
  struct {
    float _u;
    vec2 vw;
  };
  float data[3];
};

union vec4 {
  struct {
    float x, y, z, w;
  };
  struct {
    vec3 xyz;
    float _w;
  };
  struct {
    vec2 xy;
    vec2 zw;
  };
  struct {
    float _x;
    vec2 yz;
    float _w0;
  };
  struct {
    float r, g, b, a;
  };
  struct {
    vec3 rgb;
    float _a;
  };
  float data[4];
};

union mat2 {
  struct {
    float ax, ay;
    float bx, by;
  };
  struct {
    vec2 a;
    vec2 b;
  };
  float data[4];
};

union mat3 {
  struct {
    float ax, ay, az;
    float bx, by, bz;
    float cx, cy, cz;
  };
  struct {
    vec3 a;
    vec3 b;
    vec3 c;
  };
  float data[9];
};

union mat4 {
  struct {
    float ax, ay, az, aw;
    float bx, by, bz, bw;
    float cx, cy, cz, cw;
    float dx, dy, dz, dw;
  };
  struct {
    vec4 a;
    vec4 b;
    vec4 c;
    vec4 d;
  };
  float data[16];
};

// vec2
GRIMDEF vec2 v2(float x, float y);
GRIMDEF vec2 v2(float const *v);
GRIMDEF vec2 operator-(vec2 a);
GRIMDEF vec2 operator+(vec2 a, vec2 b);
GRIMDEF vec2 operator-(vec2 a, vec2 b);
GRIMDEF vec2 operator*(vec2 a, float s);
GRIMDEF vec2 operator*(float s, vec2 a);
GRIMDEF vec2 &operator+=(vec2 &a, vec2 b);
GRIMDEF vec2 &operator-=(vec2 &a, vec2 b);
GRIMDEF vec2 &operator*=(vec2 &a, float s);
// vec3
GRIMDEF vec3 v3(float x, float y, float z);
GRIMDEF vec3 v3(float const *v);
GRIMDEF vec3 v3(vec2 xy, float z);
GRIMDEF vec3 operator-(vec3 a);
GRIMDEF vec3 operator+(vec3 a, vec3 b);
GRIMDEF vec3 operator-(vec3 a, vec3 b);
GRIMDEF vec3 operator*(vec3 a, float s);
GRIMDEF vec3 operator*(float s, vec3 a);
GRIMDEF vec3 &operator+=(vec3 &a, vec3 b);
GRIMDEF vec3 &operator-=(vec3 &a, vec3 b);
GRIMDEF vec3 &operator*=(vec3 &a, float s);
// vec4
GRIMDEF vec4 v4(float x, float y, float z, float w);
GRIMDEF vec4 v4(float const *v);
GRIMDEF vec4 v4(vec2 xy, float z, float w);
GRIMDEF vec4 v4(vec3 xyz, float w);
GRIMDEF vec4 operator-(vec4 a);
GRIMDEF vec4 operator+(vec4 a, vec4 b);
GRIMDEF vec4 operator-(vec4 a, vec4 b);
GRIMDEF vec4 operator*(vec4 a, float s);
GRIMDEF vec4 operator*(float s, vec4 a);
GRIMDEF vec4 &operator+=(vec4 &a, vec4 b);
GRIMDEF vec4 &operator-=(vec4 &a, vec4 b);
GRIMDEF vec4 &operator*=(vec4 &a, float s);
// mat2
GRIMDEF mat2 m2(float ax, float ay, float bx, float by);
GRIMDEF mat2 m2(vec2 a, vec2 b);
GRIMDEF mat2 operator-(mat2 m);
GRIMDEF mat2 operator+(mat2 m, mat2 n);
GRIMDEF mat2 operator-(mat2 m, mat2 n);
GRIMDEF mat2 operator*(mat2 m, float s);
GRIMDEF mat2 operator*(float s, mat2 m);
GRIMDEF mat2 operator*(mat2 m, mat2 n);
GRIMDEF vec2 operator*(mat2 m, vec2 b);
GRIMDEF mat2 &operator+=(mat2 &a, mat2 n);
GRIMDEF mat2 &operator-=(mat2 &a, mat2 n);
GRIMDEF mat2 &operator*=(mat2 &a, float s);
GRIMDEF mat2 &operator*=(mat2 &a, mat2 n);
// mat3
GRIMDEF mat3 m3(float ax, float ay, float az, float bx, float by, float bz,
                float cx, float cy, float cz);
GRIMDEF mat3 m3(vec3 a, vec3 b, vec3 c);
GRIMDEF mat3 operator-(mat3 m);
GRIMDEF mat3 operator+(mat3 m, mat3 n);
GRIMDEF mat3 operator-(mat3 m, mat3 n);
GRIMDEF mat3 operator*(mat3 m, float s);
GRIMDEF mat3 operator*(float s, mat3 m);
GRIMDEF mat3 operator*(mat3 m, mat3 n);
GRIMDEF vec3 operator*(mat3 m, vec3 b);
GRIMDEF mat3 &operator+=(mat3 &m, mat3 n);
GRIMDEF mat3 &operator-=(mat3 &m, mat3 n);
GRIMDEF mat3 &operator*=(mat3 &m, float s);
GRIMDEF mat3 &operator*=(mat3 &m, mat3 n);
// mat4
GRIMDEF mat4 m4(float ax, float ay, float az, float aw, float bx, float by,
                float bz, float bw, float cx, float cy, float cz, float cw,
                float dx, float dy, float dz, float dw);
GRIMDEF mat4 m4(vec4 a, vec4 b, vec4 c, vec4 d);
GRIMDEF mat4 operator-(mat4 a);
GRIMDEF mat4 operator+(mat4 a, mat4 n);
GRIMDEF mat4 operator-(mat4 a, mat4 n);
GRIMDEF mat4 operator*(mat4 a, float s);
GRIMDEF mat4 operator*(float s, mat4 a);
GRIMDEF mat4 operator*(mat4 a, mat4 n);
GRIMDEF vec4 operator*(mat4 a, vec4 b);
GRIMDEF mat4 &operator+=(mat4 &m, mat4 n);
GRIMDEF mat4 &operator-=(mat4 &m, mat4 n);
GRIMDEF mat4 &operator*=(mat4 &m, float s);
GRIMDEF mat4 &operator*=(mat4 &m, mat4 n);

// helpers
GRIMDEF mat4 lookat(vec3 eye, vec3 center, vec3 up);
GRIMDEF mat4 perspective(float near, float far, float fov, float aspect_ratio);
GRIMDEF mat4 ortho(float left, float right, float bottom, float top, float near,
                   float far);
GRIMDEF mat4 translation(vec3 v);
GRIMDEF mat4 rotation_x(float rad);
GRIMDEF mat4 rotation_y(float rad);
GRIMDEF mat4 rotation_z(float rad);

// glsl functions
GRIMDEF float radians(float degrees);
GRIMDEF vec2 radians(vec2 degrees);
GRIMDEF vec3 radians(vec3 degrees);
GRIMDEF vec4 radians(vec4 degrees);

GRIMDEF float degrees(float radians);
GRIMDEF vec2 degrees(vec2 radians);
GRIMDEF vec3 degrees(vec3 radians);
GRIMDEF vec4 degrees(vec4 radians);

GRIMDEF vec2 sin(vec2 radians);
GRIMDEF vec3 sin(vec3 radians);
GRIMDEF vec4 sin(vec4 radians);

GRIMDEF vec2 cos(vec2 radians);
GRIMDEF vec3 cos(vec3 radians);
GRIMDEF vec4 cos(vec4 radians);

GRIMDEF vec2 tan(vec2 radians);
GRIMDEF vec3 tan(vec3 radians);
GRIMDEF vec4 tan(vec4 radians);

GRIMDEF vec2 asin(vec2 x);
GRIMDEF vec3 asin(vec3 x);
GRIMDEF vec4 asin(vec4 x);

GRIMDEF vec2 acos(vec2 x);
GRIMDEF vec3 acos(vec3 x);
GRIMDEF vec4 acos(vec4 x);

GRIMDEF vec2 atan(vec2 y_over_x);
GRIMDEF vec3 atan(vec3 y_over_x);
GRIMDEF vec4 atan(vec4 y_over_x);

GRIMDEF vec2 atan(vec2 y, vec2 x);
GRIMDEF vec3 atan(vec3 y, vec3 x);
GRIMDEF vec4 atan(vec4 y, vec4 x);

GRIMDEF vec2 pow(vec2 x, vec2 y);
GRIMDEF vec3 pow(vec3 x, vec3 y);
GRIMDEF vec4 pow(vec4 x, vec4 y);

GRIMDEF vec2 exp(vec2 x);
GRIMDEF vec3 exp(vec3 x);
GRIMDEF vec4 exp(vec4 x);

GRIMDEF vec2 log(vec2 x);
GRIMDEF vec3 log(vec3 x);
GRIMDEF vec4 log(vec4 x);

GRIMDEF vec2 exp2(vec2 x);
GRIMDEF vec3 exp2(vec3 x);
GRIMDEF vec4 exp2(vec4 x);

GRIMDEF vec2 log2(vec2 x);
GRIMDEF vec3 log2(vec3 x);
GRIMDEF vec4 log2(vec4 x);

GRIMDEF vec2 sqrt(vec2 x);
GRIMDEF vec3 sqrt(vec3 x);
GRIMDEF vec4 sqrt(vec4 x);

GRIMDEF float abs(float x);
GRIMDEF vec2 abs(vec2 x);
GRIMDEF vec3 abs(vec3 x);
GRIMDEF vec4 abs(vec4 x);

GRIMDEF float sign(float x);
GRIMDEF vec2 sign(vec2 x);
GRIMDEF vec3 sign(vec3 x);
GRIMDEF vec4 sign(vec4 x);

GRIMDEF vec2 floor(vec2 x);
GRIMDEF vec3 floor(vec3 x);
GRIMDEF vec4 floor(vec4 x);

GRIMDEF vec2 ceil(vec2 x);
GRIMDEF vec3 ceil(vec3 x);
GRIMDEF vec4 ceil(vec4 x);

GRIMDEF float min(float x, float y);
GRIMDEF vec2 min(vec2 x, vec2 y);
GRIMDEF vec3 min(vec3 x, vec3 y);
GRIMDEF vec4 min(vec4 x, vec4 y);

GRIMDEF vec2 min(vec2 x, float y);
GRIMDEF vec3 min(vec3 x, float y);
GRIMDEF vec4 min(vec4 x, float y);

GRIMDEF float max(float x, float y);
GRIMDEF vec2 max(vec2 x, vec2 y);
GRIMDEF vec3 max(vec3 x, vec3 y);
GRIMDEF vec4 max(vec4 x, vec4 y);

GRIMDEF vec2 max(vec2 x, float y);
GRIMDEF vec3 max(vec3 x, float y);
GRIMDEF vec4 max(vec4 x, float y);

GRIMDEF float clamp(float x, float min, float max);
GRIMDEF vec2 clamp(vec2 x, vec2 min, vec2 max);
GRIMDEF vec3 clamp(vec3 x, vec3 min, vec3 max);
GRIMDEF vec4 clamp(vec4 x, vec4 min, vec4 max);

GRIMDEF float clamp(float x, float min, float max);
GRIMDEF vec2 clamp(vec2 x, float min, float max);
GRIMDEF vec3 clamp(vec3 x, float min, float max);
GRIMDEF vec4 clamp(vec4 x, float min, float max);

GRIMDEF float mix(float x, float y, float a);
GRIMDEF vec2 mix(vec2 x, vec2 y, vec2 a);
GRIMDEF vec3 mix(vec3 x, vec3 y, vec3 a);
GRIMDEF vec4 mix(vec4 x, vec4 y, vec4 a);

GRIMDEF vec2 mix(vec2 x, vec2 y, float a);
GRIMDEF vec3 mix(vec3 x, vec3 y, float a);
GRIMDEF vec4 mix(vec4 x, vec4 y, float a);

GRIMDEF float step(float edge, float x);
GRIMDEF vec2 step(vec2 edge, vec2 x);
GRIMDEF vec3 step(vec3 edge, vec3 x);
GRIMDEF vec4 step(vec4 edge, vec4 x);

GRIMDEF vec2 step(float edge, vec2 x);
GRIMDEF vec3 step(float edge, vec3 x);
GRIMDEF vec4 step(float edge, vec4 x);

GRIMDEF float length(float x);
GRIMDEF float length(vec2 x);
GRIMDEF float length(vec3 x);
GRIMDEF float length(vec4 x);

GRIMDEF float length2(float x);
GRIMDEF float length2(vec2 x);
GRIMDEF float length2(vec3 x);
GRIMDEF float length2(vec4 x);

GRIMDEF float distance(float p0, float p1);
GRIMDEF float distance(vec2 p0, vec2 p1);
GRIMDEF float distance(vec3 p0, vec3 p1);
GRIMDEF float distance(vec4 p0, vec4 p1);

GRIMDEF float dot(float x, float y);
GRIMDEF float dot(vec2 x, vec2 y);
GRIMDEF float dot(vec3 x, vec3 y);
GRIMDEF float dot(vec4 x, vec4 y);

GRIMDEF vec3 cross(vec3 x, vec3 y);

GRIMDEF float normalize(float x);
GRIMDEF vec2 normalize(vec2 x);
GRIMDEF vec3 normalize(vec3 x);
GRIMDEF vec4 normalize(vec4 x);
#endif  // GRIM_MATH_INCLUDE_H_

/****************************
 *
 *      IMPLEMENTATION
 *
 ****************************
*/
#ifdef GRIM_MATH_IMPLEMENTATION
#include <math.h>

#define GRIM_PI 3.14159265358979323846f
#define GRIM_DEG2RAD(_a) ((_a)*GRIM_PI / 180.0f)
#define GRIM_RAD2DEG(_a) ((_a)*180.0f / GRIM_PI)

// vec2
GRIMDEF vec2 v2(float x, float y) { return {{x, y}}; }
GRIMDEF vec2 v2(float const *v) { return {{*v, *(v + 1)}}; }
GRIMDEF vec2 operator-(vec2 a) { return {{-a.x, -a.y}}; }
GRIMDEF vec2 operator+(vec2 a, vec2 b) { return {{a.x + b.x, a.y + b.y}}; }
GRIMDEF vec2 operator-(vec2 a, vec2 b) { return {{a.x - b.x, a.y - b.y}}; }
GRIMDEF vec2 operator*(vec2 a, float s) { return {{s * a.x, s * a.y}}; }
GRIMDEF vec2 operator*(float s, vec2 a) { return {{s * a.x, s * a.y}}; }
GRIMDEF vec2 &operator+=(vec2 &a, vec2 b) {
  a = a + b;
  return a;
}
GRIMDEF vec2 &operator-=(vec2 &a, vec2 b) {
  a = a - b;
  return a;
}
GRIMDEF vec2 &operator*=(vec2 &a, float s) {
  a = s * a;
  return a;
}
// vec3
GRIMDEF vec3 v3(float x, float y, float z) { return {{x, y, z}}; }
GRIMDEF vec3 v3(float const *v) { return {{*v, *(v + 1), *(v + 2)}}; }
GRIMDEF vec3 v3(vec2 xy, float z) { return {{xy.x, xy.y, z}}; }
GRIMDEF vec3 operator-(vec3 a) { return {{-a.x, -a.y, -a.z}}; }
GRIMDEF vec3 operator+(vec3 a, vec3 b) {
  return {{a.x + b.x, a.y + b.y, a.z + b.z}};
}
GRIMDEF vec3 operator-(vec3 a, vec3 b) {
  return {{a.x - b.x, a.y - b.y, a.z - b.z}};
}
GRIMDEF vec3 operator*(vec3 a, float s) {
  return {{s * a.x, s * a.y, s * a.z}};
}
GRIMDEF vec3 operator*(float s, vec3 a) {
  return {{s * a.x, s * a.y, s * a.z}};
}
GRIMDEF vec3 &operator+=(vec3 &a, vec3 b) {
  a = a + b;
  return a;
}
GRIMDEF vec3 &operator-=(vec3 &a, vec3 b) {
  a = a - b;
  return a;
}
GRIMDEF vec3 &operator*=(vec3 &a, float s) {
  a = s * a;
  return a;
}
// vec4
GRIMDEF vec4 v4(float x, float y, float z, float w) { return {{x, y, z, w}}; }
GRIMDEF vec4 v4(float const *v) { return {{*v, *(v + 1), *(v + 2), *(v + 3)}}; }
GRIMDEF vec4 v4(vec2 xy, float z, float w) { return {{xy.x, xy.y, z, w}}; }
GRIMDEF vec4 v4(vec3 xyz, float w) { return {{xyz.x, xyz.y, xyz.z, w}}; }
GRIMDEF vec4 operator-(vec4 a) { return {{-a.x, -a.y, -a.z, -a.w}}; }
GRIMDEF vec4 operator+(vec4 a, vec4 b) {
  return {{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}};
}
GRIMDEF vec4 operator-(vec4 a, vec4 b) {
  return {{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}};
}
GRIMDEF vec4 operator*(vec4 a, float s) {
  return {{s * a.x, s * a.y, s * a.z, s * a.w}};
}
GRIMDEF vec4 operator*(float s, vec4 a) {
  return {{s * a.x, s * a.y, s * a.z, s * a.w}};
}
GRIMDEF vec4 &operator+=(vec4 &a, vec4 b) {
  a = a + b;
  return a;
}
GRIMDEF vec4 &operator-=(vec4 &a, vec4 b) {
  a = a - b;
  return a;
}
GRIMDEF vec4 &operator*=(vec4 &a, float s) {
  a = s * a;
  return a;
}

// mat2
// ax bx
// ay by
GRIMDEF mat2 m2(float ax, float ay, float bx, float by) {
  return {{ax, ay, bx, by}};
}
GRIMDEF mat2 m2(vec2 a, vec2 b) { return {{a.x, a.y, b.x, b.y}}; }
GRIMDEF mat2 operator-(mat2 m) {
  return {{
      -m.ax, -m.ay,  // a
      -m.bx, -m.by   // b
  }};
}
GRIMDEF mat2 operator+(mat2 m, mat2 n) {
  return {{
      m.ax + n.ax,  // ax
      m.ay + n.ay,  // ay
      m.bx + n.bx,  // bx
      m.by + n.by   // by
  }};
}
GRIMDEF mat2 operator-(mat2 m, mat2 n) {
  return {{
      m.ax - n.ax,  // ax
      m.ay - n.ay,  // ay
      m.bx - n.bx,  // bx
      m.by - n.by   // by
  }};
}
GRIMDEF mat2 operator*(mat2 m, float s) {
  return {{
      s * m.ax,  // ax
      s * m.ay,  // ay
      s * m.bx,  // bx
      s * m.by   // by
  }};
}
GRIMDEF mat2 operator*(float s, mat2 m) {
  return {{
      s * m.ax,  // ax
      s * m.ay,  // ay
      s * m.bx,  // bx
      s * m.by   // by
  }};
}
GRIMDEF mat2 operator*(mat2 m, mat2 n) {
  return {{
      m.ax * n.ax + m.bx * n.ay,  // ax
      m.ay * n.ax + m.by * n.ay,  // ay
      m.ax * n.bx + m.bx * n.by,  // bx
      m.ay * n.bx + m.by * n.by   // by
  }};
}

GRIMDEF vec2 operator*(mat2 m, vec2 n) {
  return {{
      m.ax * n.x + m.bx * n.y,  // x
      m.ay * n.x + m.by * n.y   // y
  }};
}
GRIMDEF mat2 &operator+=(mat2 &m, mat2 n) {
  m = m + n;
  return m;
}
GRIMDEF mat2 &operator-=(mat2 &m, mat2 n) {
  m = m - n;
  return m;
}
GRIMDEF mat2 &operator*=(mat2 &m, float s) {
  m = s * m;
  return m;
}
GRIMDEF mat2 &operator*=(mat2 &m, mat2 n) {
  m = m * n;
  return m;
}
// mat3
// ax bx cx
// ay by cy
// az bz cz
GRIMDEF mat3 m3(float ax, float ay, float az, float bx, float by, float bz,
                float cx, float cy, float cz) {
  return {{
      ax, ay, az,  // a
      bx, by, bz,  // b
      cx, cy, cz   // c
  }};
}
GRIMDEF mat3 m3(vec3 a, vec3 b, vec3 c) {
  return {{
      a.x, a.y, a.z,  // a
      b.x, b.y, b.z,  // b
      c.x, c.y, c.z   // c
  }};
}
GRIMDEF mat3 operator-(mat3 m) {
  return {{
      -m.ax, -m.ay, -m.az,  // a
      -m.bx, -m.by, -m.bz,  // b
      -m.cx, -m.cy, -m.cz   // c
  }};
}
GRIMDEF mat3 operator+(mat3 m, mat3 n) {
  return {{
      m.ax + n.ax,  // ax
      m.ay + n.ay,  // ay
      m.az + n.az,  // az
      m.bx + n.bx,  // bx
      m.by + n.by,  // by
      m.bz + n.bz,  // bz
      m.cx + n.cx,  // cx
      m.cy + n.cy,  // cy
      m.cz + n.cz   // cz
  }};
}
GRIMDEF mat3 operator-(mat3 m, mat3 n) {
  return {{
      m.ax - n.ax,  // ax
      m.ay - n.ay,  // ay
      m.az - n.az,  // az
      m.bx - n.bx,  // bx
      m.by - n.by,  // by
      m.bz - n.bz,  // bz
      m.cx - n.cx,  // cx
      m.cy - n.cy,  // cy
      m.cz - n.cz   // cz
  }};
}
GRIMDEF mat3 operator*(mat3 m, float s) {
  return {{
      s * m.ax,  // ax
      s * m.ay,  // ay
      s * m.az,  // az
      s * m.bx,  // bx
      s * m.by,  // by
      s * m.bz,  // bz
      s * m.cx,  // cx
      s * m.cy,  // cy
      s * m.cz   // cy
  }};
}
GRIMDEF mat3 operator*(float s, mat3 m) {
  return {{
      s * m.ax,  // ax
      s * m.ay,  // ay
      s * m.az,  // az
      s * m.bx,  // bx
      s * m.by,  // by
      s * m.bz,  // bz
      s * m.cx,  // cx
      s * m.cy,  // cy
      s * m.cz   // cy
  }};
}
GRIMDEF mat3 operator*(mat3 m, mat3 n) {
  return {{
      m.ax * n.ax + m.bx * n.ay + m.cx * n.az,  // ax
      m.ay * n.ax + m.by * n.ay + m.cy * n.az,  // ay
      m.az * n.ax + m.bz * n.ay + m.cz * n.az,  // az
      m.ax * n.bx + m.bx * n.by + m.cx * n.bz,  // bx
      m.ay * n.bx + m.by * n.by + m.cy * n.bz,  // by
      m.az * n.bx + m.bz * n.by + m.cz * n.bz,  // bz
      m.ax * n.cx + m.bx * n.cy + m.cx * n.cz,  // cx
      m.ay * n.cx + m.by * n.cy + m.cy * n.cz,  // cy
      m.az * n.cx + m.bz * n.cy + m.cz * n.cz   // cz
  }};
}

GRIMDEF vec3 operator*(mat3 m, vec3 n) {
  return {{
      m.ax * n.x + m.bx * n.y + m.cx * n.z,  // x
      m.ay * n.x + m.by * n.y + m.cy * n.z,  // y
      m.az * n.x + m.bz * n.y + m.cz * n.z   // y
  }};
}

GRIMDEF mat3 &operator+=(mat3 &m, mat3 n) {
  m = m + n;
  return m;
}
GRIMDEF mat3 &operator-=(mat3 &m, mat3 n) {
  m = m - n;
  return m;
}
GRIMDEF mat3 &operator*=(mat3 &m, float s) {
  m = s * m;
  return m;
}
GRIMDEF mat3 &operator*=(mat3 &m, mat3 n) {
  m = m * n;
  return m;
}
// mat4
// ax bx cx dx
// ay by cy dy
// az bz cz dz
// aw bw cw dw
GRIMDEF mat4 m4(float ax, float ay, float az, float aw, float bx, float by,
                float bz, float bw, float cx, float cy, float cz, float cw,
                float dx, float dy, float dz, float dw) {
  return {{
      ax, ay, az, aw,  // a
      bx, by, bz, bw,  // b
      cx, cy, cz, cw,  // c
      dx, dy, dz, dw   // d
  }};
}
GRIMDEF mat4 m4(vec4 a, vec4 b, vec4 c, vec4 d) {
  return {{
      a.x, a.y, a.z, a.w,  // a
      b.x, b.y, b.z, b.w,  // b
      c.x, c.y, c.z, c.w,  // c
      d.x, d.y, d.z, d.w   // d
  }};
}
GRIMDEF mat4 operator-(mat4 m) {
  return {{
      -m.ax, -m.ay, -m.az, -m.aw,  // a
      -m.bx, -m.by, -m.bz, -m.bw,  // b
      -m.cx, -m.cy, -m.cz, -m.cw,  // c
      -m.dx, -m.dy, -m.dz, -m.dw   // d
  }};
}
GRIMDEF mat4 operator+(mat4 m, mat4 n) {
  return {{
      m.ax + n.ax,  // ax
      m.ay + n.ay,  // ay
      m.az + n.az,  // az
      m.aw + n.aw,  // aw
      m.bx + n.bx,  // bx
      m.by + n.by,  // by
      m.bz + n.bz,  // bz
      m.bw + n.bw,  // bw
      m.cx + n.cx,  // cx
      m.cy + n.cy,  // cy
      m.cz + n.cz,  // cz
      m.cw + n.cw,  // cw
      m.dx + n.dx,  // dx
      m.dy + n.dy,  // dy
      m.dz + n.dz,  // dz
      m.dw + n.dw   // dw
  }};
}
GRIMDEF mat4 operator-(mat4 m, mat4 n) {
  return {{
      m.ax - n.ax,  // ax
      m.ay - n.ay,  // ay
      m.az - n.az,  // az
      m.aw - n.aw,  // aw
      m.bx - n.bx,  // bx
      m.by - n.by,  // by
      m.bz - n.bz,  // bz
      m.bw - n.bw,  // bw
      m.cx - n.cx,  // cx
      m.cy - n.cy,  // cy
      m.cz - n.cz,  // cz
      m.cw - n.cw,  // cw
      m.dx - n.dx,  // dx
      m.dy - n.dy,  // dy
      m.dz - n.dz,  // dz
      m.dw - n.dw   // dw
  }};
}
GRIMDEF mat4 operator*(mat4 m, float s) {
  return {{
      s * m.ax,  // ax
      s * m.ay,  // ay
      s * m.az,  // az
      s * m.aw,  // aw
      s * m.bx,  // bx
      s * m.by,  // by
      s * m.bz,  // bz
      s * m.bw,  // bw
      s * m.cx,  // cx
      s * m.cy,  // cy
      s * m.cz,  // cy
      s * m.cw,  // cw
      s * m.dx,  // dx
      s * m.dy,  // dy
      s * m.dz,  // dy
      s * m.dw,  // dw
  }};
}
GRIMDEF mat4 operator*(float s, mat4 m) {
  return {{
      s * m.ax,  // ax
      s * m.ay,  // ay
      s * m.az,  // az
      s * m.aw,  // aw
      s * m.bx,  // bx
      s * m.by,  // by
      s * m.bz,  // bz
      s * m.bw,  // bw
      s * m.cx,  // cx
      s * m.cy,  // cy
      s * m.cz,  // cy
      s * m.cw,  // cw
      s * m.dx,  // dx
      s * m.dy,  // dy
      s * m.dz,  // dy
      s * m.dw,  // dw
  }};
}

// ax bx cx dx
// ay by cy dy
// az bz cz dz
// aw bw cw dw
GRIMDEF mat4 operator*(mat4 m, mat4 n) {
  return {{
      m.ax * n.ax + m.bx * n.ay + m.cx * n.az + m.dx * n.aw,  // ax
      m.ay * n.ax + m.by * n.ay + m.cy * n.az + m.dy * n.aw,  // ay
      m.az * n.ax + m.bz * n.ay + m.cz * n.az + m.dz * n.aw,  // az
      m.aw * n.ax + m.bw * n.ay + m.cw * n.az + m.dw * n.aw,  // aw
      m.ax * n.bx + m.bx * n.by + m.cx * n.bz + m.dx * n.bw,  // bx
      m.ay * n.bx + m.by * n.by + m.cy * n.bz + m.dy * n.bw,  // by
      m.az * n.bx + m.bz * n.by + m.cz * n.bz + m.dz * n.bw,  // bz
      m.aw * n.bx + m.bw * n.by + m.cw * n.bz + m.dw * n.bw,  // bw
      m.ax * n.cx + m.bx * n.cy + m.cx * n.cz + m.dx * n.cw,  // cx
      m.ay * n.cx + m.by * n.cy + m.cy * n.cz + m.dy * n.cw,  // cy
      m.az * n.cx + m.bz * n.cy + m.cz * n.cz + m.dz * n.cw,  // cz
      m.aw * n.cx + m.bw * n.cy + m.cw * n.cz + m.dw * n.cw,  // cw
      m.ax * n.dx + m.bx * n.dy + m.cx * n.dz + m.dx * n.dw,  // dx
      m.ay * n.dx + m.by * n.dy + m.cy * n.dz + m.dy * n.dw,  // dy
      m.az * n.dx + m.bz * n.dy + m.cz * n.dz + m.dz * n.dw,  // dz
      m.aw * n.dx + m.bw * n.dy + m.cw * n.dz + m.dw * n.dw   // dw
  }};
}

GRIMDEF vec4 operator*(mat4 m, vec4 n) {
  return {{
      m.ax * n.x + m.bx * n.y + m.cx * n.z + m.dx * n.w,  // x
      m.ay * n.x + m.by * n.y + m.cy * n.z + m.dy * n.w,  // y
      m.az * n.x + m.bz * n.y + m.cz * n.z + m.dz * n.w,  // y
      m.aw * n.x + m.bw * n.y + m.cw * n.z + m.dw * n.w   // y
  }};
}

GRIMDEF mat4 &operator+=(mat4 &m, mat4 n) {
  m = m + n;
  return m;
}

GRIMDEF mat4 &operator-=(mat4 &m, mat4 n) {
  m = m - n;
  return m;
}

GRIMDEF mat4 &operator*=(mat4 &m, float s) {
  m = s * m;
  return m;
}

GRIMDEF mat4 &operator*=(mat4 &m, mat4 n) {
  m = m * n;
  return m;
}

GRIMDEF mat4 lookat(vec3 eye, vec3 center, vec3 up) {
  /*  Rotation =
   *    right_x   right_y   right_z   0.0f
   *    up_x      up_y      up_z      0.0f
   *    forward_x forward_y forward_z 0.0f
   *    0.0f      0.0f      0.0f      1.0f
   *
   * Translation =
   *  0.0f 0.0f 0.0f -eye.x
   *  0.0f 0.0f 0.0f -eye.y
   *  0.0f 0.0f 0.0f -eye.z
   *  0.0f 0.0f 0.0f 1.0f
   *
   *  Result = Rotation * Translation
   */
  vec3 const forward = normalize(center - eye);
  vec3 const right = normalize(cross(forward, up));
  up = normalize(cross(right, forward));
  float const tx = dot(right, -eye);
  float const ty = dot(up, -eye);
  float const tz = dot(-forward, -eye);
  return m4(right.x, up.x, -forward.x, 0.0f,  //
            right.y, up.y, -forward.y, 0.0f,  //
            right.z, up.z, -forward.z, 0.0f,  //
            tx, ty, tz, 1.0f);
}

GRIMDEF mat4 translation(vec3 v) {
  return {{1.0f, 0.0f, 0.0f, 0.0f,  // a
           0.0f, 1.0f, 0.0f, 0.0f,  // b
           0.0f, 0.0f, 1.0f, 0.0f,  // c
           v.x, v.y, v.z, 1.0f}};   // d
}

GRIMDEF mat4 perspective(float near, float far, float fov, float aspect_ratio) {
  float const range = tan(0.5f * fov) * near;
  float const sx = near / (range * aspect_ratio);
  float const sy = near / range;
  float const sz = -(far + near) / (far - near);
  float const pz = -(2.0f * far * near) / (far - near);
  return m4(sx, 0.0f, 0.0f, 0.0f,   // a
            0.0f, sy, 0.0f, 0.0f,   // b
            0.0f, 0.0f, sz, -1.0f,  // c
            0.0f, 0.0f, pz, 0.0f);  // d
}

GRIMDEF mat4 ortho(float left, float right, float bottom, float top, float near,
                   float far) {
  return {{2.0f / (right - left), 0.0f, 0.0f, 0.0f, 0.0f, 2.0f / (top - bottom),
           0.0f, 0.0f, 0.0f, 0.0f, -2.0f / (far - near), 0.0f,
           -(right + left) / (right - left), -(top + bottom) / (top - bottom),
           -(far + near) / (far - near), 1.0f}};
}

#define GRIM_VEC2F(f, v)   \
  {                        \
    { f((v).x), f((v).y) } \
  }
#define GRIM_VEC3F(f, v)             \
  {                                  \
    { f((v).x), f((v).y), f((v).z) } \
  }
#define GRIM_VEC4F(f, v)                       \
  {                                            \
    { f((v).x), f((v).y), f((v).z), f((v).w) } \
  }

// glsl functions
float radians(float degrees) { return GRIM_DEG2RAD(degrees); }
vec2 radians(vec2 degrees) { return GRIM_VEC2F(GRIM_DEG2RAD, degrees); }
vec3 radians(vec3 degrees) { return GRIM_VEC3F(GRIM_DEG2RAD, degrees); }
vec4 radians(vec4 degrees) { return GRIM_VEC4F(GRIM_DEG2RAD, degrees); }

float degrees(float radians) { return GRIM_RAD2DEG(radians); }
vec2 degrees(vec2 radians) { return GRIM_VEC2F(GRIM_RAD2DEG, radians); }
vec3 degrees(vec3 radians) { return GRIM_VEC3F(GRIM_RAD2DEG, radians); }
vec4 degrees(vec4 radians) { return GRIM_VEC4F(GRIM_RAD2DEG, radians); }

vec2 sin(vec2 radians) { return GRIM_VEC2F(sinf, radians); }
vec3 sin(vec3 radians) { return GRIM_VEC3F(sinf, radians); }
vec4 sin(vec4 radians) { return GRIM_VEC4F(sinf, radians); }

vec2 cos(vec2 radians) { return GRIM_VEC2F(cosf, radians); }
vec3 cos(vec3 radians) { return GRIM_VEC3F(cosf, radians); }
vec4 cos(vec4 radians) { return GRIM_VEC4F(cosf, radians); }

vec2 tan(vec2 radians) { return GRIM_VEC2F(tanf, radians); }
vec3 tan(vec3 radians) { return GRIM_VEC3F(tanf, radians); }
vec4 tan(vec4 radians) { return GRIM_VEC4F(tanf, radians); }

vec2 asin(vec2 radians) { return GRIM_VEC2F(asinf, radians); }
vec3 asin(vec3 radians) { return GRIM_VEC3F(asinf, radians); }
vec4 asin(vec4 radians) { return GRIM_VEC4F(asinf, radians); }

vec2 acos(vec2 radians) { return GRIM_VEC2F(acosf, radians); }
vec3 acos(vec3 radians) { return GRIM_VEC3F(acosf, radians); }
vec4 acos(vec4 radians) { return GRIM_VEC4F(acosf, radians); }

vec2 atan(vec2 radians) { return GRIM_VEC2F(atanf, radians); }
vec3 atan(vec3 radians) { return GRIM_VEC3F(atanf, radians); }
vec4 atan(vec4 radians) { return GRIM_VEC4F(atanf, radians); }

vec2 pow(vec2 x, vec2 y) { return v2(powf(x.x, y.x), powf(x.y, y.y)); }
vec3 pow(vec3 x, vec3 y) {
  return v3(powf(x.x, y.x), powf(x.y, y.y), powf(x.z, y.z));
}
vec4 pow(vec4 x, vec4 y) {
  return v4(powf(x.x, y.x), powf(x.y, y.y), powf(x.z, y.z), powf(x.w, y.w));
}

vec2 exp(vec2 x) { return GRIM_VEC2F(expf, x); }
vec3 exp(vec3 x) { return GRIM_VEC3F(expf, x); }
vec4 exp(vec4 x) { return GRIM_VEC4F(expf, x); }

vec2 log(vec2 x) { return GRIM_VEC2F(logf, x); }
vec3 log(vec3 x) { return GRIM_VEC3F(logf, x); }
vec4 log(vec4 x) { return GRIM_VEC4F(logf, x); }

vec2 exp2(vec2 x) { return GRIM_VEC2F(exp2f, x); }
vec3 exp2(vec3 x) { return GRIM_VEC3F(exp2f, x); }
vec4 exp2(vec4 x) { return GRIM_VEC4F(exp2f, x); }

vec2 log2(vec2 x) { return GRIM_VEC2F(log2f, x); }
vec3 log2(vec3 x) { return GRIM_VEC3F(log2f, x); }
vec4 log2(vec4 x) { return GRIM_VEC4F(log2f, x); }

vec2 sqrt(vec2 x) { return GRIM_VEC2F(sqrtf, x); }
vec3 sqrt(vec3 x) { return GRIM_VEC3F(sqrtf, x); }
vec4 sqrt(vec4 x) { return GRIM_VEC4F(sqrtf, x); }

float abs(float x) { return fabsf(x); }
vec2 abs(vec2 x) { return GRIM_VEC2F(abs, x); }
vec3 abs(vec3 x) { return GRIM_VEC3F(abs, x); }
vec4 abs(vec4 x) { return GRIM_VEC4F(abs, x); }

float sign(float x) {
  if (x > 0.0f) {
    return 1.0f;
  } else if (x < 0.0f) {
    return -1.0f;
  } else {
    return 0.0f;
  }
}
vec2 sign(vec2 x) { return GRIM_VEC2F(sign, x); }
vec3 sign(vec3 x) { return GRIM_VEC3F(sign, x); }
vec4 sign(vec4 x) { return GRIM_VEC4F(sign, x); }

vec2 floor(vec2 x) { return GRIM_VEC2F(floorf, x); }
vec3 floor(vec3 x) { return GRIM_VEC3F(floorf, x); }
vec4 floor(vec4 x) { return GRIM_VEC4F(floorf, x); }

vec2 ceil(vec2 x) { return GRIM_VEC2F(ceilf, x); }
vec3 ceil(vec3 x) { return GRIM_VEC3F(ceilf, x); }
vec4 ceil(vec4 x) { return GRIM_VEC4F(ceilf, x); }

float min(float x, float y) { return fminf(x, y); }
vec2 min(vec2 x, vec2 y) { return {{fminf(x.x, y.x), fminf(x.y, y.y)}}; }
vec3 min(vec3 x, vec3 y) {
  return {{fminf(x.x, y.x), fminf(x.y, y.y), fminf(x.z, y.z)}};
}
vec4 min(vec4 x, vec4 y) {
  return {{fminf(x.x, y.x), fminf(x.y, y.y), fminf(x.z, y.z), fminf(x.w, y.w)}};
}

vec2 min(vec2 x, float y) { return {{fminf(x.x, y), fminf(x.y, y)}}; }
vec3 min(vec3 x, float y) {
  return {{fminf(x.x, y), fminf(x.y, y), fminf(x.z, y)}};
}
vec4 min(vec4 x, float y) {
  return {{fminf(x.x, y), fminf(x.y, y), fminf(x.z, y), fminf(x.w, y)}};
}

float max(float x, float y) { return fmaxf(x, y); }
vec2 max(vec2 x, vec2 y) { return {{fmaxf(x.x, y.x), fmaxf(x.y, y.y)}}; }
vec3 max(vec3 x, vec3 y) {
  return {{fmaxf(x.x, y.x), fmaxf(x.y, y.y), fmaxf(x.z, y.z)}};
}
vec4 max(vec4 x, vec4 y) {
  return {{fmaxf(x.x, y.x), fmaxf(x.y, y.y), fmaxf(x.z, y.z), fmaxf(x.w, y.w)}};
}

vec2 max(vec2 x, float y) { return {{fmaxf(x.x, y), fmaxf(x.y, y)}}; }
vec3 max(vec3 x, float y) {
  return {{fmaxf(x.x, y), fmaxf(x.y, y), fmaxf(x.z, y)}};
}
vec4 max(vec4 x, float y) {
  return {{fmaxf(x.x, y), fmaxf(x.y, y), fmaxf(x.z, y), fmaxf(x.w, y)}};
}

float clamp(float x, float min, float max) {
  if (x < min) {
    return min;
  } else if (x > max) {
    return max;
  } else {
    return x;
  }
}

vec2 clamp(vec2 x, vec2 min, vec2 max) {
  return {{clamp(x.x, min.x, max.x), clamp(x.y, min.y, max.y)}};
}

vec3 clamp(vec3 x, vec3 min, vec3 max) {
  return {{clamp(x.x, min.x, max.x), clamp(x.y, min.y, max.y),
           clamp(x.z, min.z, max.z)}};
}

vec4 clamp(vec4 x, vec4 min, vec4 max) {
  return {{clamp(x.x, min.x, max.x), clamp(x.y, min.y, max.y),
           clamp(x.z, min.z, max.z), clamp(x.w, min.w, max.w)}};
}

vec2 clamp(vec2 x, float min, float max) {
  return {{clamp(x.x, min, max), clamp(x.y, min, max)}};
}

vec3 clamp(vec3 x, float min, float max) {
  return {{clamp(x.x, min, max), clamp(x.y, min, max), clamp(x.z, min, max)}};
}

vec4 clamp(vec4 x, float min, float max) {
  return {{clamp(x.x, min, max), clamp(x.y, min, max), clamp(x.z, min, max),
           clamp(x.w, min, max)}};
}

float mix(float x, float y, float a) { return (1.0f - a) * x + a * y; }
vec2 mix(vec2 x, vec2 y, vec2 a) {
  return {{mix(x.x, y.x, a.x), mix(x.y, y.y, a.y)}};
}
vec3 mix(vec3 x, vec3 y, vec3 a) {
  return {{mix(x.x, y.x, a.x), mix(x.y, y.y, a.y), mix(x.z, y.z, a.z)}};
}
vec4 mix(vec4 x, vec4 y, vec4 a) {
  return {{mix(x.x, y.x, a.x), mix(x.y, y.y, a.y), mix(x.z, y.z, a.z),
           mix(x.w, y.w, a.w)}};
}

vec2 mix(vec2 x, vec2 y, float a) {
  return {{mix(x.x, y.x, a), mix(x.y, y.y, a)}};
}

vec3 mix(vec3 x, vec3 y, float a) {
  return {{mix(x.x, y.x, a), mix(x.y, y.y, a), mix(x.z, y.z, a)}};
}
vec4 mix(vec4 x, vec4 y, float a) {
  return {
      {mix(x.x, y.x, a), mix(x.y, y.y, a), mix(x.z, y.z, a), mix(x.w, y.w, a)}};
}

float step(float edge, float x) {
  if (x < edge) {
    return 0.0f;
  } else {
    return 1.0f;
  }
}
vec2 step(vec2 edge, vec2 x) {
  return {{step(edge.x, x.x), step(edge.y, x.y)}};
}
vec3 step(vec3 edge, vec3 x) {
  return {{step(edge.x, x.x), step(edge.y, x.y), step(edge.z, x.z)}};
}
vec4 step(vec4 edge, vec4 x) {
  return {{step(edge.x, x.x), step(edge.y, x.y), step(edge.z, x.z),
           step(edge.w, x.w)}};
}

vec2 step(float edge, vec2 x) { return {{step(edge, x.x), step(edge, x.y)}}; }
vec3 step(float edge, vec3 x) {
  return {{step(edge, x.x), step(edge, x.y), step(edge, x.z)}};
}
vec4 step(float edge, vec4 x) {
  return {{step(edge, x.x), step(edge, x.y), step(edge, x.z), step(edge, x.w)}};
}

float length(float x) { return abs(x); }
float length(vec2 x) { return sqrt(dot(x, x)); }
float length(vec3 x) { return sqrt(dot(x, x)); }
float length(vec4 x) { return sqrt(dot(x, x)); }

float distance(float p0, float p1) { return length(p0 - p1); }
float distance(vec2 p0, vec2 p1) { return length(p0 - p1); }
float distance(vec3 p0, vec3 p1) { return length(p0 - p1); }
float distance(vec4 p0, vec4 p1) { return length(p0 - p1); }

float dot(float x, float y) { return x * y; }
float dot(vec2 x, vec2 y) { return x.x * y.x + x.y * y.y; }
float dot(vec3 x, vec3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }
float dot(vec4 x, vec4 y) {
  return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
}

vec3 cross(vec3 u, vec3 v) {
  return {{
      u.y * v.z - u.z * v.y,  // x
      u.z * v.x - u.x * v.z,  // y
      u.x * v.y - u.y * v.x   // z
  }};
}

float normalize(float) { return 1.0f; }

vec2 normalize(vec2 x) {
  float const s = 1.0f / length(x);
  return s * x;
}
vec3 normalize(vec3 x) {
  float const s = 1.0f / length(x);
  return s * x;
}
vec4 normalize(vec4 x) {
  float const s = 1.0f / length(x);
  return s * x;
}

#undef GRIM_PI
#undef GRIM_DEG2RAD
#undef GRIM_RAD2DEG
#undef GRIM_VEC2F
#undef GRIM_VEC3F
#undef GRIM_VEC4F

#endif  // #ifdef GRIM_MATH_IMPLEMENTATION
