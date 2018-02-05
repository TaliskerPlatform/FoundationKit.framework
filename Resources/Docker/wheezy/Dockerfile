FROM debian:wheezy

ENV DEBIAN_FRONTEND noninteractive
ENV TERM linux
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
ENV HOME /root
ENV DISPLAY :0

RUN apt-get -qq update && \
	apt-get -qq -y install build-essential clang bison flex uuid-dev git-core

