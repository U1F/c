#include "settings.h"
#include "sdltest.h"

ConfigGraphics config_graphics;
ConfigAudio config_audio;
ConfigEditorSettings config_editor_settings;

int parse_settings_file() {
  FILE *file = fopen("settings.ini", "r");
  if (file == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  char line[256];
  char *key, *value;
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '[' || line[0] == '\n') {
      continue; // Skip sections and empty lines
    }

    key = strtok(line, "=");
    value = strtok(NULL, "\n");

    if (key && value) {
      printf("Key: %s, Value: %s\n", key, value);
      if (strcmp(key, "FullScreen") == 0) {
        printf("FullScreen: %s\n", value);
        config_graphics.full_screen = strcmp(value, "true") == 0;
      } else if (strcmp(key, "ResolutionWidth") == 0) {
        config_graphics.resolution_width = atoi(value);
      } else if (strcmp(key, "ResolutionHeight") == 0) {
        config_graphics.resolution_height = atoi(value);
      } else if (strcmp(key, "VSync") == 0) {
        config_graphics.vsync = strcmp(value, "true") == 0;
      } else if (strcmp(key, "AntiAliasing") == 0) {
        config_graphics.anti_aliasing = atoi(value);
      } else if (strcmp(key, "TextureQuality") == 0) {
        config_graphics.texture_quality = strdup(value);
      } else if (strcmp(key, "ShaderQuality") == 0) {
        config_graphics.shader_quality = strdup(value);
      } else if (strcmp(key, "MasterVolume") == 0) {
        config_audio.master_volume = atoi(value);
      } else if (strcmp(key, "MusicVolume") == 0) {
        config_audio.music_volume = atoi(value);
      } else if (strcmp(key, "SFXVolume") == 0) {
        config_audio.sfx_volume = atoi(value);
      } else if (strcmp(key, "VoiceVolume") == 0) {
        config_audio.voice_volume = atoi(value);
      } else if (strcmp(key, "AmbienceVolume") == 0) {
        config_audio.ambience_volume = atoi(value);
      } else if (strcmp(key, "MuteAll") == 0) {
        config_audio.mute_all = strcmp(value, "true") == 0;
      } else if (strcmp(key, "AudioOutput") == 0) {
        config_audio.audio_output = strdup(value);
      } else if (strcmp(key, "GridSize") == 0) {
        config_editor_settings.grid_size = atoi(value);
      } else if (strcmp(key, "ShowGrid") == 0) {
        config_editor_settings.show_grid = strcmp(value, "true") == 0;
      } else if (strcmp(key, "AutoSaveInterval") == 0) {
        config_editor_settings.auto_save_interval = atoi(value);
      } else if (strcmp(key, "UndoStackSize") == 0) {
        config_editor_settings.undo_stack_size = atoi(value);
      } else if (strcmp(key, "DefaultLayer") == 0) {
        config_editor_settings.default_layer = atoi(value);
      } else if (strcmp(key, "SnapToGrid") == 0) {
        config_editor_settings.snap_to_grid = strcmp(value, "true") == 0;
      } else if (strcmp(key, "TilesetPath") == 0) {
        config_editor_settings.tileset_path = strdup(value);
      }
    }
  }

  fclose(file);
  return 0;
} // End of: parse_settings_file function
