#include <Application.hpp>
#include <print>
#include <random>
#include <utilities.hpp>


namespace doom_fire
{

int Application::main()
{
  init();

  while (m_running)
  {
    timingStart();

    input();
    update();
    render();

    timingEnd();
  }

  quit();

  return 0;
}


void Application::update()
{
  static std::random_device rd{};
  static std::mt19937 mt{rd()};

  static std::uniform_int_distribution horizontalShiftDist{-1, 1};
  static auto randHorizontalShift = []() { return horizontalShiftDist(mt); };

  static std::uniform_int_distribution paletteIndexShiftDist{0, 1};
  static auto randPaletteIndexShift = []() { return paletteIndexShiftDist(mt); };

  // Initiate
  for (int i{}; i < common::WIN_WIDTH; ++i)
  {
    if (m_fireOn)
    {
      m_fireView[i, common::FIRE_HEIGHT - 1] = m_heatingElementIntensity;
    }
    else
    {
      if (m_fireView[i, common::FIRE_HEIGHT - 1] > 0)
      {
        --m_fireView[i, common::FIRE_HEIGHT - 1];
      }
    }
  }

  // Propagate
  for (int j{1}; j < common::FIRE_HEIGHT; ++j)
  {
    for (int i{}; i < common::WIN_WIDTH; ++i)
    {
      auto I = utilities::clamp(
        static_cast<int>(i + randHorizontalShift())
      , 0
      , static_cast<int>(m_framebufferView.extent(0)) - 1
      );

      auto intensity = utilities::clamp(
        static_cast<int>(m_fireView[I, j-1] = m_fireView[i, j]) - randPaletteIndexShift()
      , 0
      , static_cast<int>(constants::PALETTE_SIZE) - 1
      );

      m_fireView[I, j-1] = intensity;
    }
  }
}


void Application::render()
{
  draw();

  SDL_UpdateTexture(
    m_framebufferTexture
  , nullptr
  , m_framebufferData.data()
  , common::WIN_WIDTH * sizeof(uint32_t)
  );

  SDL_RenderTexture(m_renderer, m_framebufferTexture, nullptr, nullptr);

  SDL_RenderPresent(m_renderer);
}


void Application::draw()
{
  // Clear framebuffer to black
  m_framebufferData.fill(0x00000000);

  // Blit fire to framebuffer
  for (int i{}; i < common::WIN_WIDTH; ++i)
  {
    for (int j{}; j < common::FIRE_HEIGHT; ++j)
    {
      auto shift = common::WIN_HEIGHT - common::FIRE_HEIGHT;
      auto paletteIndex = utilities::clamp(static_cast<int>(m_fireView[i, j]), 0, static_cast<int>(constants::PALETTE_SIZE - 1));
      m_framebufferView[i, j + shift] = constants::firePalette[paletteIndex];
    }
  }
}


void Application::timingStart()
{
  m_frameStartCounts = SDL_GetPerformanceCounter();
}


void Application::timingEnd()
{
  m_frameEndCounts = SDL_GetPerformanceCounter();

  m_frameElapsedTime_s = static_cast<double>(m_frameEndCounts - m_frameStartCounts) / SDL_GetPerformanceFrequency();

  if (m_frameElapsedTime_s < constants::FRAME_TIME_S)
  {
    SDL_DelayPrecise((constants::FRAME_TIME_S - m_frameElapsedTime_s) * 1000 * 1000 * 1000);
  }

  auto fps = static_cast<double>(SDL_GetPerformanceFrequency()) / (SDL_GetPerformanceCounter() - m_frameStartCounts);

  static int count{};
  if (count == 30)
  {
    std::println(stderr, "[DEBUG] Frame rate: {}", fps);
    count = 0;
  }
  ++ count;
}


void Application::setPixel(std::size_t i, std::size_t j, uint32_t color)
{
  if (i >= m_framebufferView.extent(0) || j >= m_framebufferView.extent(1))
  {
    std::println(stderr, "Attempted to index m_framebufferView out of range ({}, {})", i, j);

    exit(1);
  }

  m_framebufferView[i, j] = color;
}


void Application::init()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::println(stderr, "SDL_Init: Failed to initialize SDL video subsystem");

    quit();
    exit(1);
  }

  m_window = SDL_CreateWindow(
  constants::WIN_TITLE.data()
  , common::WIN_WIDTH * 4
  , common::WIN_HEIGHT * 4
  , 0
  );

  if (m_window == nullptr)
  {
    std::println(stderr, "SDL_CreateWindow: Failed to create SDL window");

    quit();
    exit(1);
  }

  m_renderer = SDL_CreateRenderer(m_window, nullptr);

  if (m_renderer == nullptr)
  {
    std::println(stderr, "SDL_CreateRenderer: Failed to create SDL renderer");

    quit();
    exit(1);
  }

  m_framebufferTexture = SDL_CreateTexture(
    m_renderer
  , SDL_PIXELFORMAT_XRGB8888
  , SDL_TEXTUREACCESS_STREAMING
  , common::WIN_WIDTH
  , common::WIN_HEIGHT
  );

  if (m_framebufferTexture == nullptr)
  {
    std::println(stderr, "SDL_CreateTexture: Failed to create SDL Texture");

    quit();
    exit(1);
  }

  SDL_SetTextureScaleMode(m_framebufferTexture, SDL_SCALEMODE_NEAREST);

  m_running = true;
}


void Application::quit()
{
  if (m_framebufferTexture != nullptr)
  {
    SDL_DestroyTexture(m_framebufferTexture);
    m_framebufferTexture = nullptr;
  }

  if (m_renderer != nullptr)
  {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
  }

  if (m_window != nullptr)
  {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }

  if (SDL_WasInit(SDL_INIT_VIDEO))
  {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
  }

  SDL_Quit();
}


void Application::input()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
    {
      m_running = false;
      break;
    }

    case SDL_EVENT_KEY_DOWN:
    {
      if (event.key.key == SDLK_ESCAPE)
      {
        m_running = false;
      }

      if (event.key.key == SDLK_SPACE)
      {
        if (!event.key.repeat)
        {
          m_fireOn = !m_fireOn;
        }
      }

      if (event.key.key == SDLK_LEFT)
      {
        int updatedIntensity = utilities::clamp(
          static_cast<int>(m_heatingElementIntensity) - 1
        , 0
        , static_cast<int>(constants::PALETTE_SIZE) - 1
        );

        m_heatingElementIntensity = updatedIntensity;
      }

      if (event.key.key == SDLK_RIGHT)
      {
        int updatedIntensity = utilities::clamp(
          static_cast<int>(m_heatingElementIntensity) + 1
        , 0
        , static_cast<int>(constants::PALETTE_SIZE) - 1
        );

        m_heatingElementIntensity = updatedIntensity;
      }

      break;
    }

    default:
    {
      break;
    }
    }
  }
}

}
