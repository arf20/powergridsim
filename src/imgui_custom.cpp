#include "imgui_custom.h"

#include <cmath>
#include <cstdio>

#define PI  3.1415926535897932384626

const ImVec2 arrow[] = {
    ImVec2(0.0f, -1.0f),
    ImVec2(0.05f, 0.0f),
    ImVec2(0.05f, 0.05f),
    ImVec2(-0.05f, 0.05f),
    ImVec2(-0.05f, 0.0f),
    ImVec2(0.0f, -1.0f),
};

ImVec2 rotate(const ImVec2& v, float a) {
    return ImVec2(
        v.x * cos(a) - v.y * sin(a),
        v.x * sin(a) + v.y * cos(a)
    );
}

ImVec2 scale(const ImVec2& v, float f) {
    return ImVec2(
        v.x * f,
        v.y * f
    );
}

ImVec2 add(const ImVec2& a, const ImVec2& b) {
    return ImVec2(
        a.x + b.x,
        a.y + b.y
    );
}


void ImGui::Synchro(float angle, const float& sz) {
    while (angle < PI) angle += 2*PI;
    while (angle > PI) angle -= 2*PI;

    float indlum = fabs(angle)/PI;

    const ImU32 col = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    const ImU32 fillcol = ImColor(ImVec4(indlum, indlum, indlum, 1.0f));

    const ImVec2 p = ImGui::GetCursorScreenPos();
    float x = p.x + 4.0f;
    float y = p.y + 4.0f;
    const ImVec2 c = ImVec2(x + sz*0.5f, y + sz*0.5f);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // perimeter
    draw_list->AddCircle(ImVec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, 35, 1.0f);
    // 0° line
    draw_list->AddLine(ImVec2(x + sz*0.5f, y + sz*0.05f), ImVec2(x + sz*0.5f, y + sz*0.1f), col, 1.0f);
    // indicator lights
    draw_list->AddCircle(ImVec2(x + sz*0.3f, y + sz*0.3f), sz*0.05f, col, 20, 1.0f);
    draw_list->AddCircle(ImVec2(x + sz*0.7f, y + sz*0.3f), sz*0.05f, col, 20, 1.0f);
    draw_list->AddCircleFilled(ImVec2(x + sz*0.3f, y + sz*0.3f), sz*0.05f, fillcol, 20);
    draw_list->AddCircleFilled(ImVec2(x + sz*0.7f, y + sz*0.3f), sz*0.05f, fillcol, 20);
    // fast slow text
    static const char *faststr = "fast";
    static const char *slowstr = "slow";
    draw_list->AddText(ImVec2(p.x + sz*0.25f - (ImGui::CalcTextSize(slowstr).x / 2.0f), p.y + sz*0.5f), col, slowstr, nullptr);
    draw_list->AddText(ImVec2(p.x + sz*0.75f - (ImGui::CalcTextSize(faststr).x / 2.0f), p.y + sz*0.5f), col, faststr, nullptr);

    // arrow
    static ImVec2 t_arrow[6];
    for (size_t i = 0; i < sizeof(arrow)/sizeof(*arrow); i++)
        t_arrow[i] = add(c, scale(rotate(arrow[i], angle), sz*0.4));
    draw_list->AddConvexPolyFilled(t_arrow, 6, col);

    // text overlay
    static char overlay[100];
    snprintf(overlay, 100, "%.1f°", angle*180.0f/PI);
    draw_list->AddText(ImVec2(p.x + sz*0.5f - (ImGui::CalcTextSize(overlay).x / 2.0f), p.y + sz*0.75f), col, overlay, nullptr);

    ImGui::Dummy(ImVec2(sz + 8.0f, sz + 8.0f));
}

float gauge_angle(float val, float min, float max) {
    val -= (max-min)/2.0f;
    val *= (6.0f*PI/4.0f)/(max-min);
    return val;
}

void ImGui::Gauge(float val, float min, float max, const char *unit, const float& sz) {
    const ImU32 col = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

    const ImVec2 p = ImGui::GetCursorScreenPos();
    float x = p.x + 4.0f;
    float y = p.y + 4.0f;
    const ImVec2 c = ImVec2(x + sz*0.5f, y + sz*0.5f);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // perimter
    draw_list->AddCircle(ImVec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, 35, 1.0f);
    // center thing
    draw_list->AddCircleFilled(ImVec2(x + sz*0.5f, y + sz*0.5f), sz*0.1f, col, 20);
    // scale
    ImVec2 tp = rotate(ImVec2(0.0f, -1.0f), 0);
    for (float t = min; t < max; t += (max-min)/10.0f) {
        float a = gauge_angle(t, min, max);
        ImVec2 rtp = rotate(tp, a);
        draw_list->AddLine(add(c, scale(rtp, sz*0.40f)), add(c, scale(rtp, sz*0.45f)), col, 1.0f);
    }
    ImVec2 rtp = rotate(tp, 3.0f*PI/4.0f);
    draw_list->AddLine(add(c, scale(rtp, sz*0.40f)), add(c, scale(rtp, sz*0.45f)), col, 1.0f); // always draw end of scale

    // arrow
    static ImVec2 t_arrow[6];
    float clippedval = val;
    if (clippedval > max) clippedval = max;
    if (clippedval < min) clippedval = min;
    float a = gauge_angle(clippedval, min, max);
    for (size_t i = 0; i < sizeof(arrow)/sizeof(*arrow); i++)
        t_arrow[i] = add(c, scale(rotate(arrow[i], a), sz*0.4));
    draw_list->AddConvexPolyFilled(t_arrow, 6, col);

    // min max labels
    static char minstr[100], maxstr[100];
    snprintf(minstr, 100, "%.0f", min);
    snprintf(maxstr, 100, "%.0f", max);
    draw_list->AddText(ImVec2(p.x + sz*0.3f - (ImGui::CalcTextSize(minstr).x / 2.0f), p.y + sz*0.7f), col, minstr, nullptr);
    draw_list->AddText(ImVec2(p.x + sz*0.7f - (ImGui::CalcTextSize(maxstr).x / 2.0f), p.y + sz*0.7f), col, maxstr, nullptr);
    // value overlay text
    static char overlay[100];
    if (val > max)
        snprintf(overlay, 100, ">%.1f %s", clippedval, unit);
    else if (val < min)
        snprintf(overlay, 100, "<%.1f %s", clippedval, unit);
    else
        snprintf(overlay, 100, "%.1f %s", clippedval, unit);
    draw_list->AddText(ImVec2(p.x + sz*0.5f - (ImGui::CalcTextSize(overlay).x / 2.0f), p.y + sz*0.85f), col, overlay, nullptr);

    ImGui::Dummy(ImVec2(sz + 8.0f, sz + 8.0f));
}


