#include "grim_platform.h"
#include <SDL.h>
#include <stdio.h>
#include <string.h>

grim_internal void *memory_allocate(u64 bytes) { return malloc(bytes); }

grim_internal void memory_deallocate(void *mem) { free(mem); }

grim_internal void file_read_to_memory(char const *filepath, void *dest) {
  SDL_RWops *rw = SDL_RWFromFile(filepath, "rb");
  assertm(rw, "Could not open file %s\n", filepath);
  if (rw) {
    i64 const rw_size = SDL_RWsize(rw);
    SDL_RWread(rw, dest, rw_size, 1);
    SDL_RWclose(rw);
  }
}

grim_internal void *file_read(char const *filepath) {
  SDL_RWops *rw = SDL_RWFromFile(filepath, "rb");
  assertm(rw, "Could not open file %s\n", filepath);
  if (rw) {
    i64 const rw_size = SDL_RWsize(rw);
    void *dest = memory_allocate((usize)rw_size);
    SDL_RWread(rw, dest, rw_size, 1);
    SDL_RWclose(rw);
    return dest;
  }
  return 0;
}

grim_internal void file_close(void *bytes) { memory_deallocate(bytes); }

grim_internal i64 file_size(char const *filepath) {
  SDL_RWops *rw = SDL_RWFromFile(filepath, "rb");
  assertm(rw, "Could not open file %s\n", filepath);
  if (rw) {
    i64 const rw_size = SDL_RWsize(rw);
    SDL_RWclose(rw);
    return rw_size;
  }
  return 0;
}

typedef struct {
  grim_platform_config (*config)(int argc, char *argv[]);
  void (*init)(grim_game_state *state, grim_platform_api *platform);
  void (*unload)(grim_game_state *state, grim_platform_api *platform);
  void (*reload)(grim_game_state *state, grim_platform_api *platform);
  int (*tick)(grim_game_state *state, grim_platform_api *platform);
  void (*deinit)(grim_game_state *state, grim_platform_api *platform);
} game_api;

typedef struct {
  game_api api;
  grim_game_state state;
  char const *lib_path;
  void *handle;
#ifdef GRIM_HOT_RELOAD
#ifdef _WIN32
#else
  ino_t last_st_ino;
#endif
#endif
} game;

#ifdef GRIM_HOT_RELOAD
grim_internal grim_platform_config game_config_default(int argc, char *argv[]) {
  unused(argc);
  unused(argv);
  grim_platform_config config;
  memset(&config, 0, sizeof(config));
  return config;
}
grim_internal void game_init_default(grim_game_state *state,
                                     grim_platform_api *platform) {
  unused(state);
  unused(platform);
}
grim_internal void game_unload_default(grim_game_state *state,
                                       grim_platform_api *platform) {
  unused(state);
  unused(platform);
}
grim_internal void game_reload_default(grim_game_state *state,
                                       grim_platform_api *platform) {
  unused(state);
  unused(platform);
}
grim_internal int game_tick_default(grim_game_state *state,
                                    grim_platform_api *platform) {
  unused(state);
  unused(platform);
  return 0;
}
grim_internal void game_deinit_default(grim_game_state *state,
                                       grim_platform_api *platform) {
  unused(state);
  unused(platform);
}
grim_global_variable game_api const default_api = {
    game_config_default, game_init_default, game_unload_default,
    game_reload_default, game_tick_default, game_deinit_default};

#ifdef _WIN32
internal int game_should_reload(game *game) { return game->handle == NULL; }
#else
#include <sys/stat.h>
grim_internal ino_t get_st_ino(char const *path) {
  struct stat stat_attr;
  int const stat_ok = !stat(path, &stat_attr);
  return stat_ok ? stat_attr.st_ino : 0;
}

grim_internal int game_should_reload(game *game) {
  unused(game);
  ino_t const st_ino = get_st_ino(game->lib_path);
  int const should_reload =
      game->handle == NULL || (st_ino != game->last_st_ino);
  game->last_st_ino = st_ino;
  return should_reload;
}
#endif

grim_internal void game_load(game *game) {
  game->api = default_api;
  SDL_UnloadObject(game->handle);
  game->handle = SDL_LoadObject(game->lib_path);
  if (game->handle) {
    game->api.config = (grim_platform_config(*)(int, char *[]))SDL_LoadFunction(
        game->handle, "config");
    if (!game->api.config) {
      game->api.config = game_config_default;
      printf("Warning: %s\n", SDL_GetError());
    }
    game->api.init =
        (void (*)(grim_game_state *, grim_platform_api *))SDL_LoadFunction(
            game->handle, "init");
    if (!game->api.init) {
      game->api.init = game_init_default;
      printf("Warning: %s\n", SDL_GetError());
    }
    game->api.unload =
        (void (*)(grim_game_state *, grim_platform_api *))SDL_LoadFunction(
            game->handle, "unload");
    if (!game->api.unload) {
      game->api.unload = game_unload_default;
      printf("Warning: %s\n", SDL_GetError());
    }
    game->api.reload =
        (void (*)(grim_game_state *, grim_platform_api *))SDL_LoadFunction(
            game->handle, "reload");
    if (!game->api.reload) {
      game->api.reload = game_reload_default;
      printf("Warning: %s\n", SDL_GetError());
    }
    game->api.tick =
        (int (*)(grim_game_state *, grim_platform_api *))SDL_LoadFunction(
            game->handle, "tick");
    if (!game->api.tick) {
      game->api.tick = game_tick_default;
      printf("Warning: %s\n", SDL_GetError());
    }
    game->api.deinit =
        (void (*)(grim_game_state *, grim_platform_api *))SDL_LoadFunction(
            game->handle, "deinit");
    if (!game->api.deinit) {
      game->api.deinit = game_deinit_default;
      printf("Warning: %s\n", SDL_GetError());
    }
    SDL_ClearError();
  } else {
    // TODO(jshrake): handle LoadObject error
    printf("Error: %s\n", SDL_GetError());
  }
}
#else
internal void game_load(game *game) {
  game->api.config = &config;
  game->api.init = &init;
  game->api.tick = &tick;
  game->api.deinit = &deinit;
  game->api.unload = &unload;
  game->api.reload = &reload;
}
#endif  // GRIM_HOT_RELOAD

int main(int argc, char *argv[]) {
  game game;
  memset(&game, 0, sizeof(game));
  game.lib_path = argv[1];
  game_load(&game);
  grim_platform_config const config = game.api.config(argc - 2, argv + 2);
  u8 *const memory = cast(u8 *)
      calloc(1, config.permanent_storage_bytes + config.frame_storage_bytes);
  grim_arena_init(&game.state.permanent_storage, memory,
                  config.permanent_storage_bytes);
  grim_arena_init(&game.state.frame_storage,
                  memory + config.permanent_storage_bytes,
                  config.frame_storage_bytes);
  int const sdl_init_ok = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  assertm(sdl_init_ok == 0, "Error: %s\n", SDL_GetError());
  SDL_DisplayMode display_mode;
  i32 display_mode_ok = SDL_GetCurrentDisplayMode(0, &display_mode);
  assertm(display_mode_ok == 0, "Error: %s\n", SDL_GetError());
  i32 window_x = SDL_WINDOWPOS_CENTERED;
  i32 window_y = SDL_WINDOWPOS_CENTERED;
  i32 window_w = display_mode.w;
  i32 window_h = display_mode.h;
  u32 window_flags =
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
  switch (config.window_position) {
    case GRIM_WINDOW_POSITION_RIGHT: {
      window_x = cast(i32)(0.5 * display_mode.w);
      window_y = 0;
      window_w = cast(i32)(0.5 * display_mode.w);
      window_h = display_mode.h;
      break;
    }
    case GRIM_WINDOW_POSITION_LEFT: {
      window_x = 0;
      window_y = 0;
      window_w = cast(i32)(0.5 * display_mode.w);
      window_h = display_mode.h;
      break;
    }
    case GRIM_WINDOW_POSITION_TOP: {
      window_x = 0;
      window_y = 0;
      window_w = display_mode.w;
      window_h = cast(i32)(0.5 * display_mode.h);
      break;
    }
    case GRIM_WINDOW_POSITION_BOTTOM: {
      window_x = 0;
      window_y = cast(i32)(0.5 * display_mode.h);
      window_w = display_mode.w;
      window_h = cast(i32)(0.5 * display_mode.h);
      break;
    }
    case GRIM_WINDOW_POSITION_FULLSCREEN: {
      window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
      break;
    }
    case GRIM_WINDOW_POSITION_MAX: {
      window_flags |= SDL_WINDOW_MAXIMIZED;
      break;
    }
  }

  SDL_Window *const window =
      SDL_CreateWindow(config.window_title, window_x, window_y, window_w,
                       window_h, window_flags);
  assertm(window, "Error: %s\n", SDL_GetError());
  // TODO(jshrake): Query the hardware and make sure we can support the
  // following
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, config.multisampling ? 1 : 0);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, config.multisampling);
  SDL_GLContext const context = SDL_GL_CreateContext(window);
  assertm(context, "Error: %s\n", SDL_GetError());
  SDL_GL_MakeCurrent(window, context);
  grim_platform_api platform_api;
  platform_api.file.read = &file_read;
  platform_api.file.read_to_memory = &file_read_to_memory;
  platform_api.file.close = &file_close;
  platform_api.file.size = &file_size;
  // memory
  platform_api.memory.allocate = &memory_allocate;
  platform_api.memory.deallocate = &memory_deallocate;
  // loose
  platform_api.gl_get_proc_address = &SDL_GL_GetProcAddress;
  game.api.init(&game.state, &platform_api);
  // NOTE(jshrake): This function has a side-effect that sets the last timestamp
  // so... do something about this bit of ugly
  game_should_reload(&game);
  int game_running = 1;
  u64 const counts_per_sec = SDL_GetPerformanceFrequency();
  u64 const start = SDL_GetPerformanceCounter();
  u64 current = start;

  while (game_running) {
#ifdef GRIM_HOT_RELOAD
    if (game_should_reload(&game)) {
      printf("Reloading %s\n", game.lib_path);
      game.api.unload(&game.state, &platform_api);
      game_load(&game);
      game.api.reload(&game.state, &platform_api);
    }
#endif  // GRIM_HOT_RELOAD
    game.state.frame_count += 1;
    u64 const next = SDL_GetPerformanceCounter();
    game.state.delta_time = (next - current) / (f64)(counts_per_sec);
    game.state.total_time = (next - start) / (f64)(counts_per_sec);
    SDL_GetWindowSize(window, &game.state.window_width,
                      &game.state.window_height);
    // update inputs
    // Handle discrete events
    memset(&game.state.input.keyboard.key_event, 0, GRIM_KEYBOARD_KEY_COUNT);
    memset(&game.state.input.mouse.key_event, 0, GRIM_MOUSE_BUTTON_COUNT);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          game_running = 0;
          break;
        }
        case SDL_WINDOWEVENT: {
          switch (event.window.type) {
            default:
              break;
          }
          break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
          i32 const scancode = event.key.keysym.scancode;
          assertm(scancode < GRIM_KEYBOARD_KEY_COUNT,
                  "larger than expected scancode");
          game.state.input.keyboard.key_event[scancode] += 1;
          game.state.input.keyboard.key_down[scancode] =
              event.type == SDL_KEYDOWN;
          break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
          u8 const button = event.button.button - 1;
          assertm(button < GRIM_MOUSE_BUTTON_COUNT,
                  "larger than expected mouse button id\n");
          game.state.input.mouse.key_event[button] += event.button.clicks;
          game.state.input.mouse.key_down[button] =
              event.type == SDL_MOUSEBUTTONDOWN;
          break;
        }
        default: { break; }
      }
    }
    // Update mouse state
    SDL_GetMouseState(&game.state.input.mouse.x, &game.state.input.mouse.y);
    game_running &= !game.api.tick(&game.state, &platform_api);
    SDL_GL_SwapWindow(window);
    current = next;
  }
  game.api.deinit(&game.state, &platform_api);
  return 0;
}
