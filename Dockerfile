#FROM debian:latest
FROM ubuntu:latest

ENV DEBIAN_FRONTEND noninteractive
ENV TERM linux
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
ENV HOME /root
ENV DISPLAY :0

RUN apt-get -qq update && \
	apt-get -qq -y install software-properties-common build-essential clang \
		bison flex uuid-dev

RUN mkdir -p /root/BuildRoot/FoundationKit
ADD ./ /root/BuildRoot/FoundationKit

RUN cd /root/BuildRoot && \
	FoundationKit/Resources/CI/before_install.sh

RUN cd /root/BuildRoot/FoundationKit && \
	autoreconf -fvi && \
	./configure && \
	make clean && \
	make && \
	make check && \
	make install
