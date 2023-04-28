
#include "PmergeMe.hpp"

int str_is_digit(char *av)
{
    int i = 0;
    while (av[i])
    {
        if (!isdigit(av[i]))
            return (0);
        i++;
    }
    return (1);
}

int Atoi(const char* str)
{
    int sign = 1;
    int result = 0;
    while (*str == ' ') {
        str++;
    }
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        sign = 1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

bool is_duplicate(const char *s1, const char *s2)
{
    std::string str1(s1);
    std::string str2(s2);
    return str1 == str2;
}

bool check_dup(int ac, char **av)
{
    for(int i = 0; i < ac; i++)
    {
        for(int j = i + 1; j < ac; j++)
        {
            if(is_duplicate(av[i], av[j]))
                return(true);
        }
    }
    return(false);
}

int check_args(int ac, char **av)
{
    for(int i = 1; i < ac; i++)
    {
        if(!str_is_digit(av[i]))
        {
            std::cerr << "error : positive integers only." << std::endl;
            return (1);
        }
        if(check_dup(ac, av))
        {
            std::cerr << "error : duplicated integers" << std::endl;
            return (1);
        }
    }
    return (0);
}
