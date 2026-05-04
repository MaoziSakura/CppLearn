/*
 * @Author: MaoziSakura
 * @Date: 2026-04-13
 * @FilePath: /AbstractLinkedList/include/linked_list.hpp
 * @LastEditTime: 2026-04-30
 * @Description:
 */

#pragma once

#include "linked_struct.hpp"

// 增加节点
template <typename T>
void addListNode(list_record<T>& record, list_node<T>* node);
// 删除节点
template <typename T>
void removeListNode(list_record<T>& record, int index, void (*operation)(list_node<T>* node));
// 修改节点数据
template <typename T>
void modifyListNode(list_node<T>* node, void (*operation)(list_node<T>* node));
// 根据位置查找节点
template <typename T>
list_node<T>* findIndexListNode(const list_record<T>& record, int index, list_node<T>*& per_node = nullptr);
// 根据数据值查找节点
template <typename T>
int findValueListNode(const list_record<T>& record, const list_node<T>& node, bool (*operation)(const list_node<T>& tmp_node, const list_node<T> other_node));
// 打印链表
template <typename T>
void printListNode(const list_record<T>& record, void (*operation)(list_node<T>* node));

#include "../src/linked_list.tpp"

// template <typename T>
// void addListNode(list_record<T>& record, list_node<T>* node)
// {
//     if (!record.head_ptr)
//     {
//         record.head_ptr = node;
//         record.end_ptr = node;
//     }
//     else
//     {
//         record.end_ptr->next_ptr = node;
//         record.end_ptr = node;
//     }
//     ++record.count;
//     record.end_ptr->next_ptr = nullptr;
//     return;
// }

// // 删除节点
// template <typename T>
// void removeListNode(list_record<T>& record, int index, void (*operation)(list_node<T>* node))
// {
//     list_node<T>* per_node = nullptr;
//     list_node<T>* tmp_node = findIndexListNode(record, index, per_node);
// #ifdef DEBUG
//     cout << "remove per_node value: " << per_node << "\n";
// #endif
//     if (!tmp_node)
//     {
//         cout << "输入位置错误无法进行删除操作\n";
//         return;
//     }
//     if (!per_node)
//         record.head_ptr = tmp_node->next_ptr;
//     else
//         per_node->next_ptr = tmp_node->next_ptr;
//     tmp_node->next_ptr = nullptr;
//     --record.count;
//     if (operation)
//         operation(tmp_node);
//     return;
// }

// // 修改节点数据
// template <typename T>
// void modifyListNode(list_node<T>* node, void (*operation)(list_node<T>* node))
// {
//     if (operation)
//         operation(node);
//     return;
// }

// // 根据位置查找节点
// template <typename T>
// list_node<T>* findIndexListNode(const list_record<T>& record, int index, list_node<T>*& per_node)
// {
//     if (index <= 0)
//     {
//         cout << "输入位置不正确, 请输入大于0且小于" << record.count << "的数字" << endl;
//     }
//     list_node<T>* tmp = nullptr;
//     while (index)
//     {
//         --index;
//         per_node = tmp;
//         if (tmp)
//             tmp = tmp->next_ptr;
//         else
//             tmp = record.head_ptr;

// #ifdef DEBUG
//         cout << "per_node value: " << " " << per_node << "\n";
// #endif
//     }
//     return tmp;
// }

// // 根据数据值查找节点
// template <typename T>
// int findValueListNode(const list_record<T>& record, const list_node<T>& node, bool (*operation)(const list_node<T>& tmp_node, const list_node<T> other_node))
// {
//     bool flag = false;
//     int index = 0;
//     list_node<T> tmp_node = record.head_ptr;
//     while (tmp_node != nullptr)
//     {
//         ++index;
//         if (operation)
//             flag = operation(node, tmp_node);
//         if (flag)
//             break;
//     }

//     return index;
// }

// // 打印链表
// template <typename T>
// void printListNode(const list_record<T>& record, void (*operation)(list_node<T>* node))
// {
//     list_node<T>* tmp_node = record.head_ptr;
//     while (tmp_node != nullptr)
//     {
//         if (operation)
//             operation(tmp_node);
//         cout << " -> ";
//         tmp_node = tmp_node->next_ptr;
//     }
//     cout << "\n";
//     return;
// }