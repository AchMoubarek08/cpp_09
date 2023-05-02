#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <iomanip>


class BitcoinExchange {
	private:
		std::map<std::string, double> database;
	public:
		BitcoinExchange();
		BitcoinExchange(std::string filename);
		BitcoinExchange(BitcoinExchange const & src);
		~BitcoinExchange();
		BitcoinExchange & operator=(BitcoinExchange const & rhs);
		double get_price(std::string date_str);
		void exchange(std::string input_filename);
};

int check_line(std::string line, std::string &date, char &sep, float &val);

#endif