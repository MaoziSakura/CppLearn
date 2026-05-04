/*
 * @Author: MaoziSakura
 * @Date: 2026-04-13
 * @FilePath: /AbstractLinkedList/tests/linked_test.cpp
 * @LastEditTime: 2026-04-30
 * @Description:
 */

#include "custom_test.hpp"
#include "linked_class.hpp"
#include <iostream>
#include <random>

using namespace std;

int linked_struct_test()
{
    list_record<int> record;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    // 验证添加
    for (int i = 0; i < 10; ++i)
    {
        list_node<int>* tmp_node = new list_node<int>(); // NOLINT
        tmp_node->data = dis(gen);
#ifdef DEBUG
        cout << "tmp_node address: " << tmp_node << " data value " << tmp_node->data << "\n";
#endif
        addListNode(record, tmp_node);
    }
    printListNode(record, printNode);

    // 验证删除
    removeListNode(record, 10, removeNode);
    printListNode(record, printNode);

    return 0;
}

void printNode(list_node<int>* node)
{
    cout << node->data << " ";
    return;
}

void removeNode(list_node<int>* node)
{
    delete node; // NOLINT
    return;
}

class IntNode : public BaseNode
{
public:
    int data;
    IntNode() = default;
    IntNode(int data) : data(data) {};

    void printNode(BaseNode* ptr) const override
    {

        auto* tmp_ptr = pointer_as(ptr);
        cout << tmp_ptr->data << " -> ";
        return;
    }

    void modifyNode(BaseNode* ptr, BaseNode* modify_ptr) override
    {
        auto* tmp_modify_ptr = pointer_as(modify_ptr);
        auto* tmp_ptr = pointer_as(ptr);
        tmp_modify_ptr->data = tmp_ptr->data;
        return;
    }

    bool cmpNode(BaseNode* ptr, BaseNode* other_ptr) const override
    {
        auto* tmp_other_ptr = pointer_as(other_ptr);
        auto* tmp_ptr = pointer_as(ptr);
        return tmp_ptr->data == tmp_other_ptr->data;
    }

    static IntNode* pointer_as(BaseNode* ptr)
    {
        return dynamic_cast<IntNode*>(ptr);
    }
};

int linked_class_test()
{
    // Record record{new IntNode{-1}, new IntNode{-1}};
    Record record{};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < 10; i++)
    {
        IntNode* tmp_node = new IntNode(); // NOLINT
        tmp_node->data = dis(gen);
#ifdef DEBUG
        cout << "tmp_node address: " << tmp_node << " data value " << tmp_node->data << "\n";
#endif
        record.head_ptr->addListNode(record.head_ptr, tmp_node);
    }
    record.head_ptr->printListNode(record.head_ptr);

    IntNode* find_pre_ptr = nullptr;
    BaseNode* find_pre_ptr_median_value = find_pre_ptr;
    IntNode* find_ptr = IntNode::pointer_as(record.head_ptr->findIndexListNode(record.head_ptr, 5, &find_pre_ptr_median_value));
    find_pre_ptr = IntNode::pointer_as(find_pre_ptr_median_value);
#ifdef DEBUG
    cout << "find_pre_ptr_median_value address " << find_pre_ptr_median_value << "\n";
    cout << "find_pre_ptr address " << find_pre_ptr << "\n";
#endif
    cout << "find ptr address " << find_ptr << " find value " << find_ptr->data << " \n";
    cout << "find pre ptr address " << find_pre_ptr << " find pre value " << find_pre_ptr->data << " \n";

    record.head_ptr->removeListNode(find_pre_ptr, find_ptr);
    record.head_ptr->printListNode(record.head_ptr);

    BaseNode* test_tmp = new IntNode{5};
    record.head_ptr->modifyListNode(test_tmp, find_pre_ptr);

    record.head_ptr->printListNode(record.head_ptr);

    int find_index = record.head_ptr->findValueListNode(record.head_ptr, test_tmp);

    cout << "find value index " << find_index << " \n";
    delete test_tmp; // NOLINT
    test_tmp = nullptr;

    return 0;
}
