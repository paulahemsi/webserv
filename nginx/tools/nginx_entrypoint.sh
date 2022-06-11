#!/bin/sh

SERVER_CONF=/etc/nginx/sites-available/exemple

if [ ! -f "$SERVER_CONF" ]
then
	mkdir -p /var/www/exemple
	mv /srcs/hello-world.html /var/www/exemple/
	mv /srcs/exemple /etc/nginx/sites-available/
	ln -s /etc/nginx/sites-available/exemple etc/nginx/sites-enabled/
fi

exec "$@"
