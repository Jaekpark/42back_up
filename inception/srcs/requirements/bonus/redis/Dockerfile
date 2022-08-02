FROM debian:buster
MAINTAINER jaekpark@student.42seoul.kr
RUN apt-get update && apt-get -y upgrade &&\
	apt-get install -y redis vim wget curl

COPY ./tools/entrypoint.sh ./
COPY ./conf/redis.conf /etc/redis/

EXPOSE 6379
ENTRYPOINT ["bash", "entrypoint.sh"]
