#include "gui.h"

#include "imgui.h"
#include "imgui_custom.h"
#include "plants.h"

#include <cstdio>

const float width = 136.0f;

void win_management() {
    ImGui::Begin("Management");

    // type dropdown
    static int prev_type = 0, cur_type = 0;
    ImGui::Combo("Plant Type", &cur_type, plant_type_names, IM_ARRAYSIZE(plant_type_names));
    // capacity dropdown
    static int capacity = plant_types[0].default_capacity;
    if (cur_type != prev_type) {
        capacity = plant_types[cur_type].default_capacity;
        prev_type = cur_type;
    }
    ImGui::InputInt("Generation Capacity (kW)", &capacity);
    // build cost
    static char buff[100];
    snprintf(buff, 100, "%.0f", capacity * plant_types[cur_type].build_cost);
    ImGui::LabelText("Build Cost (US$)", buff);
    // operating cost
    snprintf(buff, 100, "%.4f", plant_types[cur_type].operating_cost);
    ImGui::LabelText("Operating Cost (US$/kWh)", buff);

    // actions
    if (ImGui::Button("Deploy")) {

    }


    ImGui::End();
}

void win_cc() {
    ImGui::Begin("Control Center");

    ImGui::Text("Frequency");
    ImGui::Gauge(50.0f, 48.0f, 52.0f, "Hz", 120.0f);

    ImGui::End();
}


void win_hydrogen() {
    ImGui::Begin("Hydroelectric Plant");

    static float t = 0.0f;
    t += 0.05;

    ImGui::Text("Water flow");
    ImGui::SameLine(width);
    ImGui::Text("Frequency");
    ImGui::SameLine(2.0f*width);
    ImGui::Text("Synchroscope");

    ImGui::Gauge(t/50.0f, 0.0f, 2.0f, "m²/s", 120.0f);
    ImGui::SameLine();
    ImGui::Gauge(10.0f*t, 48.0f, 52.0f, "Hz", 120.0f);
    ImGui::SameLine();
    ImGui::Synchro(t, 120.0f);

    ImGui::PushItemWidth(width);
    ImGui::Text("Power");
    ImGui::SameLine(width);
    ImGui::Text("Voltage");

    ImGui::Gauge(1000.0f*t, 0.0f, 100000.0f, "kW", 120.0f);
    ImGui::SameLine();
    ImGui::Gauge(100.0f*t, 0.0f, 3000.0f, "V", 120.0f);

    ImGui::Separator();

    ImGui::Indicator(1.0f, 1.0f, 1.0f, 1.0f, "control", 24);

    static int gate = 0;
    ImGui::SwitchKnob(&gate, 3, true, "Wicket Gate", 48);
    static int control = 0;
    ImGui::SwitchKnob(&control, 2, false, "Control", 48);

    ImGui::BeginGroup();
    ImGui::Button("Exciter");
    ImGui::SameLine();
    ImGui::Button("Main Breaker");
    ImGui::EndGroup();
    
    ImGui::End();
}


void render_gui() {
    win_management();
    win_cc();
    win_hydrogen();
}

