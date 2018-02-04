#! /bin/sh

set -e
set -x

if test -r /etc/debian_version ; then
  
  sudo apt-get install -qq build-essential binutils automake autoconf libtool pkg-config uuid-dev

fi

git clone --depth=50 --branch=develop https://github.com/TaliskerPlatform/idl.git
cd idl
git submodule update --init --recursive
autoreconf -fvi
./configure
make
sudo make install
cd ..
