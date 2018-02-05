#! /bin/sh

## Talisker: Foundation Toolkit

## Copyright 2012-2017 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

#############################################################################
## Utility functions                                                       ##
#############################################################################

run()
{
	echo "+ $*" >&2
	"$@"
	result="$?"
	if test $result -ne 0 ; then
		echo "**** Command failed with exit status $result ****" >&2
		exit $result
	fi
}

announce()
{
	echo "$*" >&2
}

checking()
{
	printf "checking %s..." "$*" >&2
}

result()
{
	echo " $*" >&2
}

#############################################################################
## System checks                                                           ##
#############################################################################

checking "what kind of system the build machine is"
system_name="`uname -s`"
system_kind="`echo $system_name | tr A-Z a-z`"

if test -r /etc/debian_version ; then
	system_family="debian"
	system_type="debian"
	system_name="Debian"
	system_version="`cat /etc/debian_version`"
elif test -r /System/Library/CoreServices/SystemVersion.plist ; then
	system_type="macosx"
	system_name="macOS"
	system_version="`sw_vers -productVersion`"
fi

if test -r /etc/os-release ; then
	. /etc/os-release
	system_type="$ID"
	system_name="$NAME"
	test x"$system_family" = x"" && system_family="$ID_LIKE"
	system_version="$VERSION_ID"
	system_fullname="$PRETTY_NAME"
fi

test x"$system_family" = x"" && system_family="`echo $system_kind`"
test x"$system_type" = x"" && system_type="`echo $system_name | tr A-Z a-z | sed s@[^a-z]*@@g`"
test x"$system_version" = x"" && system_version="`uname -r`"
test x"$system_fullname" = x"" && system_fullname="$system_name $system_version"

result "$system_fullname"
result " - Name:          $system_name"
result " - Type:          $system_type"
result " - Family:        $system_family"
result " - Kind:          $system_kind"
result " - Version:       $system_version"

#############################################################################
## Checks for build Dependencies in CI environments                        ##
#############################################################################

if ! test -d BuildDependencies ; then
	mkdir BuildDependencies
fi
cd BuildDependencies

checking "for sudo"
name="sudo"
if test x"$SUDO" = x"" ; then
	saveIFS=$IFS ; IFS=:
	for dir in $PATH ; do
		if test -x "$dir/$name" ; then
			$SUDO="$dir/$name"
			break
		fi
	done
	IFS=$saveIFS
fi
if test x"$SUDO" = x"" ; then
	result "(not found)"
else
	result "$SUDO"
	SUDO=sudo
fi

checking "for idl"
name="idl"
if test x"$IDL" = x"" ; then
	saveIFS=$IFS ; IFS=:
	for dir in $PATH ; do
		if test -x "$dir/$name" ; then
			IDL="$dir/$name"
			break
		fi
	done
	IFS=$saveIFS
fi
if test x"$IDL" = x"" ; then
	result "(not found)"
else
	result "$IDL"
	IDL=idl
fi

#############################################################################
## Dependency package installation for CI environments                     ##
#############################################################################

if test $system_family = debian ; then
	
	if test $system_type = ubuntu ; then
		run $SUDO add-apt-repository ppa:ubuntu-toolchain-r/test -y
	fi
	
	run $SUDO apt-get update -qq	
	run $SUDO apt-get install -qq build-essential automake autoconf libtool libltdl-dev uuid-dev git-core flex bison
fi

case $system_type in
	debian)
		run $SUDO apt-get install -qq clang
		;;
	ubuntu)
		case $system_version in
			14*)
				run $SUDO apt-get install -qq clang
				;;
			16*)
				run $SUDO apt-get install -qq clang
				;;
		esac
		;;
esac

#############################################################################
## Build dependencies that are needed in CI environments                   ##
#############################################################################

if test x"$IDL" = x"" ; then
	announce "building idl..."
	
	run git clone --depth=50 --branch=develop \
		https://github.com/TaliskerPlatform/idl.git
	run cd idl
	run git submodule update --init --recursive
	run autoreconf -fvi
	run ./configure
	run make
	run $SUDO make install
	cd ..
fi

cd ..
