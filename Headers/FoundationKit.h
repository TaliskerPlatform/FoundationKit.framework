/* Talisker
 * Foundation Toolkit
 */

/* Copyright 2012-2017 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef TALISKER_FOUNDATIONKIT_H_
# define TALISKER_FOUNDATIONKIT_H_     1

/* Foundation Toolkit interfaces */

# include "IObject.h"
# include "IAllocator.h"
# include "IFactory.h"
# include "IRegistry.h"

/* Foundation Toolkit classes */

#  include "Object.hh"

# if defined(__cplusplus)

#  include "Factory.hh"
#  include "DefaultAllocator.hh"
#  include "Process.hh"
#  include "Thread.hh"
#  include "String.hh"
#  include "URI.hh"
#  include "UUID.hh"
#  include "Registry.hh"
#  include "Array.hh"
#  include "Dictionary.hh"

# endif /*__cplusplus*/

#endif /*!TALISKER_FOUNDATIONKIT_H_*/
