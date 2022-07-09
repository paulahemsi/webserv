/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:34:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/09 15:41:46 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"

ft::RequestProcessor::RequestProcessor(void)
{
	return ;
}

ft::RequestProcessor::RequestProcessor(ft::Socket *socket):
_socket(socket)
{
	return ;
}

ft::RequestProcessor::RequestProcessor(ft::RequestProcessor const &other)
{
	*this = other;
}

ft::RequestProcessor &ft::RequestProcessor::operator=(ft::RequestProcessor const &right_hand_side)
{
	this->_request = right_hand_side._request;
	this->_response = right_hand_side._response;
	this->_socket = right_hand_side._socket;
	this->_uri = right_hand_side._uri;
	this->_server_name = right_hand_side._server_name;
	this->_server_data = right_hand_side._server_data;
	this->_location_data = right_hand_side._location_data;
	return (*this);
}

ft::RequestProcessor::~RequestProcessor(void)
{
	return ;
}

void ft::RequestProcessor::run(int client_fd)
{
	this->_request.init(client_fd);
	_define_server_name();
	_define_uri();
	//define response fields that do not depend on the request
	_execute_request();
	this->_response.send(client_fd);
}

void ft::RequestProcessor::_define_server_name(void)
{
	this->_server_name = this->_request.get_server_name();
}

void ft::RequestProcessor::_define_uri(void)
{
	this->_uri = this->_request.get_request_field("URI");
	// if (*this->_uri.rbegin() != '/')
	// 	this->_uri.push_back('/');
}

void	ft::RequestProcessor::_execute_request(void)
{
	_select_server();
	try
	{
		this->_request.check_request();
		_select_location();
		if (_is_redirection())
			return ;
		_check_method();
		_set_body();
	}
	catch(const ft::RequestProcessor::ErrorsHttp& e)
	{
		_set_error(e.code(), e.reason());
	}
}

void ft::RequestProcessor::_build_autoindex(std::string path)
{
	std::string body(AUTOINDEX_HTML_HEAD);

	_set_autoindex_h1(body);
	_set_autoindex_body(body, path.c_str());
	this->_response.build_body(body, path);
}

void	ft::RequestProcessor::_set_autoindex_h1(std::string &body)
{
	body += OPEN_BODY_TITLE + this->_uri + CLOSE_H1;
}

void	ft::RequestProcessor::_set_autoindex_body(std::string &body, const char *path)
{
	DIR *dir;
	
	dir = opendir(path);
	struct dirent *entry;
	
	while ((entry = readdir(dir)) != NULL)
		_add_autoindex_link(body, entry);
	body += CLOSE_BODY;
	closedir(dir);
}

void	ft::RequestProcessor::_add_autoindex_link(std::string &body, struct dirent *entry)
{
	if (entry->d_name[0] != '.')
	{
		std::string host = this->_server_data.get_listen().get_host();
		int port = this->_server_data.get_listen().get_port();
		body +=	OPEN_ANCHOR_TAG +
				host + DIVIDER + 
				int_to_string(port) +
				this->_uri + SLASH +
				std::string(entry->d_name) + 
				MIDDLE_ANCHOR_TAG + entry->d_name +CLOSE_ANCHOR_TAG;
	}
}

void	ft::RequestProcessor::_set_body(void)
{
	std::string path;
	
	path = this->_server_data.get_root() + this->_uri;
	if (this->_method == "GET")
		_execute_get(path);
	else if (this->_method == "POST")
		_execute_post();
	else if (this->_method == "DELETE")
		_execute_delete(path);
}

void	ft::RequestProcessor::_execute_get(std::string path)
{
	std::string method;
	std::string file_path;

	if (_is_file(path, file_path))
		_get_file(path, file_path);
	else if (this->_location_data.get_autoindex())
		_build_autoindex(path);
	else
		throw (Forbidden());
}

void	ft::RequestProcessor::_execute_post(void)
{
	std::string body(this->_request.get_request_field("Body").data());
	// size_t index_begin =  body.find("filename=\"");
	// if (index_begin == std::string::npos)
	// 	throw (InternalServerError());
	// else
	// {
		// index_begin += 10;
		// size_t index_end = body.find("\"", index_begin);
		// std::string file_name = "./www/uploads/files/";
		// file_name += body.substr(index_begin, index_end - index_begin);
		// body.erase(0, (body.find("\r\n\r\n") + 4));
		// body.erase((body.rfind("\r\n")), body.length());
		// body.erase((body.rfind("\r\n")), body.length());
		std::ofstream new_file;
		new_file.open(this->_request.get_request_field("filename").c_str(), std::ios::binary);
		new_file.write(body.c_str(), body.length());
		new_file.close();
	// }
}

