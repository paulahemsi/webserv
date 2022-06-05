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
			void _parse_body(std::string request_string);

		public:
			Request(std::string request_string);
			Request(const Request& other);
			~Request(void);

			Request& operator= (const Request& other);

			//DEBUGGING FUNCTION
			void debugging_request(void);
	};
}

#endif 
