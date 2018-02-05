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

DIST_SUBDIRS = uriparser libxml2 jansson

SUBDIRS = .

EXTRA_DIST = uriparser-Makefile.am

dist_noinst_DATA = uriparser/COPYING uthash/LICENSE

all-local:
	cd uriparser && $(MAKE) all
	cd jansson && $(MAKE) all
	cd libxml2 && $(MAKE) all

clean-local:
	cd uriparser && $(MAKE) clean
	cd jansson && $(MAKE) clean
	cd libxml2 && $(MAKE) clean

distclean-local:
	cd uriparser && $(MAKE) distclean
	cd jansson && $(MAKE) distclean
	cd libxml2 && $(MAKE) distclean

install-data-hook:
	$(mkinstalldirs) $(DESTDIR)${frameworkdocdir}
	$(INSTALL) -m 644 $(srcdir)/uriparser/COPYING $(DESTDIR)${frameworkdocdir}/LICENSE.uriparser.txt
	$(INSTALL) -m 644 $(srcdir)/uthash/LICENSE $(DESTDIR)${frameworkdocdir}/LICENSE.uthash.txt
