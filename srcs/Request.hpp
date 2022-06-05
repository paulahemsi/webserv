#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>

namespace ft
{
	typedef std::pair<std::string, std::string> request_pair;

	class Request
	{
		private:
			
			std::map<std::string, std::string> _request;
			Request(void);
			
			void _parse_request_line(std::string request_line);
			void _parse_header(std::stringstream &header);

		public:
			Request(std::string request_string);
			~Request(void);
	};
}


#endif 
