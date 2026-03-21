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
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠋⠉⠉⠉⠛⠛⠓⠈⠉⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⣠⡶⢉⣀⣄⣀⠀⢀⣀⣀⡀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢉⣾⠟⣰⠏⠉⣽⣿⢊⣻⡿⠿⠛⢷⣶⡀⠀⢛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⢠⡾⠋⢸⣧⣤⣾⡴⠀⠀⠉⠠⣤⣾⣧⡻⠃⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢉⢀⣿⠁⠀⠈⠉⠈⠕⠀⠀⠀⠀⠀⠐⢭⡛⠋⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢘⣼⠃⠀⠀⣀⡀⠄⠀⣠⠘⢧⡴⢢⡀⠀⢢⡀⠀⠀⠀⠀⢴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣯⣽⣿⣿⣿⣿⣿⣿⣿⡇⠺⣿⠃⠠⣄⢻⡇⠀⣴⣿⣿⣧⣿⣾⣇⠀⢨⣿⣤⡄⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡗⠀⣿⣧⡆⠁⠙⠆⢠⢻⡿⠿⠟⡻⡿⠿⠆⠸⣟⣃⣣⣴⡦⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣾⢸⣿⡟⣿⠐⣩⣾⣧⣶⣤⣴⣬⣟⡀⠀⠀⠀⠈⠻⣿⣿⣷⠘⠘⠛⠛⠽⠋⠉⠟⢛⣩⣭⣉⣿", STDOUT_FILENO);
	ft_putendl_fd("⠾⠿⡿⠛⠛⠛⣻⣿⣿⣿⣿⣿⠿⠁⠆⢸⣿⡇⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡄⢢⠀⠹⠌⠛⣿⣰⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠠⡄⢸⣿⡇⡆⢻⣿⣿⣿⣿⣿⣿⡛⠝⠉⠀⠁⠀⠀⠐⠀⠀⠈⢯⣙⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠁⣸⣿⣿⡇⠄⠿⣿⣿⣿⣿⣿⣿⡦⠀⠀⢀⡀⣀⠀⠀⠀⠀⠀⠉⠛⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⠟⣻⣿⣿⣿⣿⢻⣿⡿⠇⣰⣿⣿⣿⣿⣴⢮⣈⡟⡟⠻⠿⠉⠀⠀⢠⣬⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⡿⢿", STDOUT_FILENO);
}

static void	print_monke_2(void)
{
	ft_putendl_fd("⣿⣿⣿⢏⢌⠍⡩⠩⠈⠉⠠⠉⣠⣾⡿⣿⣛⣻⣿⡿⣧⣍⣾⣶⣶⣾⣶⠀⠀⠸⠝⠛⢆⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠿⢿⠻⠿⠈⠀", STDOUT_FILENO);
	ft_putendl_fd("⣉⠋⠑⠁⠉⠈⠐⠁⠀⠀⣠⣾⣿⣻⠋⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠻⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⠷⠚⠒⠒", STDOUT_FILENO);
	ft_putendl_fd("⠿⠴⠡⠮⠼⠠⠂⠤⢠⣾⣿⣿⢾⣿⡴⠋⠴⠁⢉⠐⠛⣿⢿⠿⣿⠿⣿⣿⣿⣷⣦⡀⠀⠀⠀⢿⣿⣷⣀⣀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⣀⣀⠐⠀⠂⠂⠀⠀⢹⣿⣿⣷⡿⣿⢠⠥⠄⠀⢡⠂⠀⣠⠝⢹⡿⣧⣨⡟⠿⣙⣭⠉⡀⣀⡀⠀⠘⣿⡿⢿⡄⠀⠀⠀⠀⠀⠡⠀⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⡀⢀⡀⠀⠀⠀⠀⠁⣾⣿⡿⣭⣶⣿⠞⡁⣶⣿⣿⣿⣿⣿⣴⣾⣽⣿⣿⣿⣶⣿⣷⣿⣿⣿⣷⠀⠀⢹⣿⣮⡌⣀⠀⠀⠀⠀⠀⠆⠀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠘⠛⠁⣰⣿⡇⠀⣿⣿⣾⡿⣩⣾⣘⣸⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠘⠛⣿⣟⠀⠀⠀⠀⠀⠀⡀⠀", STDOUT_FILENO);
	ft_putendl_fd("⠀⠀⠀⠀⠉⠈⠀⣠⣿⣿⢋⠞⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠼⣿⣝⣦⢚⢀⠀⠀⢠⠙⠛", STDOUT_FILENO);
	ft_putendl_fd("⣀⠀⠀⠀⠀⠀⠀⣿⣿⡿⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⢹⣯⠋⠈⢸⡟⡥⢪⠰⠦", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣶⣶⣤⣼⣿⢛⣿⢳⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣠⣼⣿⡯⠄⠀⢸⠇⠀⠘⠂⠀", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⣿⣿⣿⣟⣼⣻⠈⠉⣸⣿⣿⢟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢻⣿⣿⠁⠀⠀⠈⠀⡀⣀⢠⣴", STDOUT_FILENO);
	ft_putendl_fd("⣿⣿⣿⣿⠟⠁⠠⣿⣿⠟⠁⡼⢻⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⢹⠈⠀⣀⠁⠀⠀⠀⠁⠈⠈", STDOUT_FILENO);
	ft_putendl_fd("⣿⡿⠟⠁⠀⠀⢠⣟⡍⠀⠈⣥⡟⢡⣿⡾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠙⣤⠫⠄⠀⠀⠀⠀⠀⠀", STDOUT_FILENO);
    ft_putendl_fd("Are you sure?", STDOUT_FILENO);
}

void	print_monke(void)
{
	print_monke_1();
	print_monke_2();
}
