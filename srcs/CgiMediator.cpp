/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiMediator.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:59 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/17 17:44:02 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiMediator.hpp"

ft::CgiMediator::CgiMediator():
_env(NULL),
_cmd(NULL)
{
	return ;
}

void ft::CgiMediator::build(ft::ServerData server_data, ft::LocationData location_data, ft::Request request, std::string file_path)
{
	this->_header = request.get_request();
	this->_file_path = file_path;
	this->_cgi = _select_cgi(server_data, location_data);
	this->_cmd = _build_cmd(file_path);
	this->_env = _build_env();

	if (!is_executable(this->_cmd[0]))
		throw (ft::InternalServerError());
}

ft::Cgi ft::CgiMediator::_select_cgi(ft::ServerData server_data, ft::LocationData location_data)
{
	if (location_data.get_cgi().size())
		return (location_data.get_cgi());
	return (server_data.get_cgi());
}

void ft::CgiMediator::exec(ft::Response& response)
{
	int	pid;
	int	status;

	std::FILE *temp_file = std::tmpfile();
	int temp_fd = fileno(temp_file);
		
	pid = fork();
	if (pid == 0)
		_run_script(temp_fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		throw (ft::InternalServerError());
	_get_script_output(temp_file, response);
	fclose(temp_file);
}

void ft::CgiMediator::_run_script(int temp_fd)
{
	dup2(temp_fd, STDOUT_FILENO);
	execve(this->_cmd[0], this->_cmd, this->_env);
	close(temp_fd);
}

void ft::CgiMediator::_get_script_output(std::FILE *temp_file, ft::Response& response)
{
	int size = _get_file_size(temp_file);
	char* buffer = new char[size + 1];

	memset(buffer, 0, size + 1);
	fread(buffer, 1, size, temp_file);
	response.build_body(std::string(buffer));
	delete [] buffer;
}

int ft::CgiMediator::_get_file_size(std::FILE *temp_file)
{
	int size;

	fseek(temp_file , 0 , SEEK_END);
	size = ftell(temp_file);
	rewind(temp_file);
	return (size);
}

char** ft::CgiMediator::_build_cmd(std::string file_path)
{
	std::string executable;
	char** cmd = new char*[3];

	memset(cmd, 0, 3 * sizeof(char*));
	executable = this->_cgi.get_program(extract_extension(file_path));
	cmd[0] = strdup(executable.c_str());
	cmd[1] = strdup(file_path.c_str());
	return (cmd);
}

char ** ft::CgiMediator::_build_env(void)
{
	size_t	i;
	int		env_size = this->_header.size() + 2;
	char**	env = new char*[env_size];

	memset(env, 0, env_size * sizeof(char*));
	ft::header_map::iterator it = this->_header.begin();
	for(i = 0; i < this->_header.size(); it++, i++)
		_save_env_variable(it->first, it->second, &env[i]);
	_save_env_variable("QUERY_STRING", this->_header["Body:"], &env[i]);
	return (env);
}

void ft::CgiMediator::_save_env_variable(std::string key, std::string value, char** env_var)
{
	ft::trim(key, ":"); //!fazer um fix no request
	std::string var_string = to_upper(key) + "=" + value ;
	*(env_var) = strdup((var_string.c_str()));
}

ft::CgiMediator::~CgiMediator()
{
	int i = 0;
	while (this->_cmd[i])
		free(this->_cmd[i++]);
	delete [] this->_cmd;
	i = 0;
	while (this->_env[i])
		free(this->_env[i++]);
	delete [] this->_env;
}
