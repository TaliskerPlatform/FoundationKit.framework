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

AM_CPPFLAGS = @AM_CPPFLAGS@ \
	-I${top_srcdir}/ThirdParty/uthash/src \
	-I${top_srcdir}/ThirdParty/uriparser/include/uriparser

frameworklib_LTLIBRARIES = libFoundationKit.la

libFoundationKit_la_SOURCES = p_foundation.hh \
	Object.cc Process.cc Thread.cc DefaultAllocator.cc URI.cc String.cc \
	Factory.cc UUID.cc Registry.cc Array.cc Dictionary.cc

libFoundationKit_la_LDFLAGS = -avoid-version -no-undefined

libFoundationKit_la_LIBADD = ${top_builddir}/ThirdParty/uriparser/liburiparser.la
