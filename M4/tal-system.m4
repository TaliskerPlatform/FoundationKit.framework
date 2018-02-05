#serial 2017120400
# Talisker: Determine system types

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

m4_pattern_forbid([^_?TAL_])

##---------------------------------------------------------------------
## TAL_CANONICAL_BUILD
##---------------------------------------------------------------------
## Determine the build system type (i.e., the system this script is being
## executed on).

AC_DEFUN([TAL_CANONICAL_BUILD],[
AC_REQUIRE([_TAL_INIT])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])])

m4_ifdef([_TAL_AC_CANONICAL_BUILD],,[
m4_rename([AC_CANONICAL_BUILD],[_TAL_AC_CANONICAL_BUILD])dnl
AC_DEFUN([AC_CANONICAL_BUILD],[
AC_REQUIRE_AUX_FILE([talisker.guess])dnl
AC_REQUIRE_AUX_FILE([talisker.sub])dnl
m4_bpatsubst(m4_defn([_TAL_AC_CANONICAL_BUILD]),[/config\.\(guess\|sub\)],[/talisker.\1])dnl
])
])

##---------------------------------------------------------------------
## TAL_CANONICAL_HOST
##---------------------------------------------------------------------
## Determine the host system type (i.e., the system that executables will be
## compiled for); usually the same as the build system type unless
## cross-compiling.

AC_DEFUN([TAL_CANONICAL_HOST],[
AC_REQUIRE([_TAL_INIT])dnl
AC_REQUIRE([AC_CANONICAL_HOST])])

m4_ifdef([_TAL_AC_CANONICAL_HOST],,[
m4_rename([AC_CANONICAL_HOST],[_TAL_AC_CANONICAL_HOST])dnl
AC_DEFUN([AC_CANONICAL_HOST],[
m4_bpatsubst(m4_defn([_TAL_AC_CANONICAL_HOST]),[/config\.sub],[/talisker.sub])dnl
])
])

##---------------------------------------------------------------------
## TAL_CANONICAL_TARGET
##---------------------------------------------------------------------
## Determine the target system type (i.e., the system that output from built
## executables will be targeting; usually the same as the host system type
## unless building cross-build tools.

AC_DEFUN([TAL_CANONICAL_TARGET],[
AC_REQUIRE([_TAL_INIT])dnl
AC_REQUIRE([AC_CANONICAL_TARGET])])

m4_ifdef([_TAL_AC_CANONICAL_TARGET],,[
m4_rename([AC_CANONICAL_TARGET],[_TAL_AC_CANONICAL_TARGET])dnl
AC_DEFUN([AC_CANONICAL_TARGET],[
m4_bpatsubst(m4_defn([_TAL_AC_CANONICAL_TARGET]),[/config\.sub],[/talisker.sub])dnl
])
])

##---------------------------------------------------------------------
## TAL_CANONICAL_SYSTEM
##---------------------------------------------------------------------
## Determine the build, host and target system types

AC_DEFUN([TAL_CANONICAL_SYSTEM],[
AC_REQUIRE([_TAL_INIT])dnl
AC_REQUIRE([AC_CANONICAL_SYSTEM])])

##---------------------------------------------------------------------
## INTERNAL - _TAL_SYS_INIT
##---------------------------------------------------------------------
## A macro that _TAL_INIT can AC_REQUIRE() to ensure that aclocal
## incorporates the contents of this file

AC_DEFUN([_TAL_SYS_INIT],[])

