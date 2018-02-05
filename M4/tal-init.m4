#serial 2017120400
# Talisker: Install wrappers around various Autoconf macros

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
## TAL_INIT
##---------------------------------------------------------------------
## A placeholder

AC_DEFUN([TAL_INIT],[
AC_BEFORE([$0],[AM_INIT_AUTOMAKE])dnl
AC_BEFORE([$0],[LT_INIT])dnl
AC_BEFORE([$0],[AC_ARG_PROGRAM])dnl
AC_BEFORE([$0],[AC_ARG_WITH])dnl
AC_BEFORE([$0],[AC_ARG_ENABLE])dnl
AC_BEFORE([$0],[AC_CANONICAL_BUILD])dnl
AC_REQUIRE([_TAL_INIT])dnl
])dnl

##---------------------------------------------------------------------
## INTERNAL - TAL_INIT
##---------------------------------------------------------------------
## Everything ultimately depends upon _TAL_INIT, so anything which must
## always happen should happen here

AC_DEFUN([_TAL_INIT],[
AC_REQUIRE([_TAL_SYS_INIT])dnl
AC_REQUIRE([_TAL_M4_UPDATE])dnl
AC_REQUIRE([_TAL_BUILDCONF])dnl
])
	