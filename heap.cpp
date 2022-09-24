#include <string>
#include <functional>
#include <iostream>
using namespace std;

constexpr int n = 100;

struct student
{
    int id;
    int mark;
    string name;

    student() {}

    student(int _id, int _mark, string _name)
    {
        id = _id;
        mark = _mark;
        name = _name;
    }
};

bool maxcmp(student s1, student s2)
{
    if (s1.mark == s2.mark)
        return s1.id < s2.id;

    return s1.mark < s2.mark;
}

bool mincmp(student s1, student s2)
{
    if (s1.mark == s2.mark)
        return s1.id > s2.id;

    return s1.mark > s2.mark;
}

struct heap
{
    int sz;
    student Student[n];
    function<bool(student s1, student s2)> cmp;

    bool isEmpty()
    {
        return (sz < 1) ? true : false;
    }

    void swap(int id1, int id2)
    {
        student t = Student[id1];
        Student[id1] = Student[id2];
        Student[id2] = t;
    }

    int getParent(int i)
    {
        return (i - 1) / 2;
    }

    int getLeftChild(int i)
    {
        return (2 * i) + 1;
    }

    int getRightChild(int i)
    {
        return (2 * i) + 2;
    }

    void shiftDown(int curIdx)
    {
        int shiftIdx = curIdx;
        int leftIdx = getLeftChild(curIdx);

        while (leftIdx < sz && cmp(Student[shiftIdx], Student[leftIdx]))
        {
            shiftIdx = leftIdx;
        }

        int rightIdx = getRightChild(curIdx);

        while (rightIdx < sz && cmp(Student[shiftIdx], Student[rightIdx]))
        {
            shiftIdx = rightIdx;
        }

        if (shiftIdx != curIdx)
        {
            swap(shiftIdx, curIdx);
            shiftDown(shiftIdx);
        }
    }

    void shiftUp(int curIdx)
    {
        int parent = getParent(curIdx);

        while (curIdx > 0 && cmp(Student[parent], Student[curIdx]))
        {
            swap(parent, curIdx);
            curIdx = parent;
            parent = getParent(curIdx);
        }
    }

    void push(student t)
    {
        Student[sz] = t;
        shiftUp(sz);
        ++sz;
    }

    void pop()
    {
        Student[0] = Student[--sz];
        shiftDown(0);
    }

    student top()
    {
        return Student[0];
    }

    void update(int _id, int _mark, int _heapType)
    {
        int i = 0;
        for (i = 0; i < sz; i++)
            if (Student[i].id == _id)
                break;

        int mark = Student[i].mark;
        Student[i].mark = _mark;

        if (_heapType == 1) // MAX HEAP
        {
            (_mark < mark) ? shiftDown(i) : shiftUp(i);
        }
        else
        {
            (_mark < mark) ? shiftUp(i) : shiftDown(i);
        }
    }
};

struct maxheap : heap
{
    maxheap()
    {
        sz = 0;
        cmp = maxcmp;
    }
};

struct minheap : heap
{
    minheap()
    {
        sz = 0;
        cmp = mincmp;
    }
};

int main()
{
    maxheap MaxHeap = maxheap();

    MaxHeap.push(student(23, 77, "Bob"));
    MaxHeap.push(student(3, 90, "Jorg"));
    MaxHeap.push(student(8, 33, "May"));
    MaxHeap.push(student(99, 33, "sean"));

    MaxHeap.update(23, 99, 1);

    MaxHeap.pop();
    MaxHeap.pop();

    return 0;
}