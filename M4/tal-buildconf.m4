#serial 2017120400
# Talisker: Enable build configuration files

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
m4_pattern_allow([^TAL_BUILDCONFIG$])

##---------------------------------------------------------------------
## TAL_BUILDCONF
##---------------------------------------------------------------------
## Source a build configuration, if one is available.
##
## Build configurations are shell scripts which call one of a limited
## number of functions to set configuration parameters to particular
## values.
##
## For example, a build configuration named DEBUG might contain the
## following:
##
## enable debug
##
## The functions 'enable', 'disable', 'with' and 'without' are provided,
## and are analogous to the ``configure'' parameters with the same prefixes.
## The 'enable' and 'with' functions optionally accept a second argument,
## which is the value that should be used in place of 'yes'. For example:
##
## with libiconv-prefix /opt/gnu
##
## Build configurations are searched for in the following locations:
##
## ${builddir}/BuildConfigurations
## ${srcdir}/BuildConfigurations
## ${ac_aux_dir}/../BuildConfigurations
## /Developer/Library/BuildConfigurations
##
## A build configuration (either a name or a full path) may be specified
## using either --with-build-config=NAME or by setting the $TAL_BUILDCONFIG
## environment variable. If neither is specified, the build configuration
## DEFAULT will be used if it can be located. This behaviour can be disabled
## by specifying --without-build-config when configuring.
##
## Build configurations may manipulate variables and execute external
## programs, but care should be taken: the script is sourced within the
## context of an already-complex script (configure), and the more complex
## a build configuration becomes, the harder it is to maintain and understand.

AC_DEFUN([TAL_BUILDCONF],[
AC_REQUIRE([_TAL_INIT])dnl
AC_REQUIRE([_TAL_BUILDCONF])dnl
])
	
