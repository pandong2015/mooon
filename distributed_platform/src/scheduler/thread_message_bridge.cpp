/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: eyjian@qq.com or eyjian@gmail.com
 */
#include "thread_message_bridge.h"
SCHED_NAMESPACE_BEGIN

CThreadMessageBridge::CThreadMessageBridge(CKernelThread* kernel_thread)
 :IMessageBridge(kernel_thread)
{

}

bool CThreadMessageBridge::on_message(const TDistributedMessage* message)
{
	IDistributedObject* distributed_object = _distributed_object_table.get_object(message->session_id);
	if (distributed_object != NULL)
	{
		distributed_object->on_message(message);
	}

	return true;
}

SCHED_NAMESPACE_END
