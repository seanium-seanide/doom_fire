#include <print>
#include <array>
#include <mdspan>
#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <SDL3/SDL.h>

using namespace std::string_view_literals;

// Constants
constexpr auto FRAME_RATE_FPS{60.0}; // Frames per second
constexpr auto FRAME_TIME_S{1.0 / FRAME_RATE_FPS}; // Seconds per frame

// VGA mode 13h
static constexpr auto WIN_WIDTH{320};
static constexpr auto WIN_HEIGHT{200};
static constexpr auto WIN_SIZE{WIN_WIDTH * WIN_HEIGHT};
static constexpr auto WIN_TITLE{"SDL3 Pixels"sv};

// Framebuffer
using size_type = std::size_t;
using data_type = std::uint32_t;
using FramebufferExtentsType = std::extents<size_type, WIN_WIDTH, WIN_HEIGHT>;
using FramebufferSpanType = std::mdspan<data_type, FramebufferExtentsType, std::layout_left>;
std::array<data_type, WIN_SIZE> g_framebufferData{};
FramebufferSpanType g_framebufferView{g_framebufferData.data()};

// Window and renderer
SDL_Window* g_window{};
SDL_Renderer* g_renderer{};

// Textures
SDL_Texture* g_framebufferTexture{};


void clearBuffer(std::span<uint32_t> buffer, uint32_t color);


int main()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::println("SDL_Init: Failed to initialize SDL video subsystem");
    exit(1);
  }

  g_window = SDL_CreateWindow(
    WIN_TITLE.data()
  , WIN_WIDTH * 4
  , WIN_HEIGHT * 4
  , 0
  );

  if (g_window == nullptr)
  {
    std::println("SDL_CreateWindow: Failed to create SDL window");

    SDL_Quit();

    exit(1);
  }

  g_renderer = SDL_CreateRenderer(g_window, nullptr);

  if (g_renderer == nullptr)
  {
    std::println("SDL_CreateRenderer: Failed to create SDL renderer");

    SDL_DestroyWindow(g_window);
    SDL_Quit();

    exit(1);
  }

  g_framebufferTexture = SDL_CreateTexture(
    g_renderer
  , SDL_PIXELFORMAT_XRGB8888
  , SDL_TEXTUREACCESS_STREAMING
  , WIN_WIDTH
  , WIN_HEIGHT
  );

  SDL_SetTextureScaleMode(g_framebufferTexture, SDL_SCALEMODE_NEAREST);

  //uint32_t linearIndex{16500};
  //uint32_t i{linearIndex % WIN_WIDTH};
  //uint32_t j{linearIndex / WIN_WIDTH};

  //std::println("i: {}", i);
  //std::println("j: {}", j);
  //std::fflush(stdout);

  //g_framebufferData[linearIndex] = 0xFF0000;
  //g_framebufferData[j * WIN_WIDTH + i] = 0xFF0000;
  //g_framebufferView[i, j] = 0xFF0000;

  clearBuffer(g_framebufferData, 0xFFFFFF);

  for (std::size_t j{}; j < g_framebufferView.extent(1); ++j)
  {
    for (std::size_t i{}; i < g_framebufferView.extent(0); ++i)
    {
      if (i % 5 == 0)
      {
        g_framebufferView[i, j] = 0x00FFFF;
      }
    }
  }

  bool running = true;

  while (running)
  {
    auto frameStartCounts{SDL_GetPerformanceCounter()};

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
      {
        running = false;
        break;
      }

      case SDL_EVENT_KEY_DOWN:
      {
        if (event.key.key == SDLK_ESCAPE)
        {
          running = false;
        }

        break;
      }

      default:
      {
        break;
      }
      }
    }

    SDL_UpdateTexture(
      g_framebufferTexture
    , nullptr
    , g_framebufferData.data()
    , WIN_WIDTH * sizeof(uint32_t)
    );

    SDL_RenderClear(g_renderer);
    SDL_RenderTexture(g_renderer, g_framebufferTexture, nullptr, nullptr);
    SDL_RenderPresent(g_renderer);

    auto frameEndCounts{SDL_GetPerformanceCounter()};
    auto frameElapsedTime_s{static_cast<double>(frameEndCounts - frameStartCounts) / static_cast<double>(SDL_GetPerformanceFrequency())};
    if (frameElapsedTime_s < FRAME_TIME_S)
    {
      SDL_Delay((FRAME_TIME_S - frameElapsedTime_s) * 1000.0);
    }
  }

  SDL_DestroyTexture(g_framebufferTexture);
  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);
  SDL_Quit();

  return 0;
}


void clearBuffer(std::span<uint32_t> buffer, uint32_t color)
{
  std::memset(buffer.data(), color, buffer.size() * sizeof(uint32_t));
}
