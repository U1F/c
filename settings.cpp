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

const unsigned int RESOLUTION_WIDTH_MIN = 800;
const unsigned int RESOLUTION_WIDTH_MAX = 1920;

const unsigned int RESOLUTION_HEIGHT_MIN = 600;
const unsigned int RESOLUTION_HEIGHT_MAX = 1080;

ConfigGraphics config_graphics;
ConfigAudio config_audio;
ConfigEditorSettings config_editor_settings;

std::unordered_map<std::string, void (*)(const std::string &)> configTable = {
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

void setFullScreen(const std::string &value) {
  config_graphics.full_screen = value == "true";
}

unsigned int clamp(unsigned int value, unsigned int min, unsigned int max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

void setResolutionWidth(const std::string &value) {
  unsigned int atoi_value = std::stoi(value);
  config_graphics.resolution_width =
      clamp(atoi_value, RESOLUTION_WIDTH_MIN, RESOLUTION_WIDTH_MAX);
}

void setResolutionHeight(const std::string &value) {
  unsigned int atoi_value = std::stoi(value);
  config_graphics.resolution_height =
      clamp(atoi_value, RESOLUTION_HEIGHT_MIN, RESOLUTION_HEIGHT_MAX);
}

void setVSync(const std::string &value) {
  config_graphics.vsync = value == "true";
}

void setAntiAliasing(const std::string &value) {
  config_graphics.anti_aliasing = std::stoi(value);
}

void setTextureQuality(const std::string &value) {
  config_graphics.texture_quality = value;
}

void setShaderQuality(const std::string &value) {
  config_graphics.shader_quality = value;
}

void setMasterVolume(const std::string &value) {
  config_audio.master_volume = std::stoi(value);
}

void setMusicVolume(const std::string &value) {
  config_audio.music_volume = std::stoi(value);
}

void setSFXVolume(const std::string &value) {
  config_audio.sfx_volume = std::stoi(value);
}

void setVoiceVolume(const std::string &value) {
  config_audio.voice_volume = std::stoi(value);
}

void setAmbienceVolume(const std::string &value) {
  config_audio.ambience_volume = std::stoi(value);
}

void setMuteAll(const std::string &value) {
  config_audio.mute_all = value == "true";
}

void setAudioOutput(const std::string &value) {
  config_audio.audio_output = value;
}

void setGridSize(const std::string &value) {
  config_editor_settings.grid_size = std::stoi(value);
}

void setShowGrid(const std::string &value) {
  config_editor_settings.show_grid = value == "true";
}

void setAutoSaveInterval(const std::string &value) {
  config_editor_settings.auto_save_interval = std::stoi(value);
}

void setUndoStackSize(const std::string &value) {
  config_editor_settings.undo_stack_size = std::stoi(value);
}

void setDefaultLayer(const std::string &value) {
  config_editor_settings.default_layer = std::stoi(value);
}

void setSnapToGrid(const std::string &value) {
  config_editor_settings.snap_to_grid = value == "true";
}

void setTilesetPath(const std::string &value) {
  config_editor_settings.tileset_path = value;
}

bool parse_settings_file() {
  std::ifstream file("settings.ini");
  if (!file.is_open()) {
    std::cout << "Could not open file.\n";
    return true;
  }

  std::string line;
  while (std::getline(file, line)) {

    if (line.empty() || line[0] == '[' ) {
      continue;
    }

    std::string key, value;
    std::istringstream iss(line);
    if (std::getline(iss, key, '=') && std::getline(iss, value)) {
      auto it = configTable.find(key);
      if (it != configTable.end()) {
        it->second(value);
      }
    }
  }

  return false;
}
