/*
** Copyright 2014-2018 The Earlham Institute
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
/*
 * simple_external_servers_manager.c
 *
 *  Created on: 10 Sep 2019
 *      Author: billy
 */


/*
** Copyright 2014-2016 The Earlham Institute
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include <string.h>


#include "simple_external_servers_manager.h"




static ExternalServerNode *GetExternalServerNode (SimpleExternalServersManager *manager_p, const char * const server_uri_s);

static ExternalServer *GetExternalServerFromExternalServersManager (ServersManager *manager_p, const char * const server_uri_s, ExternalServerDeserialiser deserialise_fn);

static ExternalServer *RemoveExternalServerFromExternalServersManager (ServersManager *manager_p, const char * const server_uri_s, ExternalServerDeserialiser deserialise_fn);

static bool AddExternalServerToExternalServersManager (ServersManager *manager_p, ExternalServer *server_p, ExternalServerSerialiser serialise_fn);

static LinkedList *GetAllExternalServersFromExternalServersManager (ServersManager *manager_p, ExternalServerDeserialiser deserialise_fn);



ServersManager *GetCustomServersManager (void)
{
	return AllocateSimpleExternalServersManager ();
}


void ReleaseServersManager (ServersManager *manager_p)
{
	FreeSimpleExternalServersManager (manager_p);
}



ServersManager *AllocateSimpleExternalServersManager (void)
{
	SimpleExternalServersManager *manager_p = (SimpleExternalServersManager *) AllocMemory (sizeof (SimpleExternalServersManager));

	if (manager_p)
		{
			InitServersManager (& (manager_p -> sesm_base_manager), AddExternalServerToExternalServersManager, GetExternalServerFromExternalServersManager, RemoveExternalServerFromExternalServersManager, GetAllExternalServersFromExternalServersManager, FreeSimpleExternalServersManager);
			InitLinkedList (& (manager_p -> sesm_servers));

			return (& (manager_p -> sesm_base_manager));
		}

	return NULL;
}


void FreeSimpleExternalServersManager (ServersManager *manager_p)
{
	SimpleExternalServersManager *real_manager_p = (SimpleExternalServersManager *) manager_p;

	ClearLinkedList (& (real_manager_p -> sesm_servers));
	FreeMemory (real_manager_p);
}




static bool AddExternalServerToExternalServersManager (ServersManager *manager_p, ExternalServer *server_p, ExternalServerSerialiser UNUSED_PARAM (serialise_fn))
{
	bool success_flag = false;
	SimpleExternalServersManager *external_servers_manager_p = (SimpleExternalServersManager *) manager_p;
	ExternalServerNode *node_p = GetExternalServerNode (external_servers_manager_p, server_p -> es_uri_s);

	if (node_p)
		{
			success_flag = (node_p -> esn_server_p == server_p);
		}
	else
		{
			node_p = AllocateExternalServerNode (server_p, MF_SHADOW_USE);

			if (node_p)
				{
					LinkedListAddTail (& (external_servers_manager_p -> sesm_servers), (ListItem * const) node_p);
					success_flag = true;
				}
		}

	return success_flag;
}


static ExternalServerNode *GetExternalServerNode (SimpleExternalServersManager *manager_p, const char * const server_uri_s)
{
	ExternalServerNode *node_p = (ExternalServerNode *) manager_p -> sesm_servers.ll_head_p;

	while (node_p)
		{
			if (strcmp (node_p -> esn_server_p -> es_uri_s, server_uri_s) == 0)
				{
					return node_p;
				}

			node_p = (ExternalServerNode *) (node_p -> esn_node.ln_next_p);
		}

	return NULL;
}


static ExternalServer *GetExternalServerFromExternalServersManager (ServersManager *manager_p, const char * const server_uri_s, ExternalServerDeserialiser UNUSED_PARAM (deserialise_fn))
{
	SimpleExternalServersManager *external_servers_manager_p = (SimpleExternalServersManager *) manager_p;
	ExternalServerNode *node_p = GetExternalServerNode (external_servers_manager_p, server_uri_s);

	return (node_p ? node_p -> esn_server_p : NULL);
}


static ExternalServer *RemoveExternalServerFromExternalServersManager (ServersManager *manager_p, const char * const server_uri_s,  ExternalServerDeserialiser UNUSED_PARAM (deserialise_fn))
{
	SimpleExternalServersManager *external_servers_manager_p = (SimpleExternalServersManager *) manager_p;
	ExternalServer *server_p = NULL;
	ExternalServerNode *node_p = GetExternalServerNode (external_servers_manager_p, server_uri_s);

	if (node_p)
		{
			server_p = node_p -> esn_server_p;

			LinkedListRemove (& (external_servers_manager_p -> sesm_servers), (ListItem * const) node_p);

			node_p -> esn_server_p = NULL;
			FreeExternalServerNode ((ListItem * const) node_p);
		}

	return server_p;
}



static LinkedList *GetAllExternalServersFromExternalServersManager (ServersManager *manager_p, ExternalServerDeserialiser UNUSED_PARAM (deserialise_fn))
{
	SimpleExternalServersManager *external_servers_manager_p = (SimpleExternalServersManager *) manager_p;
	return & (external_servers_manager_p -> sesm_servers);
}


