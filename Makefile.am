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

ACLOCAL_AMFLAGS = -I M4

EXTRA_DIST = README.md LICENSE-2.0

SUBDIRS = ThirdParty IDL Headers Sources Tests .

frameworkdoc_DATA = LICENSE-2.0

#############################################################################
## Global Installation hook for "framework" projects
#############################################################################

install-data-hook:
if FRAMEWORK_FIXUPS
	$(MKDIR_P) '$(DESTDIR)$(frameworkdir)/Versions'
	cd $(DESTDIR)$(frameworkdir)/Versions && $(LN_S) $(VERSION) Current
	cd $(DESTDIR)$(frameworkdir) && $(LN_S) Versions/Current/Headers/$(frameworkname) Headers
	cd $(DESTDIR)$(frameworkdir) && $(LN_S) Versions/Current/Documentation Documentation
	cd $(DESTDIR)$(frameworkdir) && $(LN_S) Versions/Current/Libraries/lib$(frameworkname).@dylibext@ $(frameworkname)
endif
