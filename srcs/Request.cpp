
#include "Request.hpp"

ft::Request::Request(std::string request_string)
{
	std::stringstream request_(request_string);
	std::string line;
	std::getline(request_, line, '\r');
	this->_parse_request_line(line);
	this->_parse_header(request_);
	this->_parse_body(request_string);
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

void ft::Request::_parse_header(std::stringstream &header)
{
	for (std::string line; line != "\n"; std::getline(header, line, '\r'))
	{
		std::size_t pos = line.find(' ');
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1, std::string::npos);
		this->_request.insert(ft::request_pair(key, value));
	}
}

void ft::Request::_parse_body(std::string request_string)
{
	std::size_t pos = request_string.find("\r\n\r\n");
	std::string value = request_string.substr(pos + 4, std::string::npos);
	this->_request.insert(ft::request_pair("Body:", value));
}

//DEBUGGING FUNCTION
void ft::Request::debugging_request(void)
{
	std::map<std::string, std::string>::iterator it = this->_request.begin();
	while (it != this->_request.end())
	{
		std::cout << it->first << " " << it->second << std::endl;
		it++;
	}
}

ft::Request::~Request(void)
{
	std::cout << "Request destructor called" << std::endl;
}
