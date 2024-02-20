#ifndef FUNCTIONBUFFER_H
#define FUNCTIONBUFFER_H

#include <list>

#include <string>

#include <functional>

#include <unordered_map>

class FunctionBuffer
{
public:
	FunctionBuffer();

	bool isHaveFunction(const std::string&) const;
	std::unordered_map<std::string, std::function<float(const std::list<float>&)>>::const_iterator getFunction(const std::string&);
private:
	std::unordered_map<std::string, std::function<float(const std::list<float>&)>> functions;
};

#endif // !FUNCTIONBUFFER_H
