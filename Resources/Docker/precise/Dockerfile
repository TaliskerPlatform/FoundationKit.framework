FROM ubuntu:precise

ENV DEBIAN_FRONTEND noninteractive
ENV TERM linux
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
ENV HOME /root
ENV DISPLAY :0

RUN apt-get -qq update && \
	apt-get -qq -y install python-software-properties

RUN add-apt-repository ppa:ubuntu-toolchain-r/test -y

RUN apt-get -qq update && \
	apt-get -qq -y install build-essential bison flex uuid-dev git-core

