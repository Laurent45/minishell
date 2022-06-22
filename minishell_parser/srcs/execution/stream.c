

int	ft_saved_std(int std_saved[2])
{
	std_saved[0] = dup(STDIN_FILENO);
	std_saved[1] = dup(STDOUT_FILENO);
	if (std_saved[0] == -1 || std_saved[1] == -1)
		return (ft_perror(0, "dup"));
	return (1);
}
