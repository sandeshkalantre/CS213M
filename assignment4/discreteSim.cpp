minMaxHeap.hpp                                                                                      000644  000765  000024  00000014210 12671777726 014432  0                                                                                                    ustar 00sandesh                         staff                           000000  000000                                                                                                                                                                         #ifndef _MINMAXHEAP_HPP_
#define _MINMAXHEAP_HPP_

#include <vector>
#include <iostream>

using namespace std;

template<class T>
class Predicate 
{
    public:
        virtual bool toDelete(T elem)
        {
            return true;
        }
};


template<class T>
class minMaxHeap {
private:
    vector<T> nodes;
     
public:
    //constructor
    minMaxHeap();

    //helper functions
    bool is_min_level(int i)
    {
        if(i == 0)
        {
            return true;
        }
        int tmp = i + 1;
        //level = floor(log tmp)
        int level = -1;
        while(tmp)
        {
            tmp >>= 1;
            level++;
        }
        if(level % 2 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //get parent id
    int parent(int i)
    {
        if(i == 0)
        {
            return -1;
        }

        return (i-1)/2;
    }

    //get grandparent id
    int grandparent(int i)
    {
        if(i == 0 || i == 1 || i == 2)
        {
            return -1;
        }
        return parent(parent(i));
    }
    //trickle down -> used in deletion
    //generalised heapify for min-max heap
    void trickle_down(int i)
    {
        if(is_min_level(i))
        {
            trickle_down_min(i);
        }
        else
        {
            trickle_down_max(i);
        }
        return;
    }

    void trickle_down_min(int i)
    {
        int min_index = i;
        bool child = false;
        bool gchild = false;
        //children
        if(2*i + 1 < nodes.size() and nodes[2*i + 1] < nodes[min_index])
        {
            min_index = 2*i + 1;
            child = true;
        }
        if(2*i + 2 < nodes.size() and nodes[2*i + 2] < nodes[min_index])
        {
            min_index = 2*i + 2;
            child = true;
        }
        //grandchildren
        if(4*i + 3 < nodes.size() and  nodes[4*i + 3] < nodes[min_index])
        {
            min_index = 4*i + 3;
            gchild = true;
        }
        if(4*i + 4 < nodes.size() and  nodes[4*i + 4] < nodes[min_index])
        {
            min_index = 4*i + 4;
            gchild = true;
        }
        if(4*i + 5 < nodes.size() and  nodes[4*i + 5] < nodes[min_index])
        {
            min_index = 4*i + 5;
            gchild = true;
        }
        if(4*i + 6 < nodes.size() and  nodes[4*i + 6] < nodes[min_index])
        {
            min_index = 4*i + 6;
            gchild = true;
        }
        if(gchild)
        {
            if(nodes[min_index] < nodes[i])
            {
                swap_nodes(i,min_index);
                if(nodes[parent(min_index)] < nodes[min_index])
                {
                    swap_nodes(min_index,parent(min_index));
                }
                trickle_down_min(min_index);
            }
        }
        else if(child)
        {
            if(nodes[min_index] < nodes[i])
            {
                swap_nodes(min_index,i);
            }
        }
        return;
    }
    void trickle_down_max(int i)
    {
        int max_index = i;
        bool child = false;
        bool gchild = false;
        //children
        if(2*i + 1 < nodes.size() and nodes[max_index] < nodes[2*i + 1])
        {
            max_index = 2*i + 1;
            child = true;
        }
        if(2*i + 2 < nodes.size() and nodes[max_index] < nodes[2*i + 2])
        {
            max_index = 2*i + 2;
            child = true;
        }
        //grandchildren
        if(4*i + 3 < nodes.size() and nodes[max_index] < nodes[4*i + 3])
        {
            max_index = 4*i + 3;
            gchild = true;
        }
        if(4*i + 4 < nodes.size() and nodes[max_index] < nodes[4*i + 4])
        {
            max_index = 4*i + 4;
            gchild = true;
        }
        if(4*i + 5 < nodes.size() and nodes[max_index] < nodes[4*i + 5])
        {
            max_index = 4*i + 5;
            gchild = true;
        }
        if(4*i + 6 < nodes.size() and nodes[max_index] < nodes[4*i + 6])
        {
            max_index = 4*i + 6;
            gchild = true;
        }
        if(gchild)
        {
            if(nodes[i] < nodes[max_index])
            {
                swap_nodes(i,max_index);
                if(nodes[max_index] < nodes[parent(max_index)])
                {
                    swap_nodes(max_index,parent(max_index));
                }
                trickle_down_max(max_index);
            }
        }
        else if(child)
        {
            if(nodes[i] < nodes[max_index])
            {
                swap_nodes(max_index,i);
            }
        }
        return;
    }
    

    void swap_nodes(int i,int j)
    {
        T tmp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = tmp;
        return;
    }

    void bubble_up_min(int i)
    {
        if(grandparent(i) >= 0)
        {
            if(nodes[i] < nodes[grandparent(i)])
            {
                swap_nodes(i,grandparent(i));
                bubble_up_min(grandparent(i));
            }
        }
        return;
    }

    void bubble_up_max(int i)
    {
        if(grandparent(i) >= 0)
        {
            if(nodes[grandparent(i)] < nodes[i])
            {
                swap_nodes(i,grandparent(i));
                bubble_up_max(grandparent(i));
            }
        }
        return;
    }

    void print()
    {
        for(int i = 0;i < nodes.size();i++)
        {
            cout << nodes[i] << " ";
        }
        cout << endl;
        return;

    }


    //insert an object in the heap in O(log n)
    void insert(T elem);

    //delete the minimum in O(log n)
    void deleteMin();

    //delete the maximum in O(log n)
    void deleteMax();

    //get the minimum in O(1) time
    T getMin();

    //get the maximum in O(1) time
    T getMax();


    void deleteElems(Predicate<T> &predObject)
    {
        vector<T> leftovers;
        while(nodes.size() != 0)
        {
            T elem = nodes[nodes.size() - 1];
            nodes.pop_back();
            if(!predObject.toDelete(elem))
            {
                leftovers.push_back(elem);
            }
        }
        for(int i = 0;i < leftovers.size();i++)
        {
            insert(leftovers[i]);
        }
        return;
    }

};

#endif 
                                                                                                                                                                                                                                                                                                                                                                                        minMaxHeap.cpp                                                                                      000644  000765  000024  00000003447 12671776641 014432  0                                                                                                    ustar 00sandesh                         staff                           000000  000000                                                                                                                                                                         #include "minMaxHeap.hpp"

template <class T>
minMaxHeap<T>::minMaxHeap()
{
    vector<T> nodes;
}

template <class T>
void minMaxHeap<T>::insert(T elem)
{
    if(nodes.empty())
    {
        nodes.push_back(elem);
        return;
    }
    else
    {
        nodes.push_back(elem);
        int elem_key = nodes.size() - 1;
        int parent_key = parent(elem_key);
        if(is_min_level(elem_key))
        {
            //inserted position on a min level
            if(nodes[parent_key] < nodes[elem_key])
            {
                // max level violation
                swap_nodes(parent_key,elem_key);
                bubble_up_max(parent_key);
            }
            else
            {
                // min level violation
                bubble_up_min(elem_key);
            }
        }
        else
        {
            if(nodes[elem_key] < nodes[parent_key])
            {
                swap_nodes(parent_key,elem_key);
                bubble_up_min(parent_key);
            }
            else
            {
                bubble_up_max(elem_key);
            }
        }
    }
    return;
}
            

template <class T>
void minMaxHeap<T>::deleteMin()
{
    nodes[0] = nodes[nodes.size() - 1];
    nodes.pop_back();
    trickle_down(0);
    return;
}

template <class T>
void minMaxHeap<T>::deleteMax()
{
    if(nodes[1] < nodes[2])
    {
        nodes[2] = nodes[nodes.size() - 1];
        nodes.pop_back();
        trickle_down(2);
    }
    else
    {
        nodes[1] = nodes[nodes.size() - 1];
        nodes.pop_back();
        trickle_down(1);
    }
    return;
}

template <class T>
T minMaxHeap<T>::getMin()
{
    return nodes[0];
}

template <class T>
T minMaxHeap<T>::getMax()
{
    if(nodes[1] < nodes[2])
    {
        return nodes[2];
    }
    else
    {
        return nodes[1];
    }
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         