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

const unsigned int RESOLUTION_WIDTH_MIN = 800;
const unsigned int RESOLUTION_HEIGHT_MIN = 600;
const unsigned int RESOLUTION_WIDTH_MAX = 1920;
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

void setResolutionWidth(const char *value) {
  unsigned int atoi_value = atoi(value);
  if (atoi_value < RESOLUTION_WIDTH_MIN) {
    config_graphics.resolution_width = RESOLUTION_WIDTH_MIN;
  } else if (atoi_value > RESOLUTION_WIDTH_MAX) {
    config_graphics.resolution_width = RESOLUTION_WIDTH_MAX;
  } else {
    config_graphics.resolution_width = atoi_value;
  }
}

void setResolutionHeight(const char *value) {
  unsigned int atoi_value = atoi(value);
  if (atoi_value < RESOLUTION_HEIGHT_MIN) {
    config_graphics.resolution_height = RESOLUTION_HEIGHT_MIN;
  } else if (atoi_value > RESOLUTION_HEIGHT_MAX) {
    config_graphics.resolution_height = RESOLUTION_HEIGHT_MAX;
  } else {
    config_graphics.resolution_height = atoi_value;
  }
}

void setVSync(const char *value) {
  config_graphics.vsync = strcmp(value, "true") == 0;
}

void setAntiAliasing(const char *value) {
  config_graphics.anti_aliasing = atoi(value);
}

void setTextureQuality(const char *value) {
  config_graphics.texture_quality = strdup(value);
}

void setShaderQuality(const char *value) {
  config_graphics.shader_quality = strdup(value);
}

void setMasterVolume(const char *value) {
  config_audio.master_volume = atoi(value);
}

void setMusicVolume(const char *value) {
  config_audio.music_volume = atoi(value);
}

void setSFXVolume(const char *value) { config_audio.sfx_volume = atoi(value); }

void setVoiceVolume(const char *value) {
  config_audio.voice_volume = atoi(value);
}

void setAmbienceVolume(const char *value) {
  config_audio.ambience_volume = atoi(value);
}

void setMuteAll(const char *value) {
  config_audio.mute_all = strcmp(value, "true") == 0;
}

void setAudioOutput(const char *value) {
  config_audio.audio_output = strdup(value);
}

void setGridSize(const char *value) {
  config_editor_settings.grid_size = atoi(value);
}

void setShowGrid(const char *value) {
  config_editor_settings.show_grid = strcmp(value, "true") == 0;
}

void setAutoSaveInterval(const char *value) {
  config_editor_settings.auto_save_interval = atoi(value);
}

void setUndoStackSize(const char *value) {
  config_editor_settings.undo_stack_size = atoi(value);
}

void setDefaultLayer(const char *value) {
  config_editor_settings.default_layer = atoi(value);
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
