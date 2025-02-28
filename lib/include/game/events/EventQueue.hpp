#pragma once

#include <vector>

template<class T>
class [[nodiscard]] EventQueue final
{
public:
    template<class EventType, class ... Args>
    void pushEvent(Args&& ... args)
    {
        events.emplace_back<EventType>(std::forward<Args>(args...));
    }

    template<class Visitor>
    void processEvents(Visitor& visitor)
    {
        for (size_t idx = 0; idx < events.size(); ++idx)
        {
            std::visit(events[idx], visitor);
        }

        events.clear();
    }

private:
    std::vector<T> events;
};
