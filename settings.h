/**
 * @file settings.h
 * @author Ulf Dellbrügge (xintamosaik@gmail.com)
 * @brief Holds the configuration for the program.
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 * @details This file holds the configuration for the program. It is parsed from
 * a settings file.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <unordered_map>

extern const unsigned int RESOLUTION_WIDTH_MIN;
extern const unsigned int RESOLUTION_WIDTH_MAX;

extern const unsigned int RESOLUTION_HEIGHT_MAX;
extern const unsigned int RESOLUTION_HEIGHT_MIN;

/**
 * @brief Holds the configuration for the graphics.
 *
 */
typedef struct {
  bool full_screen;
  int resolution_width;
  int resolution_height;
  bool vsync;
  int anti_aliasing;
  std::string texture_quality;
  std::string shader_quality;
} ConfigGraphics;

/**
 * @brief Holds the configuration for the audio.
 *
 */
typedef struct {
  int master_volume;
  int music_volume;
  int sfx_volume;
  int voice_volume;
  int ambience_volume;
  bool mute_all;
  std::string audio_output;
} ConfigAudio;

/**
 * @brief Holds the configuration for the controls.
 *
 */
typedef struct {
  int grid_size;
  int show_grid;
  int auto_save_interval;
  int undo_stack_size;
  int default_layer;
  bool snap_to_grid;
  std::string tileset_path;
} ConfigEditorSettings;

extern ConfigGraphics config_graphics;
extern ConfigAudio config_audio;
extern ConfigEditorSettings config_editor_settings;

/**
 * @brief Parses the settings file and stores the values in the config structs.
 *
 * @return bool false if successful, true if not.
 */
bool parse_settings_file(void);

/**
 * @brief Holds a function pointer to a handler for a config key.
 *
 */
typedef void (*ConfigHandler)(const std::string &value);

/**
 * @brief Set the Full Screen object
 *
 * @param value
 */
void setFullScreen(const std::string &value);

/**
 * @brief Set the Resolution Width object
 *
 * @param value
 */
void setResolutionWidth(const std::string &value);

/**
 * @brief Set the Resolution Height object
 *
 * @param value
 */
void setResolutionHeight(const std::string &value);

/**
 * @brief Set the V Sync object
 *
 * @param value
 */
void setVSync(const std::string &value);

/**
 * @brief Set the Anti Aliasing object
 *
 * @param value
 */
void setAntiAliasing(const std::string &value);

/**
 * @brief Set the Texture Quality object
 *
 * @param value
 */
void setTextureQuality(const std::string &value);

/**
 * @brief Set the Shader Quality object
 *
 * @param value
 */
void setShaderQuality(const std::string &value);

/**
 * @brief Set the Master Volume object
 *
 * @param value
 */
void setMasterVolume(const std::string &value);

/**
 * @brief Set the Music Volume object
 *
 * @param value
 */
void setMusicVolume(const std::string &value);

/**
 * @brief Set the SFX Volume object
 *
 * @param value
 */
void setSFXVolume(const std::string &value);

/**
 * @brief Set the Voice Volume object
 *
 * @param value
 */
void setVoiceVolume(const std::string &value);

/**
 * @brief Set the Ambience Volume object
 *
 * @param value
 */
void setAmbienceVolume(const std::string &value);

/**
 * @brief Set the Mute All object
 *
 * @param value
 */
void setMuteAll(const std::string &value);

/**
 * @brief Set the Audio Output object
 *
 * @param value
 */
void setAudioOutput(const std::string &value);

/**
 * @brief Set the Grid Size object
 *
 * @param value
 */
void setGridSize(const std::string &value);

/**
 * @brief Set the Show Grid object
 *
 * @param value
 */
void setShowGrid(const std::string &value);

/**
 * @brief Set the Auto Save Interval object
 *
 * @param value
 */
void setAutoSaveInterval(const std::string &value);

/**
 * @brief Set the Undo Stack Size object
 *
 * @param value
 */
void setUndoStackSize(const std::string &value);

/**
 * @brief Set the Default Layer object
 *
 * @param value
 */
void setDefaultLayer(const std::string &value);

/**
 * @brief Set the Snap To Grid object
 *
 * @param value
 */
void setSnapToGrid(const std::string &value);

/**
 * @brief Set the Tileset Path object
 *
 * @param value
 */
void setTilesetPath(const std::string &value);

/**
 * @brief Holds the key-handler pairs for the settings file.
 *
 * @details This is a map of strings to function pointers. The strings are the
 * keys from the settings file. The function pointers are the handlers for the
 * keys.
 */
extern std::unordered_map<std::string, void (*)(const std::string &)>
    configTable;

#endif // SETTINGS_H