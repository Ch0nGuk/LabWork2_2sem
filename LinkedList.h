#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>
#include <utility>

template <typename T>
class LinkedList
{
private:
    template <typename U>
    struct Node
    {
        U data;
        Node<U>* next;

        Node(const U& data, Node<U>* next = nullptr) : data(data), next(next) {}
    };

    Node<T>* head;
    Node<T>* tail;
    int size;

    void CheckIndex(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
    }

    void Clear()
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Node<T>* GetNode(int index) const
    {
        CheckIndex(index);

        Node<T>* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0)
    {
    }

    LinkedList(const T* items, int count) : head(nullptr), tail(nullptr), size(0)
    {
        if (count < 0)
        {
            throw std::out_of_range("Negative size");
        }

        if (items == nullptr && count > 0)
        {
            throw std::invalid_argument("Source array is null");
        }

        for (int i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0)
    {
        Node<T>* current = other.head;
        while (current != nullptr)
        {
            Append(current->data);
            current = current->next;
        }
    }

    ~LinkedList()
    {
        Clear();
    }

    LinkedList<T>& operator=(LinkedList<T> other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
        return *this;
    }

    const T& GetFirst() const
    {
        if (size == 0)
        {
            throw std::out_of_range("List is empty");
        }

        return head->data;
    }

    const T& GetLast() const
    {
        if (size == 0)
        {
            throw std::out_of_range("List is empty");
        }

        return tail->data;
    }

    const T& Get(int index) const
    {
        return GetNode(index)->data;
    }

    T& Get(int index)
    {
        return GetNode(index)->data;
    }

    int GetSize() const
    {
        return size;
    }

    void Append(const T& item)
    {
        Node<T>* new_node = new Node<T>(item);

        if (size == 0)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }

        size++;
    }

    void Prepend(const T& item)
    {
        Node<T>* new_node = new Node<T>(item, head);
        head = new_node;

        if (size == 0)
        {
            tail = new_node;
        }

        size++;
    }

    void InsertAt(const T& item, int index)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0)
        {
            Prepend(item);
            return;
        }

        if (index == size)
        {
            Append(item);
            return;
        }

        Node<T>* previous = GetNode(index - 1);
        Node<T>* new_node = new Node<T>(item, previous->next);
        previous->next = new_node;
        size++;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex > endIndex)
        {
            throw std::out_of_range("Index out of range");
        }

        LinkedList<T>* result = new LinkedList<T>();
        Node<T>* current = GetNode(startIndex);

        for (int i = startIndex; i <= endIndex; i++)
        {
            result->Append(current->data);
            current = current->next;
        }

        return result;
    }

    LinkedList<T>* Concat(const LinkedList<T>& other) const
    {
        LinkedList<T>* result = new LinkedList<T>(*this);
        Node<T>* current = other.head;

        while (current != nullptr)
        {
            result->Append(current->data);
            current = current->next;
        }

        return result;
    }
};

#endif // LINKED_LIST_H
