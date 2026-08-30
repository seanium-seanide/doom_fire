#pragma once

#include <cstdint>
#include <cstddef>


namespace doom_fire::common
{

using size_type = std::size_t;
using data_type = std::uint32_t;

static constexpr auto WIN_WIDTH{320};
static constexpr auto WIN_HEIGHT{200};
static constexpr auto WIN_SIZE{common::WIN_WIDTH * common::WIN_HEIGHT};

static constexpr auto FIRE_HEIGHT{static_cast<int>(3.0 * static_cast<double>(WIN_HEIGHT) / 4.0)};
static constexpr auto FIRE_SIZE{common::WIN_WIDTH * common::FIRE_HEIGHT};

}
