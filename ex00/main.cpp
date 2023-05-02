#include "BitcoinExchange.hpp"

bool str_is_digit(const std::string& s) 
{
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) 
    {
        if (!isdigit(*it))
            return true;
    }
    return false;
}

int check_values(std::string &date, float &val)
{
    int year;
    int mounth;
    int day;
    if(str_is_digit(date.substr(0, 4)) || str_is_digit(date.substr(5, 2)) || str_is_digit(date.substr(8, 2)))
        return(1);
    try
    {
    year = std::stoi(date.substr(0, 4));
    mounth = std::stoi(date.substr(5, 2));
    day = std::stoi(date.substr(8, 2));
    }
    catch(std::exception &e)
    {}
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return (1);
    if(val < 0 || val > 1000)
    {
        if(val < 0)
            return(2);
        else if(val > 1000)
            return(3);
    }
    if(year < 2009 || year > 2022 || mounth > 12 || mounth < 1 || day < 1 ||  day > 31)
        return(1);
    return(0);
}
int check_line(std::string line, std::string &date, char &sep, float &val)
{
    std::string check;
    std::istringstream iss(line);
    if (!(iss >> date >> sep >> val) || sep != '|')
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return(1);
    }
    if((iss >> check))
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return 1;
    }
    if(check_values(date, val) == 2)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return 1;
    }
    else if(check_values(date, val) == 3)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return 1;
    }
    else if(check_values(date, val))
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return 1;
    }
    return(0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <filename>" << std::endl;
        return 1;
    }
    BitcoinExchange a("data.csv");
    a.exchange(av[1]);
}