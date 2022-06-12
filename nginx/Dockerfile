FROM debian:buster

WORKDIR /

RUN apt update; \
	apt install -y \
	nginx \
	procps \
	vim

COPY conf/ /srcs/
COPY ./tools/nginx_entrypoint.sh /usr/local/bin/

EXPOSE 4444

#ENTRYPOINT ["tail", "-f", "/dev/null"]
ENTRYPOINT ["nginx_entrypoint.sh"]
CMD ["nginx", "-g", "daemon off;"]