##---------------------------------------------------------------------
## INTERNAL - _AC_CANONICAL_SPLIT wrapper
##---------------------------------------------------------------------
## _AC_CANONICAL_SPLIT is invoked by AC_CANONICAL_BUILD, et al, in order
## to split the canonical alias into the _cpu, _vendor, _os-suffixed
## variables. We extend this function to also set various others, via
## _TAL_SYS
m4_ifdef([_TAL_AC_CANONICAL_SPLIT],,[
m4_rename([_AC_CANONICAL_SPLIT],[_TAL_AC_CANONICAL_SPLIT])dnl
AC_DEFUN([_AC_CANONICAL_SPLIT],[
_TAL_AC_CANONICAL_SPLIT([$1])
_TAL_SYS([$1])
])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_SYS($1:KIND=build|host|target)
##---------------------------------------------------------------------
## Set KIND_family, KIND_platform, KIND_type, KIND_bindir,
## KIND_variant_hosted, KIND_variant_native, and
## KIND_variant_freestanding

AC_DEFUN([_TAL_SYS],[
AS_LITERAL_IF([$1],,[m4_fatal([_TAL_SYS: $1 is not a literal])])dnl
# Determine ]$1[ system family, platform, platform type (freestanding,
# native, hosted)

AC_MSG_CHECKING([for ]$1[ system CPU architecture family])
_TAL_SYS_FAMILY([$1])
AC_MSG_RESULT([$]$1[_family])

AC_MSG_CHECKING([for ]$1[ platform and type])
_TAL_SYS_PLATFORM([$1])
_TAL_SYS_TYPE([$1])
_TAL_SYS_BINDIR([$1])
AC_MSG_RESULT([$]$1[_platform ($]$1[_type)])

m4_if([$1],[host],[_TAL_SYS_VARIANTS([$1])])
m4_if([$1],[target],[_TAL_SYS_VARIANTS([$1])])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_SYS_FAMILY($1:KIND=build|host|target)
##---------------------------------------------------------------------
## Set KIND_family based on KIND_cpu

AC_DEFUN([_TAL_SYS_FAMILY],[
case "$]$1[_cpu" in
	i?86)
		AS_VAR_SET($1[_family], ['i386'])
		;;
	x86_64|amd64)
		AS_VAR_SET($1[_family], ['x86_64'])
		;;
	*)
		AS_VAR_SET($1[_family],["$]$1[_cpu"])
		;;
esac
AC_SUBST($1[_family])
AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_FAMILY],["$]$1[_family"],[The name of the ]$1[ CPU family that we are building for])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_SYS_PLATFORM($1:KIND=build|host|target)
##---------------------------------------------------------------------
## Set KIND_platform based upon tal_os

AC_DEFUN([_TAL_SYS_PLATFORM],[
AS_VAR_SET([tal_check],["$]$1[_os"])
m4_changequote({,})dnl
case "$tal_check" in
	linux-*)
		tal_platform='linux'
		;;
	*)
		tal_platform="`echo $tal_check | sed 's@[0-9.]*{$}@@;'`"
		;;
esac
m4_changequote([,])dnl
AS_VAR_SET($1_[platform], ["${tal_platform}"])
AC_SUBST($1[_platform])
AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_PLATFORM],["$]$1[_platform"],[The name of the ]$1[ platform that we are building for])
])

##---------------------------------------------------------------------
## INTERNAL- _TAL_SYS_TYPE($1:KIND=build|host|target)
##---------------------------------------------------------------------
## Set KIND_type based upon KIND_os and KIND_vendor

AC_DEFUN([_TAL_SYS_TYPE],[
case "$]$1[_os" in
	none|elf*|coff*|ecoff*|aout*|oabi*|eabi*)
		AS_VAR_SET($1[_type], ['freestanding'])
		;;
	*)
		if test x"$]$1[_vendor" = x"none" ; then
			AS_VAR_SET($1[_type], ['native'])
		else
			AS_VAR_SET($1[_type], ['hosted'])
		fi
esac
AC_SUBST($1[_type])
AC_DEFINE_UNQUOTED(m4_translit([$1], [a-z], [A-Z])[_TYPE],["$]$1[_type"],[The type of ]$1[ platform that we are building for])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_SYS_BINDIR($1:KIND=build|host|target)
##---------------------------------------------------------------------
## Set KIND_bindir

AC_DEFUN([_TAL_SYS_BINDIR],[
case "$]$1[_type" in
	hosted)
		AS_VAR_SET($1[_bindir], ['${host_family}-${host_vendor}-${host_platform}'])
		;;
	native)
		AS_VAR_SET($1[_bindir], ['${host_family}-${host_platform}'])
		;;
	freestanding)
		AS_VAR_SET($1[_bindir], ['${host_family}'])
		;;
esac
AC_SUBST($1[_bindir])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_SYS_VARIANTS($1:KIND=build|host|target)
##---------------------------------------------------------------------
## Set KIND_variant_hosted, KIND_variant_native, and
## KIND_variant_freestanding

AC_DEFUN([_TAL_SYS_VARIANTS],[
case "$]$1[_type" in
	hosted)
		AS_VAR_SET($1[_variant_hosted], ["${]$1[_cpu}-${]$1[_vendor}-${]$1[_platform}"])
		AS_VAR_SET($1[_variant_native], ["${]$1[_cpu}-none-${]$1[_platform}"])
		AS_VAR_SET($1[_variant_freestanding], ["${]$1[_cpu}-none"])
		;;
	native)
		AS_VAR_SET($1[_variant_hosted], [''])
		AS_VAR_SET($1[_variant_native], ["${]$1[_cpu}-none-${]$1[_platform}"])
		AS_VAR_SET($1[_variant_freestanding], ["${]$1[_cpu}-none"])
		;;
	freestanding)
		AS_VAR_SET($1[_variant_hosted], [''])
		AS_VAR_SET($1[_variant_native], [''])
		AS_VAR_SET($1[_variant_freestanding], ["${]$1[_cpu}-none"])
		;;
esac
AC_SUBST($1[_variant_hosted])
AC_SUBST($1[_variant_native])
AC_SUBST($1[_variant_freestanding])
])