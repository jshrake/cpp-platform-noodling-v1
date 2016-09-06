#ifndef GRIM_INCLUDE_GAME_H
#define GRIM_INCLUDE_GAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;
typedef ptrdiff_t isize;
typedef float f32;
typedef double f64;

#define grim_internal static
#define grim_local_persist static
#define grim_global_variable static

#define bytes(_x) (_x)
#define kilobytes(_x) bytes(_x) * 1024u
#define megabytes(_x) kilobytes(_x) * 1024u
#define gigabytes(_x) megabytes(_x) * 1024u
#define terabytes(_x) gigabytes(_x) * 1024u

#define unused(_x) (void)(_x)

#define assertm(cond, format_str, ...)   \
  do {                                   \
    if (!(cond)) {                       \
      printf(format_str, ##__VA_ARGS__); \
      assert(0);                         \
    }                                    \
  } while (0)

#define countof(a) (sizeof(a) / sizeof((a)[0]))

#define cast(T) (T)

// Keyboard scancodes
// Must map to SDL scancodes
// https://wiki.libsdl.org/SDLScancodeLookup
#define GRIM_KEY_A 4
#define GRIM_KEY_B 5
#define GRIM_KEY_C 6
#define GRIM_KEY_D 7
#define GRIM_KEY_E 8
#define GRIM_KEY_F 9
#define GRIM_KEY_G 10
#define GRIM_KEY_H 11
#define GRIM_KEY_I 12
#define GRIM_KEY_J 13
#define GRIM_KEY_K 14
#define GRIM_KEY_L 15
#define GRIM_KEY_M 16
#define GRIM_KEY_N 17
#define GRIM_KEY_O 18
#define GRIM_KEY_P 19
#define GRIM_KEY_Q 20
#define GRIM_KEY_R 21
#define GRIM_KEY_S 22
#define GRIM_KEY_T 23
#define GRIM_KEY_U 24
#define GRIM_KEY_V 25
#define GRIM_KEY_W 26
#define GRIM_KEY_X 27
#define GRIM_KEY_Y 28
#define GRIM_KEY_Z 29
#define GRIM_KEY_1 30
#define GRIM_KEY_2 31
#define GRIM_KEY_3 32
#define GRIM_KEY_4 33
#define GRIM_KEY_5 34
#define GRIM_KEY_6 35
#define GRIM_KEY_7 36
#define GRIM_KEY_8 37
#define GRIM_KEY_9 38
#define GRIM_KEY_0 39
#define GRIM_KEY_RETURN 40
#define GRIM_KEY_ESCAPE 41
#define GRIM_KEY_BACKSPACE 42
#define GRIM_KEY_TAB 43
#define GRIM_KEY_SPACE 44
#define GRIM_KEY_RIGHT 79
#define GRIM_KEY_LEFT 80
#define GRIM_KEY_DOWN 81
#define GRIM_KEY_UP 82
#define GRIM_KEYBOARD_KEY_COUNT 256

// Mouse buttons
#define GRIM_MOUSE_LEFT 0
#define GRIM_MOUSE_MIDDLE 1
#define GRIM_MOUSE_RIGHT 2
#define GRIM_MOUSE_X1 3
#define GRIM_MOUSE_X2 4
#define GRIM_MOUSE_BUTTON_COUNT 5

typedef struct {
  void *(*read)(char const *filepath);
  void (*read_to_memory)(char const *filepath, void *dest);
  i64 (*size)(char const *filepath);
  void (*close)(void *bytes);
} grim_file_api;

typedef struct {
  void *(*allocate)(u64 bytes);
  void (*deallocate)(void *mem);
} grim_memory_api;

typedef struct {
  grim_file_api file;
  grim_memory_api memory;
  void *(*gl_get_proc_address)(char const *name);
  u8 *(*image_load)(char const *filename, i32 *x, i32 *y, i32 *comp,
                    i32 req_comp);
  void (*image_free)(void *retval_from_load);
} grim_platform_api;

typedef enum {
  GRIM_WINDOW_POSITION_MAX = 0,
  GRIM_WINDOW_POSITION_FULLSCREEN,
  GRIM_WINDOW_POSITION_LEFT,
  GRIM_WINDOW_POSITION_RIGHT,
  GRIM_WINDOW_POSITION_TOP,
  GRIM_WINDOW_POSITION_BOTTOM
} grim_window_position;

typedef struct {
  u64 permanent_storage_bytes;
  u64 frame_storage_bytes;
  char const *window_title;
  grim_window_position window_position;
  i32 multisampling;
} grim_platform_config;

typedef struct {
  u8 *begin;
  u8 *itr;
  u8 *end;
  u8 *stash;
} grim_arena;

grim_internal void grim_arena_init(grim_arena *a, u8 *start, u64 bytes) {
  a->begin = start;
  a->itr = start;
  a->end = start + bytes;
  a->stash = 0;
}

grim_internal u8 *grim_arena_push_bytes(grim_arena *m, u64 bytes) {
  u8 const ok = m->itr + bytes < m->end;
  assertm(ok, "arena out of space");
  u8 *const current = ok ? m->itr : 0;
  m->itr += bytes;
  return current;
}

grim_internal grim_arena *grim_arena_create(grim_arena *src, u64 bytes) {
  u8 *const data = grim_arena_push_bytes(src, sizeof(grim_arena) + bytes);
  grim_arena *a = cast(grim_arena *) data;
  grim_arena_init(a, data, bytes);
  return a;
}

#define grim_arena_stash(m) (m)->stash = (m)->itr
#define grim_arena_stash_pop(m) (m)->itr = (m)->stash
#define grim_arena_clear(m) (m)->itr = (m)->begin;
#define grim_arena_zero(m) memset((m)->begin, 0, (m)->itr - (m)->begin)
#define grim_arena_push(m, T) cast(T *) grim_arena_push_bytes((m), sizeof(T))
#define grim_arena_push_array(m, size, T) \
  cast(T *) grim_arena_push_bytes((m), size * sizeof(T))
#define grim_arena_pop(m, ptr) (m)->itr = ptr;
#define grim_arena_size(m) (m)->itr - (m)->begin
#define grim_arena_capacity(m) (m)->end - (m)->begin

typedef struct {
  u8 key_down[GRIM_KEYBOARD_KEY_COUNT];
  u8 key_event[GRIM_KEYBOARD_KEY_COUNT];
} grim_keyboard_state;

typedef struct {
  u8 key_down[GRIM_MOUSE_BUTTON_COUNT];
  u8 key_event[GRIM_MOUSE_BUTTON_COUNT];
  i32 x, y, z;
} grim_mouse_state;

#define grim_key_pressed(state, key) state.key_down[key] && state.key_event[key]

#define grim_key_down(state, key) state.key_down[key]

#define grim_key_released(state, key) \
  !state.key_down[key] && state.key_event[key]

typedef struct {
  grim_keyboard_state keyboard;
  grim_mouse_state mouse;
} grim_input;

typedef struct {
  grim_arena permanent_storage;
  grim_arena frame_storage;
  grim_input input;
  f64 delta_time;
  f64 total_time;
  u64 frame_count;
  i32 window_width;
  i32 window_height;
} grim_game_state;

#ifdef _WIN32
#define GRIMAPI __declspec(dllexport)
#else
#define GRIMAPI
#endif
/*
 */
GRIMAPI void config(int argc, char *argv[], grim_platform_config *config);

/*
 */
GRIMAPI void init(grim_game_state *state, grim_platform_api *platform);

/*
 */
GRIMAPI i32 tick(grim_game_state *state, grim_platform_api *platform);

/*
 */
GRIMAPI void deinit(grim_game_state *state, grim_platform_api *platform);

/*
 */
GRIMAPI void unload(grim_game_state *state, grim_platform_api *platform);

/*
 */
GRIMAPI void reload(grim_game_state *state, grim_platform_api *platform);

/*
 */
GRIMAPI void resize(grim_game_state *state, grim_platform_api *platform);

#ifdef __cplusplus
}
#endif

#endif  // GRIM_INCLUDE_GAME_H
