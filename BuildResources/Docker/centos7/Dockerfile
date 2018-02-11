FROM centos:centos7

ENV TERM linux
ENV HOME /root
ENV DISPLAY :0

RUN yum update -q -y && \
	yum install -y clang g++ bison flex automake autoconf libtool git make file \
		libstdc++-devel libstdc++-static libuuid-devel
