#include "stdafx.h"
#include "PiCalculator.h"

void ShowHelp()
{
	std::cout << "The programs takes two arguments:\n"
			  << "first param: <iterations> - number of iterations (points). Should be positive\n"
			  << "----------------------------------" << std::endl;
}

int main(int argc, char* argv[])
{
	ShowHelp();

	try
	{
		if (argc != 2)
		{
			throw std::invalid_argument("Invalid number of arguments");
		}

		if (argc == 2)
		{
			int numberOfIterations = std::stoi(argv[1]);

			if (0 >= numberOfIterations)
			{
				throw std::invalid_argument("Invalid values");
			}

			clock_t startTime = clock();
			CPiCalculator calculator(numberOfIterations);
			calculator.Calculate();
			std::cout << calculator.GetCalculatedPi() << std::endl
					  << "Time: " << clock() - startTime << " ms" << std::endl;
		}
		else
		{
			throw std::invalid_argument("Invalid number of arguments");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}