/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:54:08 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/29 10:06:06 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <sstream>
#include <algorithm>

class RPN
{
	public:
		RPN();
		RPN(RPN const &);
		RPN &operator=(RPN const &);
		~RPN();
		int ft_rpn(int argc, char *argv[]);
};
