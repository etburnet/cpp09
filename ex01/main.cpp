/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:54:10 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/28 15:56:54 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char *argv[])
{
	int i = 0;
	int tmp = 0;
	int len = 0;
	std::stack<int> pile;
	std::string str;
	
	if (argc != 2)
		return (std::cerr << "Error: 1 arg needed" << std::endl, 1);
	while (argv[1][i])
	{
		if (!isdigit(argv[1][i]) && argv[1][i] != '*' && argv[1][i] != '-' && argv[1][i] != '+' && argv[1][i] != '/' && argv[1][i] != ' ')
			return (std::cerr << "Error: wrong argument => " << argv[1][i] << std::endl, 1);
		i++;
	}
	i = 0;
	str = argv[1];
	if (!str.empty())
	len = strlen(str.c_str());
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	if (len < 3)
		return (std::cerr << "Error: wrong input size" << std::endl, 1);
	i = 0;
	while (i < len - 1)
	{
		while (isdigit(str[i]))
		{
			tmp = str[i] - 48;
			pile.push(tmp);
			i++;
		}
		tmp = pile.top();
		pile.pop();
		while (!isdigit(str[i]) && str[i])
		{
			if (str[i] == '+')
				tmp += pile.top();
			if (str[i] == '-')
				tmp -= pile.top();
			if (str[i] == '*')
				tmp *= pile.top();
			if (str[i] == '/')
				tmp /= pile.top();
			pile.pop();
			i++;
		}
		pile.push(tmp);
		i++;
	}
	std::cout << "size:" << pile.size() << std::endl;
	if (pile.size() > 1)
		return (std::cerr << "Error: with operators" << std::endl, 1);
	std::cout << pile.top() << std::endl;
	return (0);
}