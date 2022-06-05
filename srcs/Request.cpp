
#include "Request.hpp"


ft::Request::Request(std::string request_string)
{
	std::stringstream request_(request_string);
	std::string line;
	std::getline(request_, line, '\r');
	//parse first line
	this->_parse_request_line(line);
	//loop over other lines and insert in map
	//detect empty line
	//stores body
}

void ft::Request::_parse_request_line(std::string request_line)
{
	std::string field[3] = { "Method:", "URI:", "Protocol-Version:" };

	for (std::size_t i = 0; i < 3; i++)
	{
		std::size_t pos = request_line.find(' ');
		std::string value = request_line.substr(0, pos);
		this->_request.insert(ft::request_pair(field[i], value));
		request_line.erase(0, pos + 1);
	}
}

ft::Request::~Request(void)
{
	std::cout << "Request destructor called" << std::endl;
}
