#pragma once

#include <common.hpp>
#include <string_view>
#include <array>
#include <cstdint>
#include <cstdint>

using namespace std::string_view_literals;

namespace doom_fire::constants
{

// Constants
constexpr auto FRAME_RATE_FPS{60.0}; // Frames per second
constexpr auto FRAME_TIME_S{1.0 / FRAME_RATE_FPS}; // Seconds per frame

// VGA mode 13h
static constexpr auto WIN_SIZE{common::WIN_WIDTH * common::WIN_HEIGHT};
static constexpr auto WIN_TITLE{"SDL3 Pixels"sv};

static constexpr auto FIRE_SIZE{common::WIN_WIDTH * common::FIRE_HEIGHT};

constexpr uint32_t PALETTE_SIZE{37};
[[maybe_unused]] constexpr std::array<uint32_t, PALETTE_SIZE> firePalette{
  0x00070707, 0x001F0707, 0x002F0F07, 0x00470F07,
  0x00571707, 0x00671F07, 0x00771F07, 0x008F2707,
  0x009F2F07, 0x00AF3F07, 0x00BF4707, 0x00C74707,
  0x00DF4F07, 0x00DF5707, 0x00DF5707, 0x00D75F07,
  0x00D75F07, 0x00D7670F, 0x00CF6F0F, 0x00CF770F,
  0x00CF7F0F, 0x00CF8717, 0x00C78717, 0x00C78F17,
  0x00C7971F, 0x00BF9F1F, 0x00BF9F1F, 0x00BFA727,
  0x00BFA727, 0x00BFAF2F, 0x00B7AF2F, 0x00B7B72F,
  0x00B7B737, 0x00CFCF6F, 0x00DFDF9F, 0x00EFEFC7,
  0x00FFFFFF
};

}
