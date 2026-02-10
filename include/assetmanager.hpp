#pragma once
#include "SDL3/SDL_render.h"
#include <filesystem>
#include <unordered_map>

class AssetManager {
public:
  AssetManager(const std::filesystem::path &base_path);
  ~AssetManager();

  void load_asset(SDL_Renderer *renderer, const std::string_view &img_name, char key);

  SDL_Texture *get_asset(const char key) const;

private:
  std::filesystem::path m_base_path;
  std::unordered_map<char, SDL_Texture *> m_textures;
};
