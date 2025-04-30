/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:01:53 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/30 14:35:08 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void ft_ford_johnson_list(std::list<int>& tab)
{
	std::list<int> big;
	std::list<int> lil;

	if (tab.size() <= 1)
		return ;
	std::list<int>::iterator it = tab.begin();
	while (it != tab.end()) 
	{
		std::list<int>::iterator next = it;
		++next;
		if (next == tab.end()) 
		{
			lil.push_back(*it);
			break;
		}
		if (*it > *next) 
		{
			big.push_back(*it);
			lil.push_back(*next);
		}
		else
		{
			big.push_back(*next);
			lil.push_back(*it);
		}
		++next;
		it = next;
	}
	ft_ford_johnson_list(big);
	std::list<int>::iterator it_l = lil.begin();
	for (size_t i = 0; i < lil.size(); i++)
	{
		std::list<int>::iterator it = big.begin();
		while (it != big.end() && *it < *it_l)
			++it;
		big.insert(it, *it_l);
		++it_l;
	}
	tab = big;
}

void ft_ford_johnson_vector(std::vector<int>& tab)
{
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
				big.push_back(tab[i]);
				lil.push_back(tab[i + 1]);
			}
			else
			{
				big.push_back(tab[i + 1]);
				lil.push_back(tab[i]);
			}
		}
	}
	ft_ford_johnson_vector(big);
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
	std::vector<int> v_tab;
	std::vector<int> v_tab_dup;
	std::list<int> l_tab;
	std::list<int> l_tab_dup;

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
		v_tab.push_back(stol);
		l_tab.push_back(stol);
		len = i;
	}
	v_tab_dup = v_tab;
	l_tab_dup = l_tab;
	clock_t debut = clock();
	ft_ford_johnson_vector(v_tab);
	clock_t fin_vector = clock();
	clock_t debut2 = clock();
	ft_ford_johnson_list(l_tab);
	clock_t fin_list = clock();
	std::cout << "Before: ";
	for (size_t i = 0; i < v_tab_dup.size(); i++)
	{
		std::cout << v_tab_dup[i];
		if (i != v_tab_dup.size())
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "After: ";
	for (size_t i = 0; i < v_tab.size(); i++)
	{
		std::cout << v_tab[i];
		if (i != v_tab.size())
			std::cout << " ";
	}
	std::cout << std::endl;
	double ex_vector = (double(fin_vector - debut) / CLOCKS_PER_SEC) * 1e3;
	double ex_list = (double(fin_list - debut2) / CLOCKS_PER_SEC) * 1e3;
	std::cout << "Time to process a range of " << v_tab.size() << " elements with std::vector : " << ex_vector << " ms" << std::endl;
	std::cout << "Time to process a range of " << v_tab.size() << " elements with std::list : " << ex_list << " ms" << std::endl;
	return (0);
}

	// std::cout << "Before LIST: ";
	// std::list<int>::iterator it_t_d = l_tab_dup.begin();
	// for (size_t i = 0; i < l_tab_dup.size(); i++)
	// {
	// 	std::cout << *it_t_d;
	// 	if (i != l_tab_dup.size())
	// 		std::cout << " ";
	// 	++it_t_d;
	// }
	// std::cout << std::endl;
	// std::cout << "After LIST: ";
	// std::list<int>::iterator it_t = l_tab.begin();
	// for (size_t i = 0; i < l_tab.size(); i++)
	// {
	// 	std::cout << *it_t;
	// 	if (i != l_tab.size())
	// 		std::cout << " ";
	// 	++it_t;
	// }
	// std::cout << std::endl;