/*
 * @Author: MaoziSakura
 * @Date: 2026-04-16
 * @FilePath: /AbstractLinkedList/include/linked_class.hpp
 * @LastEditTime: 2026-04-30
 * @Description:
 */

#include <iostream>

class BaseNode
{
public:
    BaseNode* next_ptr = nullptr;

    BaseNode() = default;
    BaseNode(BaseNode* next_ptr) : next_ptr(next_ptr) {}

    virtual void printNode(BaseNode* ptr) const = 0;
    virtual void modifyNode(BaseNode* ptr, BaseNode* modify_ptr) = 0;
    virtual bool cmpNode(BaseNode* ptr, BaseNode* other_ptr) const = 0;
    void addListNode(BaseNode*& ptr, BaseNode* add_ptr)
    {
        add_ptr->next_ptr = ptr;
        ptr = add_ptr;
        return;
    }
    void removeListNode(BaseNode* ptr, BaseNode* remove_ptr);
    void modifyListNode(BaseNode* ptr, BaseNode* modify_ptr);
    BaseNode* findIndexListNode(BaseNode* start_ptr, int offset, BaseNode** pre_ptr = nullptr) const;
    int findValueListNode(BaseNode* start_ptr, BaseNode* cmp_ptr) const;
    void printListNode(BaseNode* start_ptr) const;

    virtual ~BaseNode() = default;
};

void BaseNode::removeListNode(BaseNode* ptr, BaseNode* remove_ptr)
{
#ifdef DEBUG
    std::cout << "ptr value: " << ptr << "  remove_ptr: " << remove_ptr << "\n";
#endif
    if (remove_ptr == nullptr)
        return;
    ptr->next_ptr = remove_ptr->next_ptr;
    remove_ptr->next_ptr = nullptr;
    delete remove_ptr; // NOLINT
}

void BaseNode::modifyListNode(BaseNode* ptr, BaseNode* modify_ptr)
{
    this->modifyNode(ptr, modify_ptr);
    return;
}

BaseNode* BaseNode::findIndexListNode(BaseNode* start_ptr, int offset, BaseNode** pre_ptr) const
{
    BaseNode* tmp_node = nullptr;
    tmp_node = start_ptr;
    while (offset > 1)
    {
        --offset;
        *pre_ptr = tmp_node;
        tmp_node = tmp_node->next_ptr;
        if (tmp_node == nullptr)
            break;
    }
    return tmp_node;
}

int BaseNode::findValueListNode(BaseNode* start_ptr, BaseNode* cmp_ptr) const // NOLINT
{
    int offset = 0;
    BaseNode* tmp_node = start_ptr;
    while (tmp_node)
    {
        ++offset;
        if (this->cmpNode(tmp_node, cmp_ptr)) // NOLINT
            break;
        tmp_node = tmp_node->next_ptr;
    }
    return offset;
}

void BaseNode::printListNode(BaseNode* start_ptr) const
{
    BaseNode* tmp_node = start_ptr;
#ifdef DEBUG
    std::cout << "printlistnode tmp_node value " << tmp_node << " \n";
#endif
    while (tmp_node != nullptr)
    {
        this->printNode(tmp_node);
        tmp_node = tmp_node->next_ptr;
    }
    std::cout << "\n";
    return;
}

class Record
{
public:
    BaseNode* head_ptr = nullptr;
    int count{};

    Record() = default;
    Record(BaseNode* head_ptr) : head_ptr(head_ptr) {}

    ~Record()
    {
        count = 0;
        BaseNode* tmp = head_ptr;
        while (head_ptr != nullptr)
        {
            tmp = head_ptr;
            head_ptr = head_ptr->next_ptr;
            head_ptr->removeListNode(tmp, tmp);
        }
    }
};