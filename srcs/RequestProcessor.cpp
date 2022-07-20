/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:34:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/19 21:34:24 by phemsi-a         ###   ########.fr       */
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
	this->_known_methods.insert("HEAD");
	this->_known_methods.insert("GET");
	this->_known_methods.insert("POST");
	this->_known_methods.insert("DELETE");
	this->_known_methods.insert("PUT");
	this->_known_methods.insert("PATCH");
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
	this->_known_methods = right_hand_side._known_methods;
	return (*this);
}

ft::RequestProcessor::~RequestProcessor(void)
{
	return ;
}

void ft::RequestProcessor::run(int client_fd)
{
	this->_client = client_fd;
	this->_request.init(client_fd);
	_define_server_name();
	_define_uri();
	_execute_request();
	this->_response.send(client_fd);
}

ft::Request ft::RequestProcessor::get_request(void)
{
	return (this->_request);
}

ft::ServerData ft::RequestProcessor::get_server_data(void)
{
	return (this->_server_data);
}

ft::LocationData ft::RequestProcessor::get_location_data(void)
{
	return (this->_location_data);
}

void ft::RequestProcessor::_define_server_name(void)
{
	this->_server_name = this->_request.get_server_name();
}

void ft::RequestProcessor::_define_uri(void)
{
	this->_uri = this->_request.get_request_field("URI");
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
	catch(const ft::ErrorsHttp& e)
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
		std::string uri = this->_uri;
		_check_slash(uri);
		body +=	OPEN_ANCHOR_TAG +
				host + DIVIDER + 
				int_to_string(port) +
				uri +
				std::string(entry->d_name) + 
				MIDDLE_ANCHOR_TAG + entry->d_name +CLOSE_ANCHOR_TAG;
	}
}

void	ft::RequestProcessor::_set_body(void)
{
	std::string		path;
	path = _define_path();
	if (_is_cgi(path))
		_execute_cgi(path);
	else if (this->_method == "GET")
		_execute_get(path);
	else if (this->_method == "POST")
		_execute_post();
	else if (this->_method == "DELETE")
		_execute_delete(path);
}

std::string ft::RequestProcessor::_define_path(void)
{
	std::string path;
	if (this->_location_data.get_root() != "")
	{
		path = this->_location_data.get_root();
		std::string prefix = this->_location_data.get_prefix();
		std::string resource = this->_uri.substr(this->_uri.find(prefix) + prefix.length(), this->_uri.npos);
		_check_slash(path);
		path.append(resource);
	}
	else
		path = this->_server_data.get_root() + this->_uri;
	return (path);
}

void ft::RequestProcessor::_execute_cgi(std::string file_path)
{
	ft::CgiMediator	cgi_mediator;
	cgi_mediator.build(this->_server_data, this->_location_data, this->_request, file_path);
	cgi_mediator.exec(this->_response);
}

bool ft::RequestProcessor::_has_cgi_configured(void)
{
	if (this->_server_data.get_cgi().size())
		return (true);
	if (this->_location_data.get_cgi().size())
		return (true);
	return (false);
}

bool ft::RequestProcessor::_is_cgi(std::string& path)
{
	std::string extension;
	ft::Cgi		cgi;

	if (!_has_cgi_configured())
		return (false);
	if (is_dir(path))
	{
		_check_slash(path);
		if (!_find_index(path))
			return (false);
	}
	else if (!is_file(path))
		throw (ft::NotFound());

	extension = extract_extension(path);
	cgi = _get_cgi_configs();
	if (!cgi.has_extension(extension))
		return (false);
	return (true);
}

ft::Cgi ft::RequestProcessor::_get_cgi_configs(void)
{
	if (this->_location_data.get_cgi().size())
		return (this->_location_data.get_cgi());
	return (this->_server_data.get_cgi());
}

void	ft::RequestProcessor::_execute_get(std::string path)
{
	if (is_dir(path))
	{
		_check_slash(path);
		if (_find_index(path))
			return (_get_file(path));
		else if (this->_location_data.get_autoindex())
			return (_build_autoindex(path));
		else
			throw (ft::Forbidden());
	}
	else if (is_file(path))
		return (_get_file(path));
	else
		throw (ft::NotFound());
}

void	ft::RequestProcessor::_execute_post(void)
{
	_check_payload();
	if (this->_request.is_multipart_form_data())
		return (_upload_file());
	//lidar com não-arquivos
}

void ft::RequestProcessor::_upload_file(void)
{
	std::ofstream new_file;
	std::string body;
	std::string filepath;
	std::string file_location;

	filepath = _build_filepath();
	file_location = _build_file_location();
	body = (this->_request.get_request_field("Body"));
	new_file.open(filepath.c_str(), std::ios::binary);//lidar com erros
	new_file.write(body.c_str(), body.length());//lidar com erros
	new_file.close();

	this->_response.set_status_code(CREATED_CODE);
	this->_response.set_reason_phrase(CREATED_REASON);
	this->_response.set_header_field("Location", file_location);
}

