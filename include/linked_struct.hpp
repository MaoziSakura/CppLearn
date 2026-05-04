/*
 * @Author: MaoziSakura
 * @Date: 2026-04-14
 * @FilePath: /AbstractLinkedList/include/linked_struct.hpp
 * @LastEditTime: 2026-04-30
 * @Description:
 */

#pragma once

// 抽象链表节点
template <typename T>
struct list_node
{
    T data;
    list_node<T>* next_ptr;
};

// 链表记录器
template <typename T>
struct list_record
{
    int count = 0;
    list_node<T>* head_ptr = nullptr;
    list_node<T>* end_ptr = nullptr;
};