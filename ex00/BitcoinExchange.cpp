/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:45 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/28 12:01:11 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	operator=(other);
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

int BitcoinExchange::ft_open_store_db(data &d)
{
	std::string tmp;
	std::ifstream dbFile("data.csv");
	
	if (!dbFile.is_open())
		return (std::cerr << "Error: opening file: data.csv" << std::endl, 1);
	while (getline(dbFile, tmp))
	{
		d.date = tmp.substr(0, 10);
		d.value = tmp.substr(11);
		float num_float = atof(d.value.c_str());
		d.DateExRate.insert(std::make_pair(d.date, num_float));
	}
	return (0);
}

int BitcoinExchange::ft_error_handling(data &d, std::string tmp)
{
	if (std::string::npos == tmp.find('|') || tmp.size() < 11)
		return (std::cerr << "Error: invalid inpuut format." << std::endl, 1);
	d.date = tmp.substr(0, 10);
	if (!isdigit(d.date[0]))
		return (1);
	struct tm tm;
	if (strptime(d.date.c_str(), "%Y-%m-%d", &tm) == NULL)
		return (std::cerr << "Error: Wrong date format: " << d.date << std::endl, 1);
	d.value = tmp.substr(13);
	d.val_f = atof(d.value.c_str());
	if (d.val_f < 0)
		return (std::cerr << "Error: not a positive number." << std::endl, 1);
	if (d.val_f > 1000)
		return (std::cerr << "Error: too large a number." << std::endl, 1);
	return (0);
}

int BitcoinExchange::ft_btc_ex(char *argv[])
{
	data d;
	std::string tmp;
	std::ifstream inFile(argv[1]);

	if (!inFile.is_open())
		return (std::cerr << "Error: opening file: " << argv[1] << std::endl, 1);
	if (ft_open_store_db(d) == 1)
		return (1);
	d.minDate = d.DateExRate.begin()->first;
	while (getline(inFile, tmp))
	{
		while (1)
		{
			if (ft_error_handling(d, tmp))
				break;
			std::map<std::string, float>::const_iterator it = d.DateExRate.find(d.date);
			if (it == d.DateExRate.end())
			{
				int year, month, day;
				sscanf(d.date.c_str(), "%d-%d-%d", &year, &month, &day);
				struct tm date_s;
				date_s.tm_sec = 0;
				date_s.tm_min = 0;
				date_s.tm_hour = 0;
				date_s.tm_mday = day;
				date_s.tm_mon = month - 1;
				date_s.tm_year = year - 1900;
				date_s.tm_wday = 0;
				date_s.tm_yday = 0;
				date_s.tm_isdst = -1;
				time_t t = mktime(&date_s);
				t -= 24 * 60 * 60;
				struct tm *new_date = localtime(&t);
				char buffer[11];
				sprintf(buffer, "%04d-%02d-%02d", 
					new_date->tm_year + 1900, 
					new_date->tm_mon + 1, 
					new_date->tm_mday);
				if (strcmp(buffer, d.minDate.c_str()) < 0)
				{
					std::cerr << "Error: date trop ancienne!" << std::endl;
					break ;
				}
				while (d.DateExRate.find(buffer) == d.DateExRate.end())
				{
					t -= 24 * 60 * 60;
					new_date = localtime(&t);
					sprintf(buffer, "%04d-%02d-%02d", 
						new_date->tm_year + 1900, 
						new_date->tm_mon + 1, 
						new_date->tm_mday);
				}
				it = d.DateExRate.find(buffer);
			}
			float calcul = d.val_f * it->second;
			std::cout << d.date << " => " << d.value << " = " << calcul << std::endl;	
			break;
		}
	}
	return (1);
}
