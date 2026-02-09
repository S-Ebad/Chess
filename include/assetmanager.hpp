#pragma once
#include "SDL3/SDL_render.h"
#include <filesystem>
#include <unordered_map>

class AssetManager {
public:
  AssetManager(const std::filesystem::path &base_path);
  ~AssetManager();

  void load_asset(SDL_Renderer *renderer, const std::string &img_name);

  SDL_Texture *get_asset(const std::string &name);

private:
  std::filesystem::path m_base_path;
  std::unordered_map<std::string, SDL_Texture *> m_textures;
};
