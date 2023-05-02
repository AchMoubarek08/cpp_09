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
        // two ways to insert into map (2nd is more efficient):
        // database[date_str] = price;
        database.insert(std::make_pair(date_str, price));
    }
    infile.close();
}

double  BitcoinExchange::get_price(std::string date_str) 
{
    std::map<std::string, double>::const_iterator it = database.find(date_str);
    if (it != database.end())
        return it->second;
    else 
    {
        std::map<std::string, double>::const_iterator lower_it = database.lower_bound(date_str);
        if (lower_it == database.begin())
            return 0.0;
        else 
        {
            --lower_it;
            return lower_it->second;
        }
    }
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
        if(check_line(line, date, sep, val))
            continue;
        double prix = get_price(date);
        double exchange = 0.0;
        if (prix > 0.0) {
            exchange = val * prix;
        }
        std::cout << date << " => " << val << " = " << exchange << std::endl;
    }
}
