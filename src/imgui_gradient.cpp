#include <imgui_gradient/gradient_widgets.h>
#include <imgui_gradient/imgui_draw.h>
#include <imgui_gradient/random.h>
#include <imgui_gradient/imgui_gradient.hpp>
#include <iterator>

// TODO(ASG) Fix small line above marks that happens sometimes (maybe because two marks are overlapping perfectly ???) apperas when adding a new mark in empty gradient

namespace ImGuiGradient {

static void draw_gradient_bar(Gradient& Gradient, const Interpolation& interpolation_mode, const ImVec2& bar_pos, float width, float height)
{
    ImDrawList& draw_list  = *ImGui::GetWindowDrawList();
    const float bar_bottom = bar_pos.y + height;

    draw_bar_border(draw_list, bar_pos, ImVec2(bar_pos.x + width, bar_bottom), variables::border_color());
    if (!Gradient.is_empty())
    {
        draw_gradient(Gradient, draw_list, interpolation_mode, bar_pos, bar_bottom, width);
    }

    ImGui::SetCursorScreenPos(ImVec2(bar_pos.x, bar_pos.y + height + 10.0f));
}

static bool mark_hovered(Mark*& dragging_mark, Mark*& selected_mark, Mark*& mark_to_delete, Mark& mark)
{
    bool is_hovered = ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
    if (is_hovered)
    {
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            dragging_mark = &mark;
        }
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) ||
            ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
        {
            selected_mark = &mark;
        }
        if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
        {
            ImGui::OpenPopup("picker");
        }
        if (ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonMiddle))
        {
            // When we middle click to delete a non selected mark it is impossible to remove this mark in the loop
            mark_to_delete = &mark;
        }
    }
    return is_hovered;
}

static bool draw_gradient_marks(Gradient& gradient, Mark*& dragging_mark, Mark*& selected_mark, Mark*& mark_to_delete, Mark*& mark_to_hide, const ImVec2& bar_pos, float width, float height)
{
    ImDrawList& draw_list         = *ImGui::GetWindowDrawList();
    bool        hitbox_is_hovered = false;
    for (auto markIt = gradient.get_list().begin(); markIt != gradient.get_list().end(); ++markIt)
    {
        Mark& mark = *markIt;
        if (!(mark_to_hide && *mark_to_hide == mark))
        {
            mark_button(
                draw_list,
                bar_pos + ImVec2(mark.get_position() * width, height),
                ImGui::ColorConvertFloat4ToU32(mark.color),
                selected_mark == &mark
            );
        }
        hitbox_is_hovered |= mark_hovered(dragging_mark, selected_mark, mark_to_delete, mark);
    }
    ImGui::SetCursorScreenPos(ImVec2(bar_pos.x, bar_pos.y + height + 20.0f));
    return hitbox_is_hovered;
}

bool gradient_button(Gradient& gradient, const Interpolation& interpolation)
{
    const ImVec2 widget_pos = ImGui::GetCursorScreenPos();
    const float  width      = ImMax(250.0f, ImGui::GetContentRegionAvail().x - 100.0f);
    const bool   clicked    = ImGui::InvisibleButton("gradient_bar", ImVec2(widget_pos.x + width, variables::GRADIENT_BAR_WIDGET_HEIGHT));

    draw_gradient_bar(gradient, interpolation, widget_pos, width, variables::GRADIENT_BAR_WIDGET_HEIGHT);

    return clicked;
}

// TODO(ASG) Add a reset button (and a flag to prevent this behaviour)

float position_where_add_mark(Gradient& gradient)
{
    if (gradient.is_empty())
    {
        return 0.5f;
    }
    else if (gradient.get_list().size() == 1)
    {
        return (gradient.get_list().begin()->get_position() > 1.f - gradient.get_list().begin()->get_position()) ? 0.f : 1.f;
    }
    else
    {
        float max_value_mark_position     = 0;
        float max_value_between_two_marks = gradient.get_list().begin()->get_position();
        for (auto markIt = gradient.get_list().begin(); markIt != std::prev(gradient.get_list().end()); ++markIt)
        {
            Mark& mark = *markIt;
            if (max_value_between_two_marks < abs(std::next(markIt)->get_position() - mark.get_position()))
            {
                max_value_mark_position     = mark.get_position();
                max_value_between_two_marks = abs(std::next(markIt)->get_position() - max_value_mark_position);
            }
        }
        if (max_value_between_two_marks < abs(1.f - std::prev(gradient.get_list().end())->get_position()))
        {
            max_value_mark_position     = std::prev(gradient.get_list().end())->get_position();
            max_value_between_two_marks = abs(1.f - max_value_mark_position);
        }
        return max_value_mark_position + max_value_between_two_marks / 2.f;
    }
}

