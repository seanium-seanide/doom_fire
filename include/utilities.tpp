namespace utilities
{

template <typename T>
T lerp(T x, T x1, T x2, T y1, T y2)
{
  auto dx = x2 - x1;
  auto dy = y2 - y1;
  auto m = dy / dx;

  return m * (x - x1) + y1;
}

template <typename T>
T clamp(T x, T min, T max)
{
  if (x < min)
  {
    return min;
  }
  else if (x > max)
  {
    return max;
  }

  return x;
}

}
