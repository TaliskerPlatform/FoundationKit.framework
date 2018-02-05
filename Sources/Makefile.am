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

AM_LDFLAGS = @AM_LDFLAGS@ -avoid-version -no-undefined

frameworklib_LTLIBRARIES = libFoundationKit.la

libFoundationKit_la_SOURCES = p_foundation.hh \
	Object.cc Process.cc Thread.cc DefaultAllocator.cc URI.cc String.cc \
	Factory.cc UUID.cc Registry.cc Array.cc Dictionary.cc

libFoundationKit_la_LIBADD = ${top_builddir}/ThirdParty/uriparser/liburiparser.la

#############################################################################
## IObject client                                                          ##
#############################################################################

frameworklib_LTLIBRARIES += libTalisker.FoundationKit.IObject.la
libFoundationKit_la_LIBADD += libTalisker.FoundationKit.IObject.la
libTalisker_FoundationKit_IObject_la_SOURCES = IObject_uuids.c

#############################################################################
## IFactory client                                                         ##
#############################################################################

frameworklib_LTLIBRARIES += libTalisker.FoundationKit.IFactory.la
libFoundationKit_la_LIBADD += libTalisker.FoundationKit.IFactory.la
libTalisker_FoundationKit_IFactory_la_SOURCES = IFactory_uuids.c

#############################################################################
## IRegistry client                                                        ##
#############################################################################

frameworklib_LTLIBRARIES += libTalisker.FoundationKit.IRegistry.la
libFoundationKit_la_LIBADD += libTalisker.FoundationKit.IRegistry.la
libTalisker_FoundationKit_IRegistry_la_SOURCES = IRegistry_uuids.c