##---------------------------------------------------------------------
## INTERNAL - AC_CONFIG_AUX_DIRS() wrapper
##---------------------------------------------------------------------
## We use this wrapper to ensure that we can include the list of
## auxilliary directories as part of the build configurations search
## path. This has the side-effect of meaning we have to iterate these
## directories twice, but that's not a huge penalty.
##---------------------------------------------------------------------
m4_ifdef([_TAL_AC_CONFIG_AUX_DIRS],,[
m4_rename([AC_CONFIG_AUX_DIRS],[_TAL_AC_CONFIG_AUX_DIRS])dnl
AC_DEFUN([AC_CONFIG_AUX_DIRS],[
AC_BEFORE([$0],[_TAL_BUILDCONF])
_TAL_AC_CONFIG_AUX_DIRS($1)
m4_divert_push([INIT_PREPARE])dnl
tal_aux_dir=
for tal_try in $1 ; do
	if test -r "$tal_try/install-sh" ||
		test -r "$tal_try/install.sh" ||
		test -r "$tal_try/shtool" ; then
		tal_aux_dir="$tal_try"
		break
	fi
done
m4_divert_pop([INIT_PREPARE])dnl
AC_PROVIDE([AC_CONFIG_AUX_DIR_DEFAULT])dnl
])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_BUILDCONF
##---------------------------------------------------------------------
## Determine the name of the build configuration, if any, then evaluate
## it.

AC_DEFUN([_TAL_BUILDCONF],[
AC_REQUIRE([AC_CONFIG_AUX_DIR_DEFAULT])dnl
AC_BEFORE([$0],[AC_ARG_ENABLE])dnl
AC_BEFORE([$0],[AC_ARG_WITH])dnl
AC_BEFORE([$0],[AC_ARG_VAR])dnl
AC_BEFORE([$0],[AC_CANONICAL_HOST])dnl
AC_BEFORE([$0],[AC_CANONICAL_TARGET])dnl
AC_BEFORE([$0],[AC_CANONICAL_SYSTEM])dnl

m4_divert_push([INIT_PREPARE])dnl

AC_ARG_VAR([TAL_BUILDCONFIG],[the name of the build configuration to load options from])

AC_ARG_WITH([build-config],
  [AS_HELP_STRING([--with-build-config=NAME],[load configure options from the build configuration file NAME])],
  [tal_build_config="$withval"],
  [tal_build_config=$TAL_BUILDCONFIG])

_TAL_BUILDCONF_FUNCTIONS

if test x"$tal_build_config" = x"yes" ; then
	AC_MSG_ERROR([you must specify a configuration name or path with the --with-build-config option])
elif test x"$tal_build_config" = x"no" ; then
	true
	unset tal_build_config
	unset TAL_BUILDCONFIG
elif test x"$tal_build_config" = x"" ; then
	tal_build_config=DEFAULT
	tal_fail=no
else
	tal_fail=yes
fi

if test -n "$tal_build_config" ; then
	_TAL_BUILDCONF_EXISTS([
		TAL_ECHO([using build configuration ${tal_build_config_name}])
	],[
		if test $tal_fail = yes ; then
			AC_MSG_ERROR([cannot find build configuration ${tal_build_config}])
		fi
	])
fi

if test -n "$TAL_BUILDCONFIG" ; then
	_TAL_BUILDCONF_EVAL
fi
m4_divert_pop([INIT_PREPARE])dnl
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_BUILDCONF_EXISTS($1=ACTION-IF-FOUND, $2=ACTION-IF-NOT_FOUND)
##---------------------------------------------------------------------
## Attempt to locate the build configuration ${tal_build_config}, executing
## $1 or $2 depending upon the result. Invokes _TAL_BUILDCONF_SET

AC_DEFUN([_TAL_BUILDCONF_EXISTS],[
tal_build_config_name=`basename "${tal_build_config}" 2>/dev/null` || tal_build_config_name="${tal_build_config}"
tal_found=no
case "$tal_build_config" in
	/*|*/*)
		if test -r "$tal_build_config" ; then
			tal_found=yes
		fi
		;;
	*)
		for tal_try in "BuildConfigurations/${tal_build_config}" \
			"${srcdir}/BuildConfigurations/${tal_build_config}" \
			"${tal_aux_dir}/../BuildConfigurations/${tal_build_config}" \
			"/Developer/Library/BuildConfigurations/${tal_build_config}" ; do
			if test -r "$tal_try" ; then
				tal_found=yes
				tal_build_config="$tal_try"
				break
			fi
		done
		;;
esac
if test $tal_found = yes ; then
	_TAL_BUILDCONF_SET
	$1
else
	unset TAL_BUILDCONFIG
	$2
fi
	
AC_SUBST([TAL_BUILDCONFIG])
AC_SUBST([tal_build_config])
AC_SUBST([tal_build_config_name])
AC_DEFINE_UNQUOTED([TAL_BUILDCONFIG],["${tal_build_config_name}"],[The name of the build configuration])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_BUILDCONF_SET
##---------------------------------------------------------------------
## Set TAL_BUILDCONFIG based on ${tal_build_config}

AC_DEFUN([_TAL_BUILDCONF_SET],[
tal_dir=`dirname "$tal_build_config"`
tal_dir=`cd "$tal_dir" && pwd`
tal_base=`basename "$tal_build_config"`
TAL_BUILDCONFIG="$tal_dir/$tal_base"
export TAL_BUILDCONFIG
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_BUILDCONF_EVAL
##---------------------------------------------------------------------
## Source ${TAL_BUILDCONFIG}

AC_DEFUN([_TAL_BUILDCONF_EVAL],[
if source "$TAL_BUILDCONFIG" ; then
	true
else
	AC_MSG_ERROR([error in build configuration ${tal_build_config_name}])
fi
])
	
##---------------------------------------------------------------------
## INTERNAL - _TAL_BUILDCONF_FUNCTIONS
##---------------------------------------------------------------------
## Contains all of the shell functions that can be invoked within a
## build configuration

AC_DEFUN([_TAL_BUILDCONF_FUNCTIONS],[
AC_BEFORE([$0],[_TAL_BUILDCONF_EVAL])

##
## Functions for use within build configurations
##

with() {
	AS_VAR_SET([tal_optname],AS_TR_SH([with_$][1]))
	AS_VAR_SET([tal_optarg],[$][2])
	test x"$tal_optarg" = x"" && tal_optarg=yes
	AS_VAR_SET([$tal_optname], [$tal_optarg])
}

without() {
	AS_VAR_SET([tal_optname],AS_TR_SH([with_$][1]))
	AS_VAR_SET([tal_optarg],[no])
	AS_VAR_SET([$tal_optname], [$tal_optarg])
}

enable() {
	AS_VAR_SET([tal_optname],AS_TR_SH([enable_$][1]))
	AS_VAR_SET([tal_optarg],["$][2"])
	test x"$tal_optarg" = x"" && tal_optarg=yes
	AS_VAR_SET([$tal_optname], [$tal_optarg])
}

disable() {
	AS_VAR_SET([tal_optname],AS_TR_SH([enable_$][1]))
	AS_VAR_SET([tal_optarg],[no])
	AS_VAR_SET([$tal_optname], [$tal_optarg])
}

option() {
	AS_VAR_SET([tal_optname],AS_TR_SH([$][1]))
	AS_VAR_SET([tal_optarg],[$][2])
	case "$tal_optname" in
		host|target|prefix|exec_prefix|bindir|sbindir|libexecdir|\
			sysconfdir|sharedstatedir|localstatedir|libdir|\
			includedir|oldincludedir|datarootdir|datadir|infodir|localedir|\
			mandir|docdir|htmldir|dvidir|pdfdir|psdir|\
			site|srcdir|x_includes|x_libraries|cache_file)
			if test x"$tal_optarg" = x"" ; then
				AC_MSG_ERROR([${tal_build_config_name}: option '$]1[' requires an argument])
			fi
			AS_VAR_SET([$tal_optname],[$tal_optarg])
		;;
		no_create|no_recursion|quiet|silent|verbose)
			if ! test x"$tal_optarg" = x"" ; then
				AC_MSG_ERROR([${tal_build_config_name}: option '$]1[' does not accept an argument])
			fi
			AS_VAR_SET([$tal_optname],[yes])
		;;
		config_cache)
			if ! test x"$tal_optarg" = x"" ; then
				AC_MSG_ERROR([${tal_build_config_name}: option '$]1[' does not accept an argument])
			fi
			cache_file=config.cache
		;;
		*)
			AC_MSG_ERROR([${tal_build_config_name}: unknown option '$]1['])
		;;
	esac
}
])
	
