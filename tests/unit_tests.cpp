#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <utilities.hpp>

/**
 * @brief Return the upper limit if the value is greater.
 *   Return the lower limit if the value is lower.
 */
template <typename T>
T clamp(T x, T min, T max);

TEST_CASE("Utilities", "[utilities]")
{
  using TupleType = std::tuple<double, double>;
  auto tolerance = 0.000001;

  SECTION("lerp(): Linear interpolation")
  {
    auto [result, expectedResult] = GENERATE(
      TupleType{utilities::lerp(0.0, 0.0, 1.0, 0.0, 1.0), 0.0}
    , TupleType{utilities::lerp(1.0, 0.0, 1.0, 0.0, 1.0), 1.0}
    , TupleType{utilities::lerp(5.0, 0.0, 10.0, 0.0, 1.0), 0.5}
    , TupleType{utilities::lerp(0.5, 0.0, 1.0, 0.0, 10.0), 5.0}
    );

    REQUIRE_THAT(result, Catch::Matchers::WithinRel(expectedResult, tolerance));
  }


  SECTION("clamp(): Limiting a value to a range")
  {
    auto [result, expectedResult] = GENERATE(
      TupleType{utilities::clamp(0.0, 0.0, 1.0), 0.0}
    , TupleType{utilities::clamp(1.0, 0.0, 1.0), 1.0}
    , TupleType{utilities::clamp(-1.0, 0.0, 1.0), 0.0}
    , TupleType{utilities::clamp(2.0, 0.0, 1.0), 1.0}
    );

    REQUIRE_THAT(result, Catch::Matchers::WithinRel(expectedResult, tolerance));
  }
}
