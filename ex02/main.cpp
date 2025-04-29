/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:01:53 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/29 16:31:13 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void ft_ford_johnson(std::vector<int>& tab)
{
	std::vector<std::pair<int, int> > vec;
	std::vector<int> big;
	std::vector<int> lil;

	if (tab.size() <= 1)
		return ;
	for (size_t i = 0; i < tab.size(); i += 2)
	{
		if (i + 1 >= tab.size())
			lil.push_back(tab[i]);
		else
		{
			if (tab[i] > tab[i + 1])
			{
				vec.push_back(std::make_pair(tab[i], tab[i + 1]));
				big.push_back(tab[i]);
				lil.push_back(tab[i + 1]);
			}
			else
			{
				vec.push_back(std::make_pair(tab[i + 1], tab[i]));
				big.push_back(tab[i + 1]);
				lil.push_back(tab[i]);
			}
		}
	}
	ft_ford_johnson(big);
	for (size_t i = 0; i < lil.size(); i++)
	{
		std::vector<int>::iterator it = big.begin();
		while (it != big.end() && *it < lil[i])
			++it;
		big.insert(it, lil[i]);
	}
	tab = big;
}

int main(int argc, char *argv[])
{
	long int stol;
	int j;
	int len;
	std::vector<int> tab;
	std::vector<int> tab_dup;
	
	if (argc < 2)
		return (std::cerr << "Error: to low args" << std::endl, 1);
	for (int i = 1; i < argc; i++)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!isdigit(argv[i][j]) && argv[i][j] != '+' && argv[i][j] != '-')
				return (std::cerr << "Error: not a digital value => " << argv[i][j] << std::endl, 1);
			j++;
		}
		stol = strtol(argv[i], NULL, 10);
		if (stol == 0 && argv[i][0] != '0')
			return (std::cerr << "Error: Bad input value" << std::endl, 1);
		if (stol == LONG_MIN || stol == LONG_MAX)
			return (std::cerr << "Error: value overflow" << std::endl, 1);
		tab.push_back(stol);
		len = i;
	}
	tab_dup = tab;
	ft_ford_johnson(tab);
	std::cout << "Before: ";
	for (size_t i = 0; i < tab_dup.size(); i++)
	{
		std::cout << tab_dup[i];
		if (i != tab_dup.size())
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "After: ";
	for (size_t i = 0; i < tab.size(); i++)
	{
		std::cout << tab[i];
		if (i != tab.size())
			std::cout << " ";
	}
	std::cout << std::endl;
	return (0);
}


//ajouter fonction list et timming 