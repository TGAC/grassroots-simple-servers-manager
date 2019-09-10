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

/**
 * @file
 * @brief
 */
/*
 * apr_jobs_manager.h
 *
 *  Created on: 19 May 2015
 *      Author: tyrrells
 */

#ifndef SIMPLE_EXTERNAL_SERVERS_MANAGER_H_
#define SIMPLE_EXTERNAL_SERVERS_MANAGER_H_


#include "simple_external_servers_manager_library.h"
#include "servers_manager.h"


typedef struct SimpleExternalServersManager
{
	ServersManager sesm_base_manager;
	LinkedList sesm_servers;
} SimpleExternalServersManager;



#ifdef __cplusplus
extern "C"
{
#endif


/**
 * The callback function for allocating a SimpleExternalServersManager.
 *
 * @return The newly-allocated SimpleExternalServersManager
 * or <code>NULL</code> upon error.
 * @memberof SimpleExternalServersManager
 */
SIMPLE_EXTERNAL_SERVERS_MANAGER_API ServersManager *GetCustomServersManager (void);


/**
 * The callback function for freeing the SimpleExternalServersManager.
 *
 * This will call FreeSimpleExternalServersManager().
 * @param manager_p The SimpleExternalServersManager to free.
 * @memberof SimpleExternalServersManager
 */
SIMPLE_EXTERNAL_SERVERS_MANAGER_API void ReleaseServersManager (ServersManager *manager_p);


/**
 * @brief Get the ServersManager to use in the Grassroots module.
 *
 * @memberof SimpleExternalServersManager
 * @return A newly-allocated SimpleExternalServersManager or <code>NULL</code> upon error.
 */
SIMPLE_EXTERNAL_SERVERS_MANAGER_LOCAL ServersManager *AllocateSimpleExternalServersManager (void);


/**
 * @brief Free a SimpleExternalServersManager.
 *
 * @param manager_p The SimpleExternalServersManager to free.
 * @return <code>true</code> if the SimpleExternalServersManager was freed successfully,
 * <code>false</code> otherwise
 * @memberof SimpleExternalServersManager
 */
SIMPLE_EXTERNAL_SERVERS_MANAGER_LOCAL void FreeSimpleExternalServersManager (ServersManager *manager_p);


#ifdef __cplusplus
}
#endif




#endif /* SERVERS_SIMPLE_SERVERS_MANAGER_INCLUDE_SIMPLE_EXTERNAL_SERVERS_MANAGER_H_ */
