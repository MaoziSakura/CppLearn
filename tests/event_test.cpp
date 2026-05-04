/*
 * @Author: MaoziSakura
 * @Date: 2026-04-20
 * @FilePath: /AbstractLinkedList/tests/event_test.cpp
 * @LastEditTime: 2026-04-30
 * @Description:
 */

#include "custom_test.hpp"
#include "event_handing.hpp"
#include <string>

using namespace std;

class Kwargs : public BaseKwargs
{
public:
    int a;
    string s;
    Kwargs() = default;
    Kwargs(int a, string s) : a(a), s(s) {};
};

class Action : public BaseAction
{
    void action_func(BaseKwargs* value) override
    {
        auto* kwargs = dynamic_cast<Kwargs*>(value);
        cout << "kwargs int value is " << kwargs->a << " string value is " << kwargs->s << " \n";
    }
};

class Trigger : public BaseTrigger
{
    // void trigger_execution(const BaseKwargs* value, const void* func) override
    // {

    //     auto* kwargs = dynamic_cast<const Kwargs*>(value);
    //     this->_value = kwargs->a;
    //     cout << "对trigger value 进行修改 \n";
    // }
};

void event_test()
{
    Trigger t{};
    Action a, b;
    Kwargs data1{5, "aaaaa"}, data2{10, "bbbbbbbb"};
    std::cout << "a address " << &a << "  " << "b address " << &b << std::endl;
    std::cout << "-----------------------" << std::endl;
    a.listen(t);
    std::cout << "-----------------------" << std::endl;
    b.listen(t);
    std::cout << "-----------------------" << std::endl;
    t.trigger_execution(dynamic_cast<BaseKwargs*>(&data1));
    std::cout << "-----------------------" << std::endl;
    b.unlisten(t);
    std::cout << "-----------------------" << std::endl;
    t.trigger_execution(dynamic_cast<BaseKwargs*>(&data2));
    std::cout << "-----------------------" << std::endl;

    return;
}