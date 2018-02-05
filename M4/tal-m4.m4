#serial 2017120400
# Talisker: Keep distributed files up to date

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
## TAL_M4_UPDATE
##---------------------------------------------------------------------
## Substitute a Makefile fragment which adds a `make m4-update` target which
## checks the timestamps on M4 macro files in the source tree against those
## installed on the system, and updates the tree if newer versions are
## installed system-wide.
##
## In an ideal world, aclocal/autoreconf would be able to do this for us,
## but they do not always play nicely 
##
## Remember that this an M4 macro which is expanded to a shell fragment that
## defines a rule that will be substituted into a Makefile, so care must be
## taken with escaping, newlines and quoting.

AC_DEFUN([TAL_M4_UPDATE],[
AC_REQUIRE([_TAL_INIT])
AC_REQUIRE([_TAL_M4_UPDATE])
])

##---------------------------------------------------------------------
## INTERNAL - _TAL_M4_UPDATE
##---------------------------------------------------------------------
## Perform the actual update

AC_DEFUN([_TAL_M4_UPDATE],[
AC_REQUIRE([AC_CONFIG_AUX_DIR_DEFAULT])dnl
AC_REQUIRE_AUX_FILE([tal-m4.mk])dnl
tal__aux_dir="$ac_aux_dir"
tal_m4_update="$tal__aux_dir/tal-m4.mk"
AC_SUBST([tal__aux_dir])
AC_SUBST_FILE([tal_m4_update])
])
