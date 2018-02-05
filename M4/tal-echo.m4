#serial 2017120400
# Talisker: User messages

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

dnl - TAL_ECHO(MSG)
dnl Emit a message for the user, logging it as well

AC_DEFUN([TAL_ECHO],[
_AS_ECHO_LOG([$1])
_AS_ECHO([$1])
])
