/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:42 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/28 11:09:40 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (std::cerr << "Error: input file needed!" << std::endl, 1);
	BitcoinExchange btcex;
	return (btcex.ft_btc_ex(argv));
}
	