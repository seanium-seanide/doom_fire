#pragma once

#include <common.hpp>
#include <mdspan>
#include <array>
#include <cstddef>

namespace doom_fire::types
{

using FramebufferType = std::array<common::data_type, common::WIN_SIZE>;
using FramebufferExtentsType = std::extents<common::size_type, common::WIN_WIDTH, common::WIN_HEIGHT>;
using FramebufferSpanType = std::mdspan<common::data_type, FramebufferExtentsType, std::layout_left>;

using FireType = std::array<common::data_type, common::FIRE_SIZE>;
using FireExtentsType = std::extents<common::size_type, common::WIN_WIDTH, common::FIRE_HEIGHT>;
using FireSpanType = std::mdspan<common::data_type, FireExtentsType, std::layout_left>;

}