void ft::RequestProcessor::_execute_delete(std::string path)
{
	if (is_dir(path))
		throw (Forbidden());
	if (!is_file(path))
		throw (NotFound());
	std::remove(path.c_str());
	this->_response.set_status_code(ACCEPTED_CODE);
	this->_response.set_reason_phrase(ACCEPTED_REASON);
	this->_response.build_body(DELETE_HTML);
}

void ft::RequestProcessor::_get_file(std::string path, std::string file_path)
{
	std::stringstream buffer;
	std::ifstream file(file_path.c_str());

	if (!file)
		throw (NotFound());
	buffer << file.rdbuf();
	this->_response.build_body(buffer.str(), path);
}

bool ft::RequestProcessor::_is_file(std::string path, std::string& file_path)
{
	if (is_file(path))
	{
		file_path = path;
		return (true);
	}
	if (is_dir(path))
	{
		if (_find_index(path, file_path))
			return (true);
		return (false);
	}
	throw (NotFound());
}

bool ft::RequestProcessor::_find_index(std::string path, std::string& file_path)
{
	std::vector<std::string> indexes(this->_location_data.get_index());

	if (indexes.size())
	{
		for (size_t i = 0; i < indexes.size(); i++)
		{
			if (is_file(path + indexes[i]))
			{
				file_path = path + indexes[i];
				return (true);
			}
		}
	}
	return (false);
}

std::string	ft::RequestProcessor::_get_error_page_path(std::string code)
{
	std::string	path;

	path = this->_server_data.get_root() + this->_server_data.get_error_page(code);
	if (is_file(path))
		return (path);
	return (this->_server_data.get_default_error_page(code));
}

void	ft::RequestProcessor::_set_error(std::string code, std::string reason)
{
	std::string			path = _get_error_page_path(code);
	std::ifstream		file(path.c_str());
	std::stringstream	buffer;
	
	buffer << file.rdbuf();
	this->_response.set_status_code(code);
	this->_response.set_reason_phrase(reason);
	this->_response.build_body(buffer.str(), path);
}

void	ft::RequestProcessor::_select_server(void)
{
	server_data_vector confs = this->_socket->get_confs();
	server_data_vector::iterator it = confs.begin();
	server_data_vector::iterator it_end = confs.end();

	for (; it != it_end; it++)
		if (_is_match(it->get_server_name()) != ERROR)
			return (_define_server(*it));
	_define_server(confs[0]);
}

int	ft::RequestProcessor::_is_match(std::vector<std::string> names)
{
	for (size_t i = 0; i < names.size(); i++)
		if (names[i] == this->_server_name)
			return (i);
	return (ERROR);
}

void	ft::RequestProcessor::_define_server(ft::ServerData server)
{
	this->_server_data = server;
}

void	ft::RequestProcessor::_select_location(void)
{
	std::priority_queue<ft::LocationData> locations = _check_locations();
	if (locations.empty())
		throw (NotFound());
	this->_location_data = locations.top();
}

ft::RequestProcessor::location_data_queue ft::RequestProcessor::_check_locations(void)
{
	location_data_vector all_locations = this->_server_data.get_location();
	std::priority_queue<ft::LocationData> match_locations;
	std::string prefix;
	for (size_t i = 0; i < all_locations.size(); i++)
	{
		prefix = all_locations[i].get_prefix();
		size_t found = this->_uri.find(prefix);
		if (found == 0)
			match_locations.push(all_locations[i]);
	}
	return (match_locations);
}

bool	ft::RequestProcessor::_is_redirection(void)
{
	std::string redirection;
	redirection = this->_location_data.get_redirection();
	if (redirection == "")
		return (false);
	this->_response.set_header_field("Location", redirection);
	this->_response.set_status_code("301");
	return (true);
}

void	ft::RequestProcessor::_check_method(void)
{
	std::set<std::string> methods = this->_location_data.get_accepted_methods();
	this->_method = this->_request.get_method();

	std::set<std::string>::iterator found = methods.find(this->_method);
	if (found == methods.end())
			throw (MethodNotAllowed());
}
