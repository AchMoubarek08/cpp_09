#include "PmergeMe.hpp"

template <typename T>
void fill_container(T & container, int ac, char **av)
{
    for(int i = 1; i < ac; i++)
        container.push_back(Atoi(av[i]));
}

template <typename T>
void    merge_insert_sort(T & container)
{
    if (container.size() <= 1)
        return;
    T left;
    T right;
    typename T::iterator it = container.begin();
    typename T::iterator ite = container.end();
    typename T::iterator mid = it + (ite - it) / 2;
    left.insert(left.begin(), it, mid);
    right.insert(right.begin(), mid, ite);
    merge_insert_sort(left);
    merge_insert_sort(right);
    container.clear();
    typename T::iterator it_left = left.begin();
    typename T::iterator it_right = right.begin();
    while (it_left != left.end() && it_right != right.end())
    {
        if (*it_left < *it_right)
        {
            container.push_back(*it_left);
            it_left++;
        }
        else
        {
            container.push_back(*it_right);
            it_right++;
        }
    }
    container.insert(container.end(), it_left, left.end());
    container.insert(container.end(), it_right, right.end());
}

template <typename T>
void print(const T& container)
{
    int i = 0;
    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
    {
        if(i++ == 6)
        {
            std::cout << "[...]";
            break;
        }
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(int ac, char **av)
{
    if(ac <= 1)
    {
        std::cout << "two args or more" << std::endl;
        return(1);
    }
    if(check_args(ac, av))
        return(1);
    std::vector <int> vec;
    fill_container(vec, ac, av);
    std::vector <int>vector(vec);
    std::cout << "before : ";
    print(vector);
    clock_t start = clock();
    merge_insert_sort(vector);
    clock_t end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "after : ";
    print(vector);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << time << " us\n";
    std::deque <int>deque(vec.begin(), vec.end());
    std::cout << "before : ";
    print(deque);
    start = clock();
    merge_insert_sort(deque);
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "after : ";
    print(deque);
    std::cout << "Time to process a range of " << deque.size() << " elements with std::deque: " << time << " us\n";
}