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
	// constructors
		BitcoinExchange();
		BitcoinExchange(std::string filename);
		BitcoinExchange(BitcoinExchange const & src);
		~BitcoinExchange();
	// operators
		BitcoinExchange & operator=(BitcoinExchange const & rhs);
	// methods
		double get_price(std::string date_str);
		void exchange(std::string input_filename);
};


#endif