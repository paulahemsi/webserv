#!/bin/sh

SERVER_CONF=/etc/nginx/sites-available/example

if [ ! -f "$SERVER_CONF" ]
then
	mkdir -p /var/www/example
	mv /srcs/hello-world.html /var/www/example/
	mv /srcs/1.jpg /var/www/example/
	mv /srcs/example /etc/nginx/sites-available/
	ln -s /etc/nginx/sites-available/example etc/nginx/sites-enabled/
fi

exec "$@"
