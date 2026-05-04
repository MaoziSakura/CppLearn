/*
 * @Author: MaoziSakura
 * @Date: 2026-04-20
 * @FilePath: /AbstractLinkedList/include/event_handing.hpp
 * @LastEditTime: 2026-04-30
 * @Description:
 */

#pragma once

#include <iostream>
#include <memory>
#include <vector>

// 空类, 用于中转
class Empty
{};

// 事件与执行关联类
template <typename EventAction>
class EventResponsor
{
public:
    // Empty* actor{nullptr};
    // EventAction* action{nullptr};
    Empty* actor;
    std::unique_ptr<EventAction> action;

    EventResponsor() = default;
    EventResponsor(Empty* actor, EventAction* action) : actor(actor), action(action) {};
    EventResponsor(EventResponsor&&) noexcept = default;
    EventResponsor& operator=(EventResponsor&&) noexcept = default;
    friend bool operator==(const EventResponsor& lptr, const EventResponsor& rptr)
    {
        if (lptr.action == nullptr or rptr.action == nullptr)
            std::cerr << "比较错误, 存在空指针 \n";
        return lptr.actor == rptr.actor && *(lptr.action) == *(rptr.action);
    }

#ifdef DEBUG
    ~EventResponsor()
    {
        std::cout << "EventResponsor address" << this << std::endl;
        std::cout << "Empty* address " << actor << std::endl;
        std::cout << "调用EventResponsor析构函数 \n" << std::endl;
    }
#endif
};

// 事件类
template <typename EventAction>
class Event
{
private:
    using responsor_vec = std::vector<EventResponsor<EventAction>>;
    responsor_vec ers;

public:
    Event()
    {
        ers.reserve(10);
    }
    void bind(void* actor, EventAction action);
    void unbind(void* actor, EventAction action);
    [[nodiscard]] const responsor_vec& get_event_responsor() const
    {
        return ers;
    }

    // ~Event()
    // {
    //     for (auto iter = this->ers.begin(); iter != ers.end(); ++iter)
    //     {
    //         delete iter->action;
    //         iter->action = nullptr;
    //     }
    // }
};

// 参数类
class BaseKwargs
{
public:
    virtual ~BaseKwargs() = default;
};

using EmptyActionFunc = void (Empty::*)(const BaseKwargs* value);
// 监听器类
class BaseTrigger
{
protected:
    int _value{0};
    Event<EmptyActionFunc> event{};

public:
    [[nodiscard]] int get_value() const
    {
        return _value;
    }
    void trigger_execution(const BaseKwargs* value);
    void add_event_bind(void* actor, EmptyActionFunc action);
    void remove_event_bind(void* actor, EmptyActionFunc action);
};

// 执行者类
class BaseAction
{
public:
    void listen(BaseTrigger& trigger);
    void unlisten(BaseTrigger& trigger);
    virtual void action_func(BaseKwargs* value) = 0;
};

// 事件类成员函数实现
template <typename EventAction>
void Event<EventAction>::bind(void* actor, EventAction action)
{
    auto* tmp_actor = reinterpret_cast<Empty*>(actor);
    EventResponsor<EventAction> tmp_event(tmp_actor, new EventAction(action));
    bool flag = false;
    for (auto iter = this->ers.begin(); iter != this->ers.end(); ++iter)
    {
#ifdef DEBUG
        std::cout << "bind loop Responsor +++++" << std::endl;
#endif
        if (*iter == tmp_event)
        {
            flag = true;
            break;
        }
    }
#ifdef DEBUG
    std::cout << "bind loop over!!!!!!!" << std::endl;
#endif
    if (!flag)
        this->ers.push_back(std::move(tmp_event));
#ifdef DEBUG
    std::cout << "tmp_event address " << &tmp_event << std::endl;
    std::cout << "bind func over \n" << std::endl;
#endif
    return;
}

template <typename EventAction>
void Event<EventAction>::unbind(void* actor, EventAction action)
{
    auto* tmp_actor = reinterpret_cast<Empty*>(actor);
    EventResponsor<EventAction> tmp_event(tmp_actor, new EventAction(action));
    for (auto iter = this->ers.begin(); iter != this->ers.end(); ++iter)
    {
        if (*iter == tmp_event)
        {
            std::swap(*iter, this->ers.back());
            this->ers.pop_back();
#ifdef DEBUG
            std::cout << "swap over \n" << std::endl;
#endif
            break;
        }
    }
#ifdef DEBUG
    std::cout << "unbind func over \n" << std::endl;
#endif
    return;
}

// 监听器类成员函数实现
void BaseTrigger::trigger_execution(const BaseKwargs* value)
{
    const auto& event_responsor = event.get_event_responsor();
    for (auto iter = event_responsor.begin(); iter != event_responsor.end(); ++iter)
    {
        ((iter->actor)->*(*(iter->action)))(value);
    }
}

void BaseTrigger::add_event_bind(void* actor, EmptyActionFunc action)
{
    event.bind(actor, action);
}

void BaseTrigger::remove_event_bind(void* actor, EmptyActionFunc action)
{
    event.unbind(actor, action);
}

// 执行者类成员函数实现
void BaseAction::listen(BaseTrigger& trigger)
{
    trigger.add_event_bind(this, reinterpret_cast<EmptyActionFunc>(&BaseAction::action_func));
}

void BaseAction::unlisten(BaseTrigger& trigger)
{
    trigger.remove_event_bind(this, reinterpret_cast<EmptyActionFunc>(&BaseAction::action_func));
}