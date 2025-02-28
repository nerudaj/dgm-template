#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Tgui.hpp>
#include <memory>
#include <set>
#include <string>

class [[nodiscard]] Gui final
{
public:
    Gui(tgui::Gui& gui, tgui::Theme& theme) noexcept : gui(gui), theme(theme) {}

public:
    template<class T>
    T::Ptr get(const std::string& id) const
    {
        return gui.get<T>(id);
    }

    void add(const tgui::Widget::Ptr& widget)
    {
        gui.add(widget);
    }

    void add(const tgui::Widget::Ptr& widget, const tgui::String& id)
    {
        gui.add(widget, id);
    }

    void remove(const tgui::Widget::Ptr& widget)
    {
        gui.remove(widget);
    }

    void handleEvent(const sf::Event& event)
    {
        gui.handleEvent(event);
    }

    void draw()
    {
        gui.draw();
    }

    void rebuildWith(const tgui::Widget::Ptr& layout)
    {
        removeAllWidgets();
        add(layout);
    }

    void removeAllWidgets()
    {
        gui.removeAllWidgets();
    }

    void setWindow(sf::RenderWindow& window)
    {
        gui.setWindow(window);
    }

private:
    tgui::Gui& gui;
    tgui::Theme& theme; // TODO: is this used?
};