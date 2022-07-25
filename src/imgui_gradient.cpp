#include <imgui_gradient/imgui_draw.h>
#include <imgui_gradient/imgui_gradient.hpp>
#include <iterator>

// TODO(ASG) Fix small line above marks that happens sometimes (maybe because two marks are overlapping perfectlyt ???)

namespace Gradient {

void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

GradientMarks::GradientMarks()
{
    add_mark(Mark{0.f, ImVec4{0.f, 0.f, 0.f, 1.f}});
    add_mark(Mark{1.f, ImVec4{1.f, 1.f, 1.f, 1.f}});
}

ImVec4 GradientMarks::get_color_at(float position) const
{
    return compute_color_at(RelativePosition{
        ImClamp(position, 0.f, 1.f)}); // TODO(ASG) Offer more options: repeat, mirror, clamp, etc.
}

static auto random_color() -> ImVec4
{
    const auto color = ImVec4{utils::rand(), utils::rand(), utils::rand(), 1.f};
    return color;
}

ImVec4 GradientMarks::compute_color_at(RelativePosition position) const
{
    const Mark* lower = nullptr;
    const Mark* upper = nullptr;
    for (const Mark& mark : m_marks.m_list)
    {
        if (mark.position > position &&
            (!upper || mark.position < upper->position))
        {
            upper = &mark;
        }
        if (mark.position < position &&
            (!lower || mark.position > lower->position))
        {
            lower = &mark;
        }
    }
    if (!lower && !upper)
    {
        return random_color();
    }
    else if (upper && !lower)
    {
        lower = upper;
    }
    else if (!upper && lower)
    {
        upper = lower;
    }

    if (upper == lower)
    {
        return upper->color;
    }
    else
    {
        float distance = upper->get_position() - lower->get_position();
        float mix      = (position.get() - lower->get_position()) / distance;

        // lerp
        return ImVec4{(1.f - mix), (1.f - mix), (1.f - mix), (1.f - mix)} * lower->color +
               ImVec4{mix, mix, mix, mix} * upper->color;
    }
}

static void draw_gradient_bar(Gradient::GradientMarks& GradientMarks, const ImVec2& bar_pos, float width, float height)
{
    ImDrawList& draw_list  = *ImGui::GetWindowDrawList();
    const float bar_bottom = bar_pos.y + height;

    internal::draw_bar_border(draw_list, bar_pos, ImVec2(bar_pos.x + width, bar_bottom), variables::border_color());
    internal::draw_background_if(draw_list, bar_pos, ImVec2(bar_pos.x + width, bar_bottom), variables::empty_backgroung_color(), GradientMarks.get_list().empty());

    internal::draw_gradient(GradientMarks, draw_list, bar_pos, bar_bottom, width);

    ImGui::SetCursorScreenPos(ImVec2(bar_pos.x, bar_pos.y + height + 10.0f));
}

static void draw_gradient_marks(Gradient::GradientMarks& gradient, Mark*& dragging_mark, Mark*& selected_mark, const ImVec2& bar_pos, float width, float height)
{
    ImDrawList& draw_list = *ImGui::GetWindowDrawList();

    Gradient::Mark* mark_to_delete = nullptr; // When we middle click to delete a non selected mark it is impossible to remove this mark in the loop
    for (auto markIt = gradient.get_list().begin(); markIt != gradient.get_list().end(); ++markIt)
    {
        Gradient::Mark& mark = *markIt;

        internal::mark_button(
            draw_list,
            bar_pos + ImVec2(mark.get_position() * width, height),
            ImGui::ColorConvertFloat4ToU32(mark.color),
            selected_mark == &mark
        );

        if (ImGui::IsItemHovered())
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                dragging_mark = &mark;
            }
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) || ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
            {
                selected_mark = &mark;
            }
            if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
            {
                ImGui::OpenPopup("picker");
            }
            if ((ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonMiddle) && ImGui::IsItemHovered()))
            {
                mark_to_delete = &mark;
            }
        }
    }
    if (mark_to_delete)
    {
        if (selected_mark && *selected_mark == *mark_to_delete)
        {
            gradient.remove_mark(*mark_to_delete);
            mark_to_delete = nullptr;
            selected_mark  = nullptr;
        }
        else
        {
            gradient.remove_mark(*mark_to_delete);
            mark_to_delete = nullptr;
        }
    }

    ImGui::SetCursorScreenPos(ImVec2(bar_pos.x, bar_pos.y + height + 20.0f));
}
} // namespace Gradient

namespace ImGuiGradient {
bool gradient_button(Gradient::GradientMarks& gradient)
{
    const ImVec2 widget_pos = ImGui::GetCursorScreenPos();
    const float  width      = ImMax(250.0f, ImGui::GetContentRegionAvail().x - 100.0f);
    const bool   clicked    = ImGui::InvisibleButton("gradient_bar", ImVec2(widget_pos.x + width, variables::GRADIENT_BAR_WIDGET_HEIGHT));

    draw_gradient_bar(gradient, widget_pos, width, variables::GRADIENT_BAR_WIDGET_HEIGHT);

    return clicked;
}

bool GradientWidget::gradient_editor(std::string_view name, float horizontal_margin, ImGuiColorEditFlags flags)
{
    ImGui::Text("%s", name.data());

    const float  width      = std::max(1.f, ImGui::GetContentRegionAvail().x - 2.f * horizontal_margin);
    const ImVec2 bar_pos    = variables::bar_position(horizontal_margin);
    const float  bar_bottom = bar_pos.y + variables::GRADIENT_BAR_EDITOR_HEIGHT;

    internal::draw_border_widget(
        bar_pos - ImVec2(horizontal_margin, ImGui::CalcTextSize(name.data()).y * 1.5f),
        ImVec2(bar_pos.x + width + horizontal_margin, bar_bottom + variables::button_size() * 3.f),
        variables::border_color()
    );

    ImGui::BeginGroup();
    ImGui::InvisibleButton("gradient_editor_bar", ImVec2(width, variables::GRADIENT_BAR_EDITOR_HEIGHT));

    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        add_mark((ImGui::GetIO().MousePos.x - bar_pos.x) / width);
        ImGui::OpenPopup("picker");
    }

    draw_gradient_bar(gradient, bar_pos, width, variables::GRADIENT_BAR_EDITOR_HEIGHT);
    draw_gradient_marks(gradient, dragging_mark, selected_mark, bar_pos, width, variables::GRADIENT_BAR_EDITOR_HEIGHT);

    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && dragging_mark)
    {
        dragging_mark = nullptr;
    }

    bool modified = false;
    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && dragging_mark)
    {
        const float map = ImClamp((ImGui::GetIO().MousePos.x - bar_pos.x) / width, 0.f, 1.f);
        if (dragging_mark->get_position() != map)
        {
            dragging_mark->position.set(map);
            gradient.get_marks().sorted();
            modified = true;
        }

        float diffY = ImGui::GetIO().MousePos.y - bar_bottom;
        if (diffY >= variables::GRADIENT_MARK_DELETE_DIFFY)
        {
            gradient.remove_mark(*dragging_mark); // TODO(ASG) hide it when dragging and remove it when released
            dragging_mark = nullptr;
            selected_mark = nullptr;
            modified      = true;
        }
    }
    ImGui::EndGroup();

    if (!gradient.get_list().empty() &&
        (ImGui::Button("-", ImVec2(variables::button_size(), variables::button_size()))) &&
        selected_mark)
    {
        gradient.remove_mark(*selected_mark);
        selected_mark = nullptr;
        dragging_mark = nullptr;
        modified      = true;
    }
    Gradient::tooltip("Select a mark to remove it\nor middle click on it\nor drag it down");

    if (!gradient.get_list().empty())
    {
        ImGui::SameLine();
    }
    if (ImGui::Button("+", ImVec2(variables::button_size(), variables::button_size())))
    {
        if (selected_mark)
        {
            const float select_pos = ImClamp(selected_mark->get_position(), 0.f, 1.f);

            float closer_pos = 0.f;
            if (gradient.get_list().size() == 1)
            {
                closer_pos = (select_pos < 1.f - select_pos) ? 0.f : 1.f;
            }
            else if (*selected_mark == gradient.get_list().front())
            {
                closer_pos = 0.f;
            }
            else if (*selected_mark == gradient.get_list().back())
            {
                closer_pos = 1.f;
            }
            else
            {
                closer_pos =
                    (abs(select_pos - ImClamp(
                                          gradient.previous_mark(selected_mark).get_position(), 0.f, 1.f
                                      )) >
                     abs(ImClamp(gradient.next_mark(selected_mark).get_position(), 0.f, 1.f) - select_pos))
                        ? ImClamp(gradient.previous_mark(selected_mark).get_position(), 0.f, 1.f)
                        : ImClamp(gradient.next_mark(selected_mark).get_position(), 0.f, 1.f);
            }
            add_mark((select_pos + closer_pos) / 2.f);
        }
        else
        {
            add_mark(utils::rand());
        }
        modified = true;
    }
    Gradient::tooltip("Add a mark here\nor click on the gradient to choose its position");
    ImGui::SameLine();
    if (selected_mark && ImGui::ColorEdit4("##picker1", reinterpret_cast<float*>(&selected_mark->color), ImGuiColorEditFlags_NoInputs | flags))
    {
        modified = true;
    }

    ImGui::PushItemWidth(width * .25f);
    ImGui::SameLine();
    if (selected_mark && ImGui::DragFloat("##3", &selected_mark->get_position(), 1.f / width, 0.f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
    {
        gradient.get_marks().sorted();
        modified = true;
    }

    if (ImGui::BeginPopup("picker") && selected_mark)
    {
        ImGui::SetNextItemWidth(variables::button_size() * 12.f);
        bool colorModified = ImGui::ColorPicker4("##picker2", reinterpret_cast<float*>(&selected_mark->color), flags);
        if (selected_mark && colorModified)
        {
            modified = true;
        }
        ImGui::EndPopup();
    }
    return modified;
}

}; // namespace ImGuiGradient