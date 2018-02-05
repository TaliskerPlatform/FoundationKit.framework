#serial 2017021100
# Talisker: Keep distributed M4 macro files up to date

## Copyright 2017 Mo McRoberts.
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

m4-update:
	@result=0 ; \
	devellibdir='${devellibdir}' ; \
	test x"$$devellibdir" = x"" && devellibdir='/Developer/Library' ; \
	for i in $(am__aclocal_m4_deps) $(tal__aux_dir)/tal-m4.mk ; do \
		basename=`echo $$i | awk -F"/" '{print $$NF}'` ; \
		case "$$basename" in \
			tal-*|*.m4) \
				dest_serial=`head -1 $$i | $(AWK) '/^#[ ]*serial ([0-9]+)[ ]*$$/{print $$2}'` ; \
				if test x"$$dest_serial" = x"" ; then \
					echo "$$basename: no serial number, skipping" >&2 ; \
				else \
					src_path="" ; \
					for sub in M4 BuildScripts ; do \
						if test -e "$$devellibdir/$$sub/$$basename" ; then \
							src_path="$$devellibdir/$$sub/$$basename" ; \
							break ; \
						fi ; \
					done ; \
					if test x"$$src_path" = x"" ; then \
						echo "$$basename: not found in $$devellibdir" >&2 ; \
					else \
						src_serial=`head -1 $$src_path | $(AWK) '/^#[ ]*serial ([0-9]+)[ ]*$$/{print $$2}'` ; \
						if test x"$$src_serial" = x"" ; then \
							echo "$$basename: no serial number in source file ($$src_path)" >&2 ; \
						elif test $$src_serial -lt $$dest_serial ; then \
							echo "$$basename: local copy is newer than source file ($$dest_serial versus $$src_serial in $$src_path)" >&2 ; \
						elif test $$src_serial -eq $$dest_serial ; then \
							echo "$$basename: up to date" >&2 ; \
						else \
							cp "$$src_path" "$$i" || result=1 ; \
							echo "$$basename: updated to $$src_serial" >&2 ; \
						fi ; \
					fi ; \
				fi \
				;; \
		esac ; \
	done ; \
	exit $$result
