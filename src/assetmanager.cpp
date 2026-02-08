#include "assetmanager.hpp"
#include <format>

namespace fs = std::filesystem;

AssetManager::AssetManager(const fs::path &base_path)
    : m_base_path{base_path}, m_textures{} {}

AssetManager::~AssetManager() {
  for (auto &[_, texture] : m_textures) {
    SDL_DestroyTexture(texture);
  }
}

void AssetManager::add_asset(SDL_Renderer *renderer,
                             std::string_view img_name) {

  fs::path img_path = m_base_path / img_name;

  if (!fs::is_regular_file(img_path)) {
    throw std::runtime_error(
        std::format("ERROR: {} Does not exist!", img_path.c_str()));
  }

  SDL_Surface *img_surface = SDL_LoadPNG(img_path.c_str());
  if (!img_surface) {
    throw std::runtime_error(std::format("ERROR: Failed to load {}: {}",
                                         img_path.c_str(), SDL_GetError()));
  }

  SDL_Texture *img_texture =
      SDL_CreateTextureFromSurface(renderer, img_surface);

  if (!img_texture) {
    SDL_DestroySurface(img_surface);
    throw std::runtime_error(
        std::format("ERROR: Failed to create texture from {}: {}",
                    img_path.c_str(), SDL_GetError()));
  }

  m_textures.insert({std::string(img_name), img_texture});

  SDL_DestroySurface(img_surface);
}

SDL_Texture *AssetManager::get_asset(const std::string &name) {
  auto it = m_textures.find(name);

  if(it == m_textures.end()) {
    throw std::runtime_error(std::format("Failed to find texture with name: {}", name));
  }

  return it->second;
}
