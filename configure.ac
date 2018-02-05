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
## Initialise Autoconf and Automake with project-specific information      ##
#############################################################################

AC_INIT([FoundationKit],[develop])
AS_VAR_SET([DESC], ["Talisker Foundation Toolkit framework"])
AC_CONFIG_AUX_DIR([BuildScripts])
AC_CONFIG_MACRO_DIR([M4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_MAINTAINER_MODE
AC_CONFIG_HEADER([config.h])

#############################################################################
## Check for basic system utilities and build tools (e.g., compilers)      ##
#############################################################################

AC_PROG_LN_S
AC_PROG_CC([clang c99 g++ cc])
AC_PROG_CXX([clang++ g++ c++])

AC_CHECK_PROG([IDL],[idl],[idl],)
if test x"$IDL" = x"" ; then
	AC_MSG_ERROR([
Cannot locate the Talisker IDL compiler, which is required to build the
${DESC}.

The source repository for the compiler can be found at:
  <https://github.com/TaliskerPlatform/idl>
])
fi

LT_INIT

if test x"$GCC" = x"yes" ; then
	AS_VAR_APPEND([AM_CFLAGS], ['-W -Wall '])
	AS_VAR_APPEND([AM_CFLAGS], ['-fvisibility=hidden '])
fi

if test x"$GXX" = x"yes" ; then
	AS_VAR_APPEND([AM_CXXFLAGS], ['-W -Wall '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-fvisibility=hidden '])
fi

AS_VAR_APPEND([AM_CPPFLAGS], ['-I${top_srcdir}/Headers '])
AS_VAR_APPEND([AM_CPPFLAGS], ['-I${top_builddir}/Headers '])

AC_SUBST([LIBS])
AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

#############################################################################
## Project-specific compilation environment tests                          ##
#############################################################################

AC_CHECK_FUNC([uuid_generate],,[
	AC_CHECK_LIB([uuid],[uuid_generate],,[
		AC_MSG_ERROR([cannot locate UUID library (-luuid)])
	])
])


AC_CHECK_FUNC([pthread_create],,[
	AC_CHECK_LIB([pthread],[pthread_create],,[
		AC_MSG_ERROR([cannot locate POSIX threads library (-lpthread)])
	])
])

AC_CHECK_FUNCS([pthread_main_np])

AC_CHECK_FUNC([dlopen],,[
	AC_CHECK_LIB([dl],[dlopen],,[
		AC_MSG_ERROR([cannot locate dynamic loader library (-ldl)])
	])
])


PRIVATE_CONFIG_URIPARSER

#############################################################################
## Substitute variables for a "framework" project                          ##
#############################################################################

AS_VAR_SET([frameworkname], ['${PACKAGE_NAME}'])

case "$host_os" in
	darwin[1-9]*)
		AS_VAR_SET([frameworkdir], ['/Library/Frameworks/${frameworkname}.framework'])
		AS_VAR_SET([frameworkbindir], ['${frameworkdir}/Versions/${VERSION}/'])
		AS_VAR_SET([frameworklibdir], ['${frameworklibdir}'])
		AS_VAR_SET([frameworkheadersdir], ['${frameworkdir}/Versions/${VERSION}/Headers'])
		AS_VAR_SET([frameworkdocdir], ['${frameworkdir}/Documentation'])
		AS_VAR_SET([framework_fixups], [yes])
		AS_VAR_SET([dylibext],['.dylib'])
		;;
	*)
		AS_VAR_SET([frameworkdir], ['${prefix}'])
		AS_VAR_SET([frameworkbindir], ['${bindir}'])
		AS_VAR_SET([frameworklibdir], ['${libdir}'])
		AS_VAR_SET([frameworkheadersdir], ['${includedir}/${PACKAGE_NAME}'])
		AS_VAR_SET([frameworkdocdir],['${datarootdir}/doc/${PACKAGE_NAME}'])
		AS_VAR_SET([dylibext],['.so'])
esac

AC_SUBST([frameworkname])
AC_SUBST([frameworkdir])
AC_SUBST([frameworklibdir])
AC_SUBST([frameworkheadersdir])
AC_SUBST([frameworkdocdir])
AC_SUBST([dylibext])

AM_CONDITIONAL([FRAMEWORK_FIXUPS], [test x"$framework_fixups" = x"yes"])

#############################################################################
## Output files                                                            ##
#############################################################################

AC_CONFIG_FILES([
Makefile
IDL/Makefile
Headers/Makefile
Sources/Makefile
ThirdParty/Makefile
])

AC_OUTPUT
