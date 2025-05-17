#include "imgui.h"

namespace ImGui {
    void Synchro(float fraction, const float& sz);
    void Gauge(float val, float min, float max, const char *unit, const float& sz);
    void LinearGauge(float val, float min, float max, const char *unit, const float& sz);
    void Indicator(float state, float r, float g, float b, const char *label, float sz);
    void SwitchKnob(int *state, int positions, bool momentary, const char *label, float sz);
}

