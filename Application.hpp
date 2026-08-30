#pragma once

#include <types.hpp>
#include <constants.hpp>
#include <cstdlib>
#include <SDL3/SDL.h>


namespace doom_fire
{

class Application
{
public:
  Application() = default;

  int main();

  void init();
  void quit();
  void input();
  void update();
  void render();
  void draw();
  void timingStart();
  void timingEnd();
  void setPixel(std::size_t i, std::size_t j, uint32_t color);

private:
  SDL_Window* m_window{};
  SDL_Renderer* m_renderer{};
  SDL_Texture* m_framebufferTexture{};
  bool m_running{};

  types::FramebufferType m_framebufferData{};
  types::FramebufferSpanType m_framebufferView{m_framebufferData.data()};
  types::FireType m_fireData{};
  types::FireSpanType m_fireView{m_fireData.data()};

  uint64_t m_frameStartCounts{};
  uint64_t m_frameEndCounts{};
  double m_frameElapsedTime_s{};
};

} // namespace doom_fire
