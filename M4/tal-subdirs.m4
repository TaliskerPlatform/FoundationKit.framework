#serial 2017120400
# Talisker: Configure sub-projects

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

dnl - TAL_CONFIG_SUBDIR($1:SRC-PATH, [$2:BUILD-PATH], [$3:EXTRA-ARGUMENTS], [$4:POST-CONFIGURE-COMMANDS], [$5:HOST=$host], [$6:TARGET=$target], [$7:BUILD=$build],[$8:FOUND-COMMANDS],[$9:NOT-FOUND-COMMANDS])
dnl Analogous to AC_CONFIG_SUBDIR but allows overriding both the build
dnl location and configure arguments

AC_DEFUN([TAL_CONFIG_SUBDIR],[
AC_REQUIRE([_TAL_INIT])dnl
AS_LITERAL_IF([$1],,[m4_fatal([TAL_CONFIG_SUBDIR: $1 is not a literal])])dnl
AS_LITERAL_IF([$2],,[m4_fatal([TAL_CONFIG_SUBDIR: $2 is not a literal])])dnl
dnl
dnl Add a no-op AC_CONFIG_SUBDIRS for the source directory so that
dnl recursive autoreconf and configure --help=recursive work
dnl correctly
if false ; then
	dnl Prevent AC_CONFIG_SUBDIRS being expanded more than once for the
	dnl same SRC-PATH
	m4_ifdef([tal_wrapname], [m4_undefine([tal_wrapname])])dnl
	m4_define([tal_wrapname], [tal_srcdir_]$1)dnl
	m4_ifdef(m4_defn([tal_wrapname]),[:],[
		m4_define(m4_defn([tal_wrapname]))
		AC_CONFIG_SUBDIRS([$1])
	])
fi
dnl
dnl If this is the first call to TAL_CONFIG_SUBDIR(), perform one-off
dnl actions (defining _TAL_OUTPUT_SUBDIRS so that it can be expanded later)
dnl
m4_ifset([_TAL_OUTPUT_SUBDIRS],,[
	m4_define([tal_subcount],[0])dnl
	m4_define([_TAL_OUTPUT_SUBDIRS],[
##
## Talisker: configure subdirectories
##
		TAL_ECHO([configuring subdirectories...])
		tal_popdir=`pwd`
		_TAL_SUBDIR_CONFIGURE_ARGS
])
	AC_CONFIG_COMMANDS_PRE([_TAL_OUTPUT_SUBDIRS])
])

dnl
dnl Because this macro may be expanded inside a shell conditional, we need
dnl to set a variable unique this is macro invocation that can be
dnl checked for in the fragment (executed later) that is appended to the
dnl _TAL_OUTPUT_SUBDIRS() macro.
dnl
m4_ifdef([tal_varname], [m4_undefine([tal_varname])])dnl
m4_define([tal_varname], [tal_subdir_try]m4_defn([tal_subcount]))dnl

## Preflight checks for sub-project in $1

AS_VAR_SET([m4_defn([tal_varname])], [no])
tal_type=none
tal_sub=''
tal_srcdir="$1"
tal_abs_srcdir="$ac_abs_confdir/$tal_srcdir"
tal_builddir="]m4_ifval($2,$2,$1)["
tal_abs_builddir="$ac_pwd$ac_dir_suffix/$tal_builddir"
# Determine what sort of configuration needs to happen

_TAL_SUBDIR_DETECT

if test x"$tal_type" != x"none" ; then
	m4_defn([tal_varname])=yes
	$8
else
	true
	$9
fi
m4_defn([tal_varname])_type="$tal_type"
m4_defn([tal_varname])_sub="$tal_sub"

dnl Append our sub-configure fragment to _TAL_OUTPUT_SUBDIRS(), which will
dnl be executed as part of AC_CONFIG_COMMANDS_PRE() (see above) just before
dnl ./config.status is generated. This is earlier than AC_CONFIG_SUBDIRS(),
dnl but allows AC_SUBST() variables to be influenced by the results of the
dnl sub-configure (for example, if the sub-configure generates a
dnl *-uninstalled.pc file that the parent needs to use with pkg-config.

m4_append([_TAL_OUTPUT_SUBDIRS],[
## Configure sub-project ]$1[ in ]m4_ifval($2,$2,$1)[
if test x"$no_recursion" != xyes && test x"$]m4_defn([tal_varname])[" = xyes; then
	tal_srcdir="$1"
	tal_abs_srcdir="$ac_abs_confdir/$tal_srcdir"
	tal_builddir="]m4_ifval($2,$2,$1)["
	tal_abs_builddir="$ac_pwd$ac_dir_suffix/$tal_builddir"
	tal_sub_type=$]m4_defn([tal_varname])[_type
	tal_sub_configure=$]m4_defn([tal_varname])[_sub
	
	if test x"$tal_srcdir" = x"$tal_builddir" ; then
		TAL_ECHO([=== configuring sub-project $tal_srcdir])
	else
		TAL_ECHO([=== configuring sub-project $tal_srcdir in $tal_builddir])
	fi
	AS_MKDIR_P(["$tal_abs_builddir"])
	cd "$tal_abs_builddir"
	
	if test x"$tal_sub_type" == x"autoconf" ; then
		# Extend $tal_sub_configure_args for this specific project
		tal_arg="$tal_abs_srcdir"
		_TAL_SUBDIR_ARG_QUOTE
		tal_sub_args="--srcdir='$tal_arg' $tal_sub_configure_args $3"
	
		# Add build, host, target
		tal_arg="]m4_ifval($7,$7,[$build])["
		_TAL_SUBDIR_ARG_QUOTE
		AS_VAR_APPEND([tal_sub_args],[" --build='$tal_arg'"])

		tal_arg="]m4_ifval($5,$5,[$host])["
		_TAL_SUBDIR_ARG_QUOTE
		AS_VAR_APPEND([tal_sub_args],[" --host='$tal_arg'"])

		tal_arg="]m4_ifval($6,$6,[$target])["
		_TAL_SUBDIR_ARG_QUOTE
		AS_VAR_APPEND([tal_sub_args],[" --target='$tal_arg'"])

		if test -n "$TAL_BUILDCONF" ; then
			tal_arg="$TAL_BUILDCONFIG"
			_TAL_SUBDIR_ARG_QUOTE
			AS_VAR_APPEND([tal_sub_args],[" TAL_BUILDCONFIG='$tal_arg'"])
		fi
		TAL_ECHO([running $SHELL $tal_abs_srcdir/$tal_sub_configure $tal_sub_args])
		eval "\$SHELL \"\$tal_abs_srcdir/\$tal_sub_configure\" $tal_sub_args" || AC_MSG_ERROR([$tal_sub_configure failed for $tal_srcdir])
	elif test x"$tal_sub_type" = x"bootstrap" ; then
		tal_sub_args="$tal_bootstrap_args $3"
		TAL_ECHO([running $SHELL $tal_abs_srcdir/$tal_sub_configure $tal_sub_args])
		eval "\$SHELL \"\$tal_abs_srcdir/\$tal_sub_configure\" $tal_sub_args" || AC_MSG_ERROR([$tal_sub_configure failed for $tal_srcdir])
	elif test x"$tal_sub_type" = x"cmake" ; then
		AC_MSG_ERROR([currently unable to build CMake projects])
	fi
	]m4_ifval([$4],[$4],[
	AS_VAR_APPEND([tal_subdirs],[" $tal_builddir"])
	AC_SUBST([tal_subdirs])
	])[
	if test x"$tal_srcdir" = x"$tal_builddir" ; then
		TAL_ECHO([=== configured sub-project $tal_srcdir])
	else
		TAL_ECHO([=== configured sub-project $tal_srcdir in $tal_builddir])
	fi
fi
cd "$tal_popdir"
])dnl
m4_define([tal_result],m4_incr(m4_defn([tal_subcount])))dnl
m4_copy_force([tal_result],[tal_subcount])dnl
])

dnl - _TAL_SUBDIR_DETECT()
dnl Determine the type of subject-project in $tal_srcdir. The following shell
dnl variables are used:
dnl   INPUT:  $tal_abs_srcdir, $tal_srcdir
dnl   OUTPUT: $tal_type, $tal_sub
AC_DEFUN([_TAL_SUBDIR_DETECT],[
if test -d "$tal_abs_srcdir" ; then
	AC_MSG_CHECKING([for type of sub-project in $tal_srcdir])
	if test -f "$tal_abs_srcdir/bootstrap"; then
		tal_type=bootstrap
		tal_sub='bootstrap'
	elif test -f "$tal_abs_srcdir/configure.gnu"; then
		tal_type=autoconf
		tal_sub='configure.gnu'
	elif test -f "$tal_abs_srcdir/configure"; then
		tal_type=autoconf
		tal_sub='configure'
	elif test -f "$tal_abs_srcdir/CMakeLists.txt" ; then
		tal_type=cmake
	fi
	AC_MSG_RESULT([$tal_type])
	if test x"$tal_type" = x"none" ; then
		AC_MSG_WARN([no configuration information is in $tal_srcdir but directory is present])
	fi
fi
])

dnl - _TAL_SUBDIR_CONFIGURE_ARGS()
dnl Determine the arguments that will be passed to a configure script
dnl Sets $tal_sub_configure_args (which should not be modified once set)
AC_DEFUN([_TAL_SUBDIR_CONFIGURE_ARGS],[
tal_sub_configure_args=''
tal_bootstrap_args=''

# Prepend --disable-option-checking to prevent warnings about options which
# aren't known to this specific sub-project
AS_VAR_APPEND([tal_sub_configure_args], [' --disable-option-checking'])

# Prepend --silent if it was provided to us
if test x"$silent" = xyes; then
	AS_VAR_APPEND([tal_sub_configure_args], [' --silent'])
fi

# Prepend --prefix
tal_arg="$prefix"
_TAL_SUBDIR_ARG_QUOTE
AS_VAR_APPEND([tal_sub_configure_args],[" --prefix='$tal_arg'"])
AS_VAR_APPEND([tal_bootstrap_args],[" --prefix='$tal_arg'"])

# Strip arguments, such as --cache-file, that we don't want to be propagated
# (e.g., because we've provided alternative)
eval "set x $ac_configure_args"
shift
tal_skip=no
for tal_arg
do
	# tal_skip=yes when the previous argument accepted an argument which is
	# now in tal_arg (i.e., the user supplied '--foo bar' instead of
	# '--foo=bar')
	if test $tal_skip = yes ; then
		tal_skip=no
		continue
	fi
	# Ignore options we don't want, add the remainder to tal_sub_configure_args
	# Note that configure accepts shortened forms of some arguments, so we must
	# adhere to that.
	case "$tal_arg" in
		--disable-option-checking)
			;;
		--build=*|--host=*|--target=*)
			;;
		--build|--host|--target)
			tal_skip=yes
			;;
		-cache-file=* | --cache-file=* | --cache-fil=* | --cache-fi=* | --cache-f=* | --cache-=* | --cache=* | --cach=* | --cac=* | --ca=* | --c=*)
			;;
		--config-cache | -C)
			;;
		-cache-file | --cache-file | --cache-fil | --cache-fi | --cache-f | --cache- | --cache | --cach | --cac | --ca | --c)
			tal_skip=yes
			;;
		-srcdir=* | --srcdir=* | --srcdi=* | --srcd=* | --src=* | --sr=*)
			;;
		-srcdir | --srcdir | --srcdi | --srcd | --src | --sr)
			tal_skip=yes
			;;
		-prefix=* | --prefix=* | --prefi=* | --pref=* | --pre=* | --pr=* | --p=*)
			;;
		-prefix | --prefix | --prefi | --pref | --pre | --pr | --p)
			tal_skip=yes
			;;
		target_alias=*|host_alias=*|build_alias=*)
			tal_skip=yes
			;;
		*)
			_TAL_SUBDIR_ARG_QUOTE
			AS_VAR_APPEND([tal_sub_configure_args],[" '$tal_arg'"])
			;;
		esac
done
])

dnl Substitute characters in $tal_arg to make it suitable for enclosing
dnl in single-quotes in another shell variable
AC_DEFUN([_TAL_SUBDIR_ARG_QUOTE],[
case $tal_arg in
	*\'*)
		tal_arg=`AS_ECHO(["$tal_arg"]) | sed "s/'/'\\\\\\\\''/g"`
		;;
esac
])
