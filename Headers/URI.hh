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

#ifndef TALISKER_URI_HH_
# define TALISKER_URI_HH_               1

# include "Object.hh"

namespace Talisker
{
#ifndef TALISKER_INTERNAL_FOUNDATION_
	struct URIPrivate;
#endif

	class TALISKER_EXPORT_ URI: public Object
	{
	public:
		URI(const char *uri);
		virtual ~URI();
	protected:
		URIPrivate *m_uri;
	};
};

#endif /*!TALISKER_URI_HH_*/
