/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:42 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/25 16:02:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	std::map<std::string, float> DateExRate;
	std::string tmp;
	std::string date;
	std::string value;

	if (argc != 2)
		return (std::cerr << "Error: input file needed!" << std::endl, 1);
	std::ifstream inFile(argv[1]);
	std::ifstream dbFile("data.csv");
	if (!dbFile.is_open())
		return (std::cerr << "Error: opening file: data.csv" << std::endl, 1);
	if (!inFile.is_open())
		return (std::cerr << "Error: opening file: " << argv[1] << std::endl, 1);
	while (getline(dbFile, tmp))
	{
		date = tmp.substr(0, 10);
		value = tmp.substr(11);
		float num_float = atof(value.c_str());
		DateExRate.insert(std::make_pair(date, num_float));
	}
	while (getline(inFile, tmp))
	{
		while (1)
		{
			if (std::string::npos == tmp.find('|') || tmp.size() < 11)
			{
				std::cerr << "Error: invalid inpuut format." << std::endl;
				break;
			}
			date = tmp.substr(0, 10);
			if (!isdigit(date[0]))
				break;
			struct tm tm;
			if (strptime(date.c_str(), "%Y-%m-%d", &tm) == NULL)
			{

				std::cerr << "Error: Wrong date format: " << date << std::endl;
				break;
			}
			value = tmp.substr(13);
			float val_f = atof(value.c_str());
			if (val_f < 0)
			{
				std::cerr << "Error: not a positive number." << std::endl;
				break;
			}
			if (val_f > 1000)
			{
				std::cerr << "Error: too large a number." << std::endl;
				break;
			}
			std::map<std::string, float>::const_iterator it = DateExRate.find(date);
			if (it == DateExRate.end())
			{
				// std::cout << "AVANT: " << date << std::endl;
				int year, month, day;
				sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
				struct tm date_s;
				date_s.tm_year = year;
				date_s.tm_mon  = month;
				date_s.tm_mday = day;
				std::cout << "DECOMPO: " << year << " " << month << " " << day << std::endl;
				std::cout << "DECOMPO2: " << date_s.tm_year << " " << date_s.tm_mon << " " << date_s.tm_mday << std::endl;
				time_t t = mktime(&date_s);
				t -= 24 * 60 * 60;
				struct tm *new_date = localtime(&t);
				char buffer[11];
				sprintf(buffer, "%04d-%02d-%02d", 
					new_date->tm_year, 
					new_date->tm_mon, 
					new_date->tm_mday);
				std::cout << "Date: " << buffer << std::endl;
				while (DateExRate.find(buffer) == DateExRate.end())
				{
					t -= 24 * 60 * 60;
					new_date = localtime(&t);
					sprintf(buffer, "%04d-%02d-%02d", 
						new_date->tm_year, 
						new_date->tm_mon, 
						new_date->tm_mday);
				}
				it = DateExRate.find(buffer);
			}
			float calcul = val_f * it->second;
			std::cout << date << " => " << value << " = " << calcul << std::endl;	
			break;
		}
	}
	return (1);
}
	