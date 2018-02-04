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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_foundation.hh"

using namespace Talisker;

static UriUriA *
uri_parse(const char *str)
{
	UriUriA *uri;
	UriParserStateA state;

	uri = new UriUriA;
	state.uri = uri;
	if(uriParseUriA(&state, str) != URI_SUCCESS)
	{
		Talisker::err("failed to parse URI <%s>\n", str);
		delete uri;
		return NULL;
	}
	return uri;
}

URI::URI(const char *uri):
	Object::Object()
{
	m_uri = uri_parse(uri);   
}

URI::~URI()
{
	if(m_uri)
	{
		uriFreeUriMembersA(m_uri);
		delete m_uri;
	}
}

