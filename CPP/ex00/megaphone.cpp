#include <iostream>
#include <ctype.h>


#define LOG(x) std::cout << x ;
int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		int j = 1;
		int i = 0;
		while (j < argc)
		{
			i = 0;
			while (argv[j][i] != '\0')
			{
				LOG((char)toupper(argv[j][i]));
				i++;
			}
			j++;
		}
		std::cout << std::endl;
	}
	else
		LOG("* LOUD AND UNBEARABLE FEEDBACK NOISE *");
}