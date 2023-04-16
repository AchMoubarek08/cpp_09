#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {return;}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src) { *this = src; return;}

BitcoinExchange::~BitcoinExchange() {return;}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & rhs){this->database = rhs.database; return *this;}

BitcoinExchange::BitcoinExchange(std::string filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::string date_str;
    float price;
    if (!infile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        date_str = line.substr(0, 10);
        price = std::stof(line.substr(11, line.size()));
        database[date_str] = price;
    }
    infile.close();
}

int check_values(std::string &date, float &val)
{
    int year;
    int mounth;
    int day;
    try
    {
    year = std::stoi(date.substr(0, 4));
    mounth = std::stoi(date.substr(6, 7));
    day = std::stoi(date.substr(8, 9));
    }
    catch(std::exception &e)
    {}
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return (1);
    if(val < 0 || val > 1000)
        return(1);
    if(year < 2009 || year > 2022 || mounth > 12 || mounth < 0 || day < 1 ||  day > 31)
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
        std::cerr << "Error: bad input => " << line << std::endl;
    if(check_values(date, val))
        std::cerr << "Error: bad input => " << line << std::endl;
    return(0);
}
void BitcoinExchange::exchange(std::string file)
{
    std::ifstream infile(file);
    if(!infile.is_open())
    {
        std::cerr << "error : cannot open file" << std::endl;
        return;
    }
    std::string line;
    std::getline(infile, line);
    while(std::getline(infile, line))
    {
        std::string date;
        char sep;
        float val;
        try
        {
            line.replace(line.find(','), 1, ".");
        }
        catch(std::exception &e)
        {}
        check_line(line, date, sep, val);
    }
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