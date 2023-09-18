
/**
 * @brief Holds the configuration for the graphics.
 *
 */
typedef struct {
  int full_screen;
  int resolution_width;
  int resolution_height;
  int vsync;
  int anti_aliasing;
  char *texture_quality;
  char *shader_quality;
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
  int mute_all;
  char *audio_output;
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
  int snap_to_grid;
  char *tileset_path;
} ConfigEditorSettings;

extern ConfigGraphics config_graphics;
extern ConfigAudio config_audio;
extern ConfigEditorSettings config_editor_settings;

/**
 * @brief Parses the settings file and stores the values in the config structs.
 *
 * @return int 0 if successful, 1 if not.
 */
int parse_settings_file();
