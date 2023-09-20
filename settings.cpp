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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

const unsigned int RESOLUTION_WIDTH_MIN = 800;
const unsigned int RESOLUTION_WIDTH_MAX = 1920;

const unsigned int RESOLUTION_HEIGHT_MIN = 600;
const unsigned int RESOLUTION_HEIGHT_MAX = 1080;

ConfigGraphics config_graphics;
ConfigAudio config_audio;
ConfigEditorSettings config_editor_settings;

ConfigTableType config_table = {
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

void setFullScreen(const string &value) {
  config_graphics.full_screen = value == "true";
}

unsigned int clamp(unsigned int value, unsigned int min, unsigned int max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

void setResolutionWidth(const string &value) {
  unsigned int atoi_value = stoi(value);
  config_graphics.resolution_width =
      clamp(atoi_value, RESOLUTION_WIDTH_MIN, RESOLUTION_WIDTH_MAX);
}

void setResolutionHeight(const string &value) {
  unsigned int atoi_value = stoi(value);
  config_graphics.resolution_height =
      clamp(atoi_value, RESOLUTION_HEIGHT_MIN, RESOLUTION_HEIGHT_MAX);
}

void setVSync(const string &value) {
  config_graphics.vsync = value == "true";
}

void setAntiAliasing(const string &value) {
  config_graphics.anti_aliasing = stoi(value);
}

void setTextureQuality(const string &value) {
  config_graphics.texture_quality = value;
}

void setShaderQuality(const string &value) {
  config_graphics.shader_quality = value;
}

void setMasterVolume(const string &value) {
  config_audio.master_volume = stoi(value);
}

void setMusicVolume(const string &value) {
  config_audio.music_volume = stoi(value);
}

void setSFXVolume(const string &value) {
  config_audio.sfx_volume = stoi(value);
}

void setVoiceVolume(const string &value) {
  config_audio.voice_volume = stoi(value);
}

void setAmbienceVolume(const string &value) {
  config_audio.ambience_volume = stoi(value);
}

void setMuteAll(const string &value) {
  config_audio.mute_all = value == "true";
}

void setAudioOutput(const string &value) {
  config_audio.audio_output = value;
}

void setGridSize(const string &value) {
  config_editor_settings.grid_size = stoi(value);
}

void setShowGrid(const string &value) {
  config_editor_settings.show_grid = value == "true";
}

void setAutoSaveInterval(const string &value) {
  config_editor_settings.auto_save_interval = stoi(value);
}

void setUndoStackSize(const string &value) {
  config_editor_settings.undo_stack_size = stoi(value);
}

void setDefaultLayer(const string &value) {
  config_editor_settings.default_layer = stoi(value);
}

void setSnapToGrid(const string &value) {
  config_editor_settings.snap_to_grid = value == "true";
}

void setTilesetPath(const string &value) {
  config_editor_settings.tileset_path = value;
}

bool parse_settings_file() {
  ifstream file("settings.ini");
  if (!file.is_open()) {
    cout << "Could not open file.\n";
    return true;
  }

  string line;
  while (getline(file, line)) {

    if (line.empty() || line[0] == '[' ) {
      continue;
    }

    string key, value;
    istringstream iss(line);
    if (getline(iss, key, '=') && getline(iss, value)) {
      auto it = config_table.find(key);
      if (it != config_table.end()) {
        it->second(value);
      }
    }
  }

  return false;
}
