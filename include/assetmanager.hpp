#pragma once
#include "SDL3/SDL_render.h"
#include <filesystem>
#include <unordered_map>

class AssetManager {
public:
  AssetManager(const std::filesystem::path &base_path);
  ~AssetManager();

  void add_asset(SDL_Renderer *renderer,
                 std::string_view img_name) noexcept(false);

  SDL_Texture *get_asset(const std::string &name);

private:
  std::filesystem::path m_base_path;
  std::unordered_map<std::string, SDL_Texture *> m_textures;
};
