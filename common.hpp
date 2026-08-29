#pragma once

#include <cstdint>
#include <cstddef>


namespace doom_fire::common
{

using size_type = std::size_t;
using data_type = std::uint32_t;

static constexpr auto WIN_WIDTH{320};
static constexpr auto WIN_HEIGHT{200};
static constexpr auto FIRE_HEIGHT{static_cast<size_type>(static_cast<double>(WIN_HEIGHT) / 3.0)};

}