void	ft::RequestProcessor::_check_payload(void)
{
	int payload_max_size;
	int body_length;

	body_length = this->_request.get_content_length();
	payload_max_size = this->_server_data.get_body_size();
	if (this->_location_data.get_body_size())
		payload_max_size = this->_location_data.get_body_size();

	if (body_length > payload_max_size)
		throw (ft::PayloadTooLarge());
}

std::string	ft::RequestProcessor::_build_filepath(void)
{
	std::string filepath;
	std::string filename;

	filepath = _define_path();
	filename = this->_request.get_request_field("filename");
	if (filename == "")
		throw (ft::BadRequest());
	filepath += filename;
	return (filepath);
}

std::string	ft::RequestProcessor::_build_file_location(void)
{
	std::string file_location;
	std::string filename;

	file_location = this->_server_data.get_root() + this->_uri;
	_check_slash(file_location);
	filename = this->_request.get_request_field("filename");
	file_location.append(filename);
	return (file_location);
}

void ft::RequestProcessor::_execute_delete(std::string path)
{
	if (is_dir(path))
		throw (ft::Forbidden());
	if (!is_file(path))
		throw (ft::NotFound());
	std::remove(path.c_str());
	this->_response.set_status_code(ACCEPTED_CODE);
	this->_response.set_reason_phrase(ACCEPTED_REASON);
	this->_response.build_body(DELETE_HTML);
}

void ft::RequestProcessor::_get_file(std::string path)
{
	std::stringstream buffer;
	std::ifstream file(path.c_str());

	if (!file)
		throw (ft::NotFound());
	buffer << file.rdbuf();
	this->_response.build_body(buffer.str(), path);
}

void ft::RequestProcessor::_check_slash(std::string &path)
{
	if (*path.rbegin() != '/')
			path.append("/");
}

bool ft::RequestProcessor::_find_index(std::string& path)
{
	std::vector<std::string> indexes(this->_location_data.get_index());

	if (indexes.size())
	{
		for (size_t i = 0; i < indexes.size(); i++)
		{
			if (is_file(path + indexes[i]))
			{
				path.append(indexes[i]);
				return (true);
			}
		}
	}
	return (false);
}

std::string	ft::RequestProcessor::_get_error_page_path(std::string code)
{
	std::string	path;
	std::string root;

	root = this->_location_data.get_root();
	if (root == "")
		root = this->_server_data.get_root();
	if (this->_location_data.has_error_page(code))
	{
		path = root + this->_location_data.get_error_page(code);
		if (is_file(path))
			return (path);
	}
	if (this->_server_data.has_error_page(code))
	{
		path = root + this->_server_data.get_error_page(code);
		if (is_file(path))
			return (path);
	}
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

void	ft::RequestProcessor::_define_server(const ft::ServerData& server)
{
	this->_server_data = server;
}

void	ft::RequestProcessor::_select_location(void)
{
	std::priority_queue<ft::LocationData> locations = _check_locations();
	if (locations.empty())
		throw (ft::NotFound());
	this->_location_data = locations.top();
}

ft::RequestProcessor::location_data_queue ft::RequestProcessor::_check_locations(void)
{
	location_data_vector all_locations = this->_server_data.get_location();
	std::priority_queue<ft::LocationData> match_locations;

	for (size_t i = 0; i < all_locations.size(); i++)
		if (_is_uri_in_location(all_locations[i]))
			match_locations.push(all_locations[i]);
	return (match_locations);
}

bool ft::RequestProcessor::_is_uri_in_location(ft::LocationData location)
{
	std::string prefix;

	_define_prefix(prefix, location);
	return (this->_uri.find(prefix) == 0);
}

void ft::RequestProcessor::_define_prefix(std::string& prefix, ft::LocationData location)
{
	prefix = location.get_prefix();
	if ((prefix != "/") && (*prefix.rbegin() == '/'))
		prefix.resize(prefix.length() - 1);
}

bool	ft::RequestProcessor::_is_redirection(void)
{
	std::string redirection;
	redirection = this->_location_data.get_redirection();
	if (redirection == "")
		return (false);
	this->_response.set_header_field("Location", redirection);
	this->_response.set_status_code(MOVED_PERMANENTLY_CODE);
	this->_response.set_reason_phrase(MOVED_PERMANENTLY_REASON);
	return (true);
}

void	ft::RequestProcessor::_check_method(void)
{
	std::set<std::string> methods = this->_location_data.get_accepted_methods();
	this->_method = this->_request.get_method();

	std::set<std::string>::iterator found = methods.find(this->_method);

	if (found == methods.end())
	{
		if (this->_known_methods.find(this->_method) == this->_known_methods.end())
			throw (ft::BadRequest());
		throw (ft::MethodNotAllowed());
	}
}
