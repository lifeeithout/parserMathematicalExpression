#include "FunctionBuffer.h"

#include <cmath>

#include <algorithm>

#include <stdexcept>

FunctionBuffer::FunctionBuffer()
{
	functions["sin"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 1)
			{
				throw std::invalid_argument("Wrong arguments for function sin: " + std::to_string(argument.size()));
			}

			return std::sin(argument.front());
		};

	functions["cos"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 1)
			{
				throw std::invalid_argument("Wrong arguments for function cos: " + std::to_string(argument.size()));
			}

			return std::cos(argument.front());
		};

	functions["tan"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 1)
			{
				throw std::invalid_argument("Wrong arguments for function tan: " + std::to_string(argument.size()));
			}

			return std::tan(argument.front());
		};

	functions["exp"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 1)
			{
				throw std::invalid_argument("Wrong arguments for function exp: " + std::to_string(argument.size()));
			}

			return std::exp(argument.front());
		};

	functions["pow"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 2)
			{
				throw std::invalid_argument("Wrong arguments for function pow: " + std::to_string(argument.size()));
			}

			return std::pow(argument.front(), argument.back());
		};

	functions["abs"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 1)
			{
				throw std::invalid_argument("Wrong arguments for function abs: " + std::to_string(argument.size()));
			}

			return std::abs(argument.front());
		};

	functions["min"] = [](const std::list<float> argument) -> float
		{
			if (argument.empty())
			{
				throw std::invalid_argument("No arguments for function min");
			}

			return *std::min_element(argument.begin(), argument.end());
		};

	functions["max"] = [](const std::list<float> argument) -> float
		{
			if (argument.empty())
			{
				throw std::invalid_argument("No arguments for function min");
			}

			return *std::max_element(argument.begin(), argument.end());
		};

	functions["sqrt"] = [](const std::list<float> argument) -> float
		{
			if (argument.size() != 1)
			{
				throw std::invalid_argument("Wrong arguments for function sqrt: " + std::to_string(argument.size()));
			}

			return std::sqrt(argument.front());
		};
}

bool FunctionBuffer::isHaveFunction(const std::string& name) const
{
	return functions.find(name) != functions.end();
}

std::unordered_map<std::string, std::function<float(const std::list<float>&)>>::const_iterator FunctionBuffer::getFunction(const std::string& name)
{
	std::unordered_map<std::string, std::function<float(const std::list<float>&)>>::const_iterator iter = functions.find(name);
	if (iter != functions.end())
	{
		return iter;
	}

	throw std::out_of_range("Function not found: " + name);
}
