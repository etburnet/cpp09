/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:44 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/29 10:04:22 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
#include <string.h>

struct data
{
	std::string date;
	std::string value;
	std::map<std::string, float> DateExRate;
	std::string minDate;
	float val_f;
};

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &);
		BitcoinExchange &operator=(BitcoinExchange const &);
		~BitcoinExchange();
		int ft_btc_ex(char *argv[]);
		int ft_error_handling(data &d, std::string tmp);
		int ft_open_store_db(data &d);
};
