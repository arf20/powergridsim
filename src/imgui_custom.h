#include "imgui.h"

namespace ImGui {
    void Synchro(float fraction, const float& sz);
    void Gauge(float val, float min, float max, const char *unit, const float& sz);
    void Indicator(float state, float r, float g, float b, const char *label, float sz);
    void SwitchKnob(int *state, bool momentary);
}

