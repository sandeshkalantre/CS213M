prob1.cpp                                                                                           000644  000765  000024  00000004176 12704147706 013415  0                                                                                                    ustar 00sandesh                         staff                           000000  000000                                                                                                                                                                         #include <iostream>
#include <set>
#include <vector>
#include <string>
#include "A_star.hpp"

using namespace std;

class node
{
    public:
        string word;
        int f,g,h;

        node(string tmp_word)
        {
            word = tmp_word;
            f = 0;
            g = 0;
            h = 0;
        }

        int calculate_h(node end)
        {
            int ham = 0;
            for(int i = 0;i < word.length();i++)
            {
                if(word[i] != end.word[i])
                {
                    ham++;
                }
            }
            return ham/2;
        }

        bool operator<(const node& n) const
        {
            if(f < n.f)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool operator==(const node& n) const
        {
            if(word == n.word)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool operator!=(const node& n) const
        {
            if(word == n.word)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        
        vector<node> get_neighbours() const
        {
            vector< node > neigh;
            string swap_word = word;
            string ini_word = word;
            int len = word.length();
            for(int i = 0;i < len;i++)
            {
                for(int j = i+1;j < len ;j++)
                {
                    char ch = swap_word[i];
                    swap_word[i] = swap_word[j];
                    swap_word[j] = ch;

                    node tmp_node(swap_word);
                    neigh.push_back(tmp_node);
                    swap_word = ini_word;
                }
            }
            return neigh;
        }

};

int main()
{
    string inp1,inp2;
    cin >> inp1 >> inp2;
    node start(inp1);
    node end(inp2);
    A_star<node> my_A_star;
    cout << my_A_star.A_star_solve(start,end) << endl;

    return 0;
} 




                                                                                                                                                                                                                                                                                                                                                                                                  prob2.cpp                                                                                           000644  000765  000024  00000012473 12704147706 013415  0                                                                                                    ustar 00sandesh                         staff                           000000  000000                                                                                                                                                                         #include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include "A_star.hpp"

using namespace std;

class node
{
    public:
        vector<int> state;
        int f,g,h;
        
        void print_state()
        {
            for(int i = 0; i < 9;i++)
            {
                cout << state[i];
            }
            cout << endl;
        }
        node(vector<int> tmp_state)
        {
            state = tmp_state;
            f = 0;
            g = 0;
            h = 0;
        }

        int calculate_h(node end)
        {
            return 0;
        }

        bool operator<(const node& n) const
        {
            if(f < n.f)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool operator==(const node& n) const
        {
            if(state == n.state)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool operator!=(const node& n) const
        {
            if(state == n.state)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        //utility swap
        vector<int> swap_ele(int i,int j,vector<int> state) const
        {
            vector<int> result = state;
            int tmp = result[i];
            result[i] = result[j];
            result[j] = tmp;
            return result;
        }
        
        vector<node> get_neighbours() 
        {
            vector<node> neigh;
            //find the position of zero
            int zero_pos;
            for(int i = 0;i < 9;i++)
            {
                if(this->state[i] == 0)
                {
                    zero_pos = i;
                    break;
                }
            }
            vector<int> tmp_state = state;
            if(zero_pos == 0)
            {
                node tmp_node(swap_ele(0,1,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(0,1,tmp_state));
                neigh.push_back(tmp_node1);
            }
            else if(zero_pos == 1)
            {
                node tmp_node(swap_ele(0,1,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(1,2,tmp_state));
                neigh.push_back(tmp_node1);
                node tmp_node2(swap_ele(1,4,tmp_state));
                neigh.push_back(tmp_node2);
            }
            else if(zero_pos == 2)
            {
                node tmp_node(swap_ele(2,1,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(2,4,tmp_state));
                neigh.push_back(tmp_node1);
            }
            else if(zero_pos == 3)
            {
                node tmp_node(swap_ele(3,0,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(3,4,tmp_state));
                neigh.push_back(tmp_node1);
                node tmp_node2(swap_ele(3,6,tmp_state));
                neigh.push_back(tmp_node2);
            }
            else if(zero_pos == 4)
            {
                node tmp_node(swap_ele(4,1,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(4,3,tmp_state));
                neigh.push_back(tmp_node1);
                node tmp_node2(swap_ele(4,5,tmp_state));
                neigh.push_back(tmp_node2);
                node tmp_node3(swap_ele(4,7,tmp_state));
                neigh.push_back(tmp_node3);
            }
            else if(zero_pos == 5)
            {
                node tmp_node(swap_ele(5,2,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(5,4,tmp_state));
                neigh.push_back(tmp_node1);
                node tmp_node2(swap_ele(5,8,tmp_state));
                neigh.push_back(tmp_node2);
            }
            else if(zero_pos == 6)
            {
                node tmp_node(swap_ele(6,3,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(6,7,tmp_state));
                neigh.push_back(tmp_node1);
            }
            else if(zero_pos == 7)
            {
                node tmp_node(swap_ele(7,4,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(7,6,tmp_state));
                neigh.push_back(tmp_node1);
                node tmp_node2(swap_ele(7,8,tmp_state));
                neigh.push_back(tmp_node2);
            }
            else if(zero_pos == 8)
            {
                node tmp_node(swap_ele(8,5,tmp_state));
                neigh.push_back(tmp_node);
                node tmp_node1(swap_ele(8,7,tmp_state));
                neigh.push_back(tmp_node1);
            }
            return neigh;
        }

};

int main()
{
    vector<int> inp;
    for(int i = 0;i < 9;i++)
    {
        int tmp;
        cin >> tmp;
        inp.push_back(tmp);
    }

    node start(inp);
    //start.print_state();

    vector<int> end_state;
    for(int i = 0;i < 8;i++)
    {
        end_state.push_back(i+1);
    }
    end_state.push_back(0);
    node end(end_state);

    A_star<node> my_A_star;
    cout << my_A_star.A_star_solve(start,end) << endl;

    return 0;
} 




                                                                                                                                                                                                     A_star.hpp                                                                                          000644  000765  000024  00000004476 12704147706 013613  0                                                                                                    ustar 00sandesh                         staff                           000000  000000                                                                                                                                                                         #include <vector>
#include <algorithm>
#include <list>

using namespace std;

template<class T>
class A_star
{
    public:
        //returns the minimum cost
        //I have assumed all costs are integers
        int A_star_solve(T start, T end)
        {
            list<T> open;
            list<T> closed;

            //initialization 
            start.g = 0;
            open.push_back(start);
            while(!open.empty())
            {
                typename list<T>::iterator it_current = min_element(open.begin(),open.end());
                T current = *it_current;
                if(*it_current == end)
                {
                    //golden bullet
                    return (*it_current).f;
                }

                vector<T> neighbours = (*it_current).get_neighbours();
                closed.push_back(*it_current);
                open.erase(it_current);

                for(int i = 0;i < neighbours.size();i++)
                {
                    T v = neighbours[i];
                    //v.print_state();
                    if(count(closed.begin(),closed.end(),v) == 0)
                    {
                        typename list<T>::iterator it = find(open.begin(),open.end(),v);
                        if(count(open.begin(),open.end(),v) == 0)
                        {
                            //1 is the cost of going from current to neighbours of current
                            //here I have assumed it to be 1, in general one can have a function inside class T
                            v.g = current.g + 1;
                            v.h = v.calculate_h(end);
                            v.f = v.g + v.h;
                            open.push_back(v); 
                        }
                        else
                        {
                            int tent = current.g + 1;
                            if(tent < (*it).g)
                            {
                                T tmp_node = *it;
                                tmp_node.g = tent;
                                tmp_node.f = (*it).g + (*it).h;
                                open.erase(it);
                                open.push_back(tmp_node);
                            }

                        }
                    }
                }
             
            }
            return -1;
        }
};
                                                                                                                                                                                                  README.txt                                                                                          000644  000765  000024  00000000750 12704147706 013356  0                                                                                                    ustar 00sandesh                         staff                           000000  000000                                                                                                                                                                         For the first problem, I have used the heurestic as half of the hamming distance between the two strings since it seemed plausible to expect that many swaps.

For the second problem, as a first try I used h  = 0 as heurestic.

I have used vector as a data stucture to store the open and closed set in A-star. Ideally one should be using something like a BST,RB-tree which is present as set in STL. However, I had the functions set API behaving unexpectedly and hence I dropped the idea. 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        