#include "grim_game.h"
#define GRIM_GL_IMPLEMENTATION
#include "grim_gl.h"

grim_platform_config config(int argc, char *argv[]) {
  grim_platform_config config = {};
  config.window_title = "GRIM_NAME";
  config.window_position = GRIM_WINDOW_POSITION_RIGHT;
  config.permanent_storage_bytes = megabytes(8);
  config.frame_storage_bytes = megabytes(64);
  config.multisampling = 8;
  return config;
}

void init(grim_game_state *state, grim_platform_api *platform) {}

void deinit(grim_game_state *state, grim_platform_api *platform) {}

void unload(grim_game_state *state, grim_platform_api *platform) {}

void reload(grim_game_state *state, grim_platform_api *platform) {}

int tick(grim_game_state *state, grim_platform_api *platform) {
  glClear(GL_COLOR_BUFFER_BIT);
  grim_arena_clear(&state->frame_storage);
  return grim_key_pressed(state->input.keyboard, GRIM_KEY_ESCAPE);
}
