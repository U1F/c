/**
 * @file settings.c
 * @author Ulf Dellbrügge (xintamosaik@gmail.com)
 * @brief Holds the configuration for the program.
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright (c) 2023
 *
 * @details This file holds the configuration for the program. It is parsed from
 * a settings file.
 */

#include "settings.h"
#include "sdltest.h"
#include <errno.h>


const unsigned int RESOLUTION_WIDTH_MIN = 800;
const unsigned int RESOLUTION_WIDTH_MAX = 1920;

const unsigned int RESOLUTION_HEIGHT_MIN = 600;
const unsigned int RESOLUTION_HEIGHT_MAX = 1080;

ConfigGraphics config_graphics;
ConfigAudio config_audio;
ConfigEditorSettings config_editor_settings;

ConfigKeyHandlerPair configTable[] = {
    {"FullScreen", setFullScreen},
    {"ResolutionWidth", setResolutionWidth},
    {"ResolutionHeight", setResolutionHeight},
    {"VSync", setVSync},
    {"AntiAliasing", setAntiAliasing},
    {"TextureQuality", setTextureQuality},
    {"ShaderQuality", setShaderQuality},
    {"MasterVolume", setMasterVolume},
    {"MusicVolume", setMusicVolume},
    {"SFXVolume", setSFXVolume},
    {"VoiceVolume", setVoiceVolume},
    {"AmbienceVolume", setAmbienceVolume},
    {"MuteAll", setMuteAll},
    {"AudioOutput", setAudioOutput},
    {"GridSize", setGridSize},
    {"ShowGrid", setShowGrid},
    {"AutoSaveInterval", setAutoSaveInterval},
    {"UndoStackSize", setUndoStackSize},
    {"DefaultLayer", setDefaultLayer},
    {"SnapToGrid", setSnapToGrid},
    {"TilesetPath", setTilesetPath},
};

void setFullScreen(const char *value) {
  config_graphics.full_screen = strcmp(value, "true") == 0;
}

unsigned int safeAtoi(const char *value) {
  char *endptr;
  long conv_value = strtol(value, &endptr, 10);

  if (endptr == value || *endptr != '\0' || errno == ERANGE) {
    return 0;
  }
  
  return (unsigned int)conv_value;
}

unsigned int clamp(unsigned int value, unsigned int min, unsigned int max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

void setResolutionWidth(const char *value) {
  unsigned int atoi_value = safeAtoi(value);
  config_graphics.resolution_width = clamp(atoi_value, RESOLUTION_WIDTH_MIN, RESOLUTION_WIDTH_MAX);
}

void setResolutionHeight(const char *value) {
  unsigned int atoi_value = safeAtoi(value);
  config_graphics.resolution_height = clamp(atoi_value, RESOLUTION_HEIGHT_MIN, RESOLUTION_HEIGHT_MAX);
}

void setVSync(const char *value) {
  config_graphics.vsync = strcmp(value, "true") == 0;
}

void setAntiAliasing(const char *value) {
  config_graphics.anti_aliasing = safeAtoi(value);
}

void setTextureQuality(const char *value) {
  config_graphics.texture_quality = strdup(value);
}

void setShaderQuality(const char *value) {
  config_graphics.shader_quality = strdup(value);
}

void setMasterVolume(const char *value) {
  config_audio.master_volume = safeAtoi(value);
}

void setMusicVolume(const char *value) {
  config_audio.music_volume = safeAtoi(value);
}

void setSFXVolume(const char *value) { 
  config_audio.sfx_volume = safeAtoi(value); 
}

void setVoiceVolume(const char *value) {
  config_audio.voice_volume = safeAtoi(value);
}

void setAmbienceVolume(const char *value) {
  config_audio.ambience_volume = safeAtoi(value);
}

void setMuteAll(const char *value) {
  config_audio.mute_all = strcmp(value, "true") == 0;
}

void setAudioOutput(const char *value) {
  config_audio.audio_output = strdup(value);
}

void setGridSize(const char *value) {
  config_editor_settings.grid_size = safeAtoi(value);
}

void setShowGrid(const char *value) {
  config_editor_settings.show_grid = strcmp(value, "true") == 0;
}

void setAutoSaveInterval(const char *value) {
  config_editor_settings.auto_save_interval = safeAtoi(value);
}

void setUndoStackSize(const char *value) {
  config_editor_settings.undo_stack_size = safeAtoi(value);
}

void setDefaultLayer(const char *value) {
  config_editor_settings.default_layer = safeAtoi(value);
}

void setSnapToGrid(const char *value) {
  config_editor_settings.snap_to_grid = strcmp(value, "true") == 0;
}

void setTilesetPath(const char *value) {
  config_editor_settings.tileset_path = strdup(value);
}

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

    size_t tableSize = sizeof(configTable) / sizeof(ConfigKeyHandlerPair);
    if (key && value) {
      for (size_t i = 0; i < tableSize; i++) {
        if (strcmp(key, configTable[i].key) == 0) {
          configTable[i].handler(value);
          break;
        }
      }
    }
  }

  fclose(file);
  return 0;
} // End of: parse_settings_file function