bool GradientWidget::gradient_editor(std::string_view name, std::default_random_engine& generator, float horizontal_margin, ImGuiColorEditFlags flags)
{
    ImGui::Text("%s", name.data());

    const float  width      = std::max(1.f, ImGui::GetContentRegionAvail().x - 2.f * horizontal_margin);
    const ImVec2 bar_pos    = variables::bar_position(horizontal_margin);
    const float  bar_bottom = bar_pos.y + variables::GRADIENT_BAR_EDITOR_HEIGHT;

    draw_border_widget(
        bar_pos - ImVec2(horizontal_margin, ImGui::CalcTextSize(name.data()).y * 1.5f),
        ImVec2(bar_pos.x + width + horizontal_margin, bar_bottom + variables::button_size() * 3.f),
        variables::border_color()
    );

    ImGui::BeginGroup();
    ImGui::InvisibleButton("gradient_editor_bar", ImVec2(width, variables::GRADIENT_BAR_EDITOR_HEIGHT));
    draw_gradient_bar(gradient, interpolation_mode, bar_pos, width, variables::GRADIENT_BAR_EDITOR_HEIGHT);

    const bool add_mark_possible      = ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left);
    const bool mark_hitbox_is_hovered = draw_gradient_marks(gradient, dragging_mark, selected_mark, mark_to_delete, mark_to_hide, bar_pos, width, variables::GRADIENT_BAR_EDITOR_HEIGHT);

    bool modified = false;
    if (add_mark_possible && !mark_hitbox_is_hovered)
    {
        modified = add_mark((ImGui::GetIO().MousePos.x - bar_pos.x) / width, generator);
        ImGui::OpenPopup("picker");
    }

    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && dragging_mark)
    {
        dragging_mark = nullptr;
    }

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
            mark_to_hide = dragging_mark;
        }
        if (mark_to_hide && diffY <= variables::GRADIENT_MARK_DELETE_DIFFY)
        {
            dragging_mark = mark_to_hide;
            mark_to_hide  = nullptr;
        }
    }
    if (mark_to_hide && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        if (dragging_mark && *dragging_mark == *mark_to_hide)
        {
            dragging_mark = nullptr;
        }
        mark_to_delete = mark_to_hide;
        mark_to_hide   = nullptr;
        modified       = true;
    }
    if (mark_to_delete)
    {
        if (selected_mark && *selected_mark == *mark_to_delete)
        {
            selected_mark = nullptr;
        }
        remove_mark(mark_to_delete);
        mark_to_delete = nullptr;
    }
    ImGui::EndGroup();

    if (!gradient.is_empty())
    {
        if ((ImGui::Button("-", ImVec2(variables::button_size(), variables::button_size()))) &&
            selected_mark)
        {
            remove_mark(selected_mark);
            selected_mark = nullptr;
            modified      = true;
        }
        tooltip("Select a mark to remove it\nor middle click on it\nor drag it down");
        ImGui::SameLine();
    }

    if (ImGui::Button("+", ImVec2(variables::button_size(), variables::button_size())))
    {
        // Add a mark where there is the greater space in the gradient
        modified = add_mark(position_where_add_mark(gradient), generator);
    }
    tooltip("Add a mark here\nor click on the gradient to choose its position");

    ImGui::SameLine();
    if (selected_mark && ImGui::ColorEdit4("##picker1", reinterpret_cast<float*>(&selected_mark->color), ImGuiColorEditFlags_NoInputs | flags))
    {
        modified = true;
    }

    ImGui::PushItemWidth(width * .25f);
    ImGui::SameLine();
    if (selected_mark)
    {
        if (ImGui::DragFloat("##3", &selected_mark->get_position(), 1.f / width, 0.f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
        {
            gradient.get_marks().sorted();
            modified = true;
        }
        if (!gradient.is_empty())
        {
            tooltip("Choose a precise position");
        }
    }

    ImGui::SameLine();
    modified |= ImGui::Checkbox("Random Mode", &random_mode);
    tooltip("Add mark with random color");

    ImGui::SameLine();
    modified |= position_mode_combo(position_mode);
    ImGui::SameLine();
    modified |= gradient_interpolation_mode(interpolation_mode);

    if (ImGui::Button("Reset"))
    {
        reset_widget();
    }
    tooltip("Reset gradient to the default value");

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