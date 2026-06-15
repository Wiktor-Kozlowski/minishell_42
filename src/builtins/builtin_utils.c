/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:49:35 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_secret(void)
{
	ft_putendl_fd("⠀⠀⠀⠀⠀⣀⡴⠖⠒⠒⢒⣒⡖⠒⠒⠒⠒⠒⠒⠶⠶⠤⣤⣀⣀⠀⠀⠀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⣴⠋⠀⠀⠤⣪⣝⡲⠯⠭⠥⠀⠀⠀⠀⠀⣀⣐⣒⡒⠉⠙⢦⡀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⣼⠃⠀⠈⠰⠫⠋⣀⣀⣀⣀⠀⠃⠀⠀⠀⠸⠀⠀⠀⠈⠆⠀⠀⢧⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⣠⡾⠁⠀⡀⠠⠄⢰⣿⠿⠿⢯⣍⣙⣶⠀⠀⢀⣠⣶⣾⣿⠶⠆⠤⠤⢜⢷⡄", STDOUT_FILENO);
	ft_putendl_fd("⡾⢻⢡⡞⠋⣽⠛⠲⠤⡤⠴⠋⠀⠀⠉⠁⠀⠀⠈⣿⠁⠀⢀⣀⣠⠶⠶⣽⣵⣿", STDOUT_FILENO);
	ft_putendl_fd("⣇⢠⢸⡥⠶⣟⠛⠶⣤⣀⠀⠀⠀⢲⡖⣂⣀⠀⠀⠈⢳⣦⡀⠉⠉⣽⡄⠰⣻⣿", STDOUT_FILENO);
	ft_putendl_fd("⠙⣮⡪⠁⠀⠻⣶⣄⣸⣍⠙⠓⠶⣤⣥⣉⣉⠀⠠⠴⠋⠁⣈⣥⣴⣿⡇⠈⣽⠃", STDOUT_FILENO);
	ft_putendl_fd("⠀⠈⢻⡄⠀⠀⠙⣆⢹⡟⠷⣶⣤⣇⣀⠉⠙⡏⠉⢻⡟⢉⣹⣅⣼⣿⣇⠂⡏⢠", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠻⣄⠀⠀⠈⠻⢦⡀⠀⣽⠉⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⡐⡇⠌", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⠙⢦⣀⠄⡀⢄⡙⠻⠧⣤⣀⣀⣿⠀⠀⣿⢀⣼⣃⣾⣼⠟⡍⠀⡇⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠉⠓⢮⣅⡚⠵⣒⡤⢄⣉⠉⠉⠉⠉⠉⠉⠉⢀⡢⠤⠀⣐⣷⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠳⢦⣄⡉⠙⠛⠃⠀⠀⠀⠀⠉⠁⢠⠂⠀⠀⡿⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠲⠶⢤⣤⣀⣀⣀⣀⣆⣀⡤⠞⠁⠀", STDOUT_FILENO);
}

static void	print_monke_1(void)
{
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠋⠉⠉⠉⠛⠛⠓⠈⠉⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⣠⡶⢉⣀⣄⣀⠀⢀⣀⣀⡀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢉⣾⠟⣰⠏⠉⣽⣿⢊⣻⡿⠿⠛⢷⣶⡀⠀⢛⣿⣿⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⢠⡾⠋⢸⣧⣤⣾⡴⠀⠀⠉⠠⣤⣾⣧⡻⠃⠀⠀⢿⣿⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢉⢀⣿⠁⠀⠈⠉⠈⠕⠀⠀⠀⠀⠀⠐⢭⡛⠋⠀⠀⠀⠈⢻⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢘⣼⠃⠀⠀⣀⡀⠄⠀⣠⠘⢧⡴⢢⡀⠀⢢⡀⠀⠀⠀⠀⢴⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣯⣽⣿⣿⣿⣿⣿⣿⣿⡇⠺⣿⠃⠠⣄⢻⡇⠀⣴⣿⣿⣧⣿⣾⣇⠀⢨⣿⣤⡄⠀⠀⢸⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡗⠀⣿⣧⡆⠁⠙⠆⢠⢻⡿⠿⠟⡻⡿⠿⠆⠸⣟⣃⣣⣴⡦⠹⣿⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣾⢸⣿⡟⣿⠐⣩⣾⣧⣶⣤⣴⣬⣟⡀⠀⠀⠀⠈⠻⣿⣿⣷⠘⠘⠛⠛⠽"
		"⠋⠉⠟⢛⣩⣭⣉⣿", STDOUT_FILENO);
	ft_putendl_fd("⠾⠿⡿⠛⠛⠛⣻⣿⣿⣿⣿⣿⠿⠁⠆⢸⣿⡇⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡄⢢⠀⠹⠌⠛⣿⣰⣾⣿⣿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠠⡄⢸⣿⡇⡆⢻⣿⣿⣿⣿⣿⣿⡛⠝⠉⠀⠁⠀⠀⠐⠀⠀⠈⢯⣙⡿⢿⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠁⣸⣿⣿⡇⠄⠿⣿⣿⣿⣿⣿⣿⡦⠀⠀⢀⡀⣀⠀⠀⠀⠀⠀⠉⠛⢾⣿"
		"⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⠟⣻⣿⣿⣿⣿⢻⣿⡿⠇⣰⣿⣿⣿⣿⣴⢮⣈⡟⡟⠻⠿⠉⠀⠀⢠⣬⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠙"
		"⢿⣿⣿⣿⣿⣿⡿⢿", STDOUT_FILENO);
}

static void	print_monke_2(void)
{
	ft_putendl_fd("⣿⣿⣿⢏⢌⠍⡩⠩⠈⠉⠠⠉⣠⣾⡿⣿⣛⣻⣿⡿⣧⣍⣾⣶⣶⣾⣶⠀⠀⠸⠝⠛⢆⡀⠀⠀⠀⠀⠀⠀⠀⠀"
		"⠀⠙⠿⢿⠻⠿⠈⠀", STDOUT_FILENO);
	ft_putendl_fd("⣉⠋⠑⠁⠉⠈⠐⠁⠀⠀⣠⣾⣿⣻⠋⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠻⣶⣄⠀⠀⠀⠀⠀⠀"
		"⠀⠀⠀⠹⠷⠚⠒⠒", STDOUT_FILENO);
	ft_putendl_fd("⠿⠴⠡⠮⠼⠠⠂⠤⢠⣾⣿⣿⢾⣿⡴⠋⠴⠁⢉⠐⠛⣿⢿⠿⣿⠿⣿⣿⣿⣷⣦⡀⠀⠀⠀⢿⣿⣷⣀⣀⠀⠀"
		"⠀⠀⠀⢀⡀⠀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⣀⣀⠐⠀⠂⠂⠀⠀⢹⣿⣿⣷⡿⣿⢠⠥⠄⠀⢡⠂⠀⣠⠝⢹⡿⣧⣨⡟⠿⣙⣭⠉⡀⣀⡀⠀⠘⣿⡿⢿⡄⠀"
		"⠀⠀⠀⠀⠡⠀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⡀⢀⡀⠀⠀⠀⠀⠁⣾⣿⡿⣭⣶⣿⠞⡁⣶⣿⣿⣿⣿⣿⣴⣾⣽⣿⣿⣿⣶⣿⣷⣿⣿⣿⣷⠀⠀⢹⣿⣮⡌⣀"
		"⠀⠀⠀⠀⠀⠆⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠘⠛⠁⣰⣿⡇⠀⣿⣿⣾⡿⣩⣾⣘⣸⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠘⠛⣿⣟"
		"⠀⠀⠀⠀⠀⠀⡀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⠉⠈⠀⣠⣿⣿⢋⠞⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠼⣿⣝"
		"⣦⢚⢀⠀⠀⢠⠙⠛", STDOUT_FILENO);
	ft_putendl_fd("⣀⠀⠀⠀⠀⠀⠀⣿⣿⡿⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⢹⣯"
		"⠋⠈⢸⡟⡥⢪⠰⠦", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣶⣶⣤⣼⣿⢛⣿⢳⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣠⣼⣿⡯"
		"⠄⠀⢸⠇⠀⠘⠂⠀", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣟⣼⣻⠈⠉⣸⣿⣿⢟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢻⣿⣿⠁"
		"⠀⠀⠈⠀⡀⣀⢠⣴", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⠟⠁⠠⣿⣿⠟⠁⡼⢻⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢹⠈⠀"
		"⣀⠁⠀⠀⠀⠁⠈⠈", STDOUT_FILENO);
	ft_putendl_fd("⣿⡿⠟⠁⠀⠀⢠⣟⡍⠀⠈⣥⡟⢡⣿⡾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠙⣤"
		"⠫⠄⠀⠀⠀⠀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("Are you sure?", STDOUT_FILENO);
}

void	print_monke(void)
{
	print_monke_1();
	print_monke_2();
}
