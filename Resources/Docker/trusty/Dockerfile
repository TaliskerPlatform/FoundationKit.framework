FROM ubuntu:trusty

ENV DEBIAN_FRONTEND noninteractive
ENV TERM linux
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
ENV HOME /root
ENV DISPLAY :0

RUN apt-get -qq update && \
	apt-get -qq -y install software-properties-common

RUN add-apt-repository ppa:ubuntu-toolchain-r/test -y

RUN apt-get -qq update && \
	apt-get -qq -y install build-essential bison flex uuid-dev clang git-core

