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

idlgenerated = Interfaces.h \
	IAllocator.h IArray IDictionary.h IFactory.h IObject.h IRegistry.h \
	IString.h IVariant.h

CLEANFILES = $(idlgenerated) ${frameworkname}

frameworkheaders_HEADERS = Declarations.h \
	$(idlgenerated) \
	Object.hh Process.hh DefaultAllocator.hh Thread.hh String.hh URI.hh \
	Factory.hh UUID.hh Registry.hh Array.hh Dictionary.hh

%.h: $(top_srcdir)/IDL/%.idl
	$(IDL) -I$(top_srcdir)/IDL -H $@ $<

all-local:
	rm -f ${frameworkname}
	$(LN_S) $(srcdir) ${frameworkname}
