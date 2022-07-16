/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiMediator.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:59 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/15 21:36:31 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiMediator.hpp"

ft::CgiMediator::CgiMediator()
{
}

void ft::CgiMediator::build(ft::ServerData server_data, ft::LocationData location_data, ft::Request request, std::string file_path)
{
	this->_request = request;
	this->_server_data = server_data;
	this->_location_data = location_data;
	this->_file_path = file_path;
	this->_cmd = _build_cmd(file_path);
	this->_env = _build_env();

	if (!is_executable(this->_cmd[0]))
		throw (InternalServerError());
}

void ft::CgiMediator::exec(void)
{
	int	pid;
	int	status;
	std::cout << "exec" << std::endl;
	std::string temp = "./temp";
	int temp_fd = open(temp.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
		
	pid = fork();
	std::cout << "pré pid 0 " << std::endl;
	
	if (pid == 0)
	{
		dup2(temp_fd, STDOUT_FILENO);
		execve(this->_cmd[0], this->_cmd, this->_env);
		close(temp_fd);
	}
	waitpid(pid, &status, 0);
	std::cout << "pós pid 0 " << std::endl;
	
	if (WIFSIGNALED(status))
		throw (InternalServerError());
	std::cout << "not error " << std::endl;
	
}

char** ft::CgiMediator::_build_cmd(std::string file_path)
{
	std::string executable;
	char** cmd = (char**)malloc(3 * sizeof(char *));

	executable = _get_cgi_configs().get_program(extract_extension(file_path));
	cmd[0] = strdup(executable.c_str());
	cmd[1] = strdup(file_path.c_str());
	cmd[2] = NULL;
	return (cmd);
}

ft::Cgi ft::CgiMediator::_get_cgi_configs(void)
{
	if (this->_location_data.get_cgi().size())
		return (this->_location_data.get_cgi());
	return (this->_server_data.get_cgi());
}

char ** ft::CgiMediator::_build_env(void)
{
	std::map<std::string, std::string> header;
	header = this->_request.get_request();
	char** env = (char**)malloc(header.size() * sizeof(char *));

	std::map<std::string, std::string>::iterator it = header.begin();

	for(size_t i = 0; i < header.size(); it++, i++)
	{
		std::string key = it->first;
		ft::trim(key, ":"); //!fazer um fix no request
		std::string value = it->second;
		std::string env_var = to_upper(key) + "=" + to_upper(value);
		env[i] = strdup((env_var.c_str()));
	}
	env[header.size() - 1] = NULL;
	return (env);
}

void ft::CgiMediator::_free_cmd(void)
{
	for (size_t i = 0; this->_cmd[i]; i++)
		free(this->_cmd[i]);
	free(this->_cmd);
}

void ft::CgiMediator::_free_env(void)
{
	for (size_t i = 0; this->_env[i]; i++)
		free(this->_env[i]);
	free(this->_env);
}

ft::CgiMediator::~CgiMediator()
{
	_free_cmd();
	_free_env();
}
