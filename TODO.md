# TODO List

* [ ] Optimize blitting fire to framebuffer (SIMD? std::memcpy the raw fire buffer to the framebuffer?).
* [ ] Add unit tests for application.
* [ ] In `Application::update()`, when the hot plate is turned off, on a new non-blocking thread, start a timer, When
      the timer times out, if the hot plate is off, clear the fire buffer buffer so the window does not display with
      a gray-ish gradient up to `FIRE_HEIGHT`.
* [ ] Resolve embedded TODOs.
* [ ] Eventually, render the fire on the GPU via OpenGL.
