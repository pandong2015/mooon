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
#ifndef MOOON_SCHEDULER_KERNEL_THREAD_H
#define MOOON_SCHEDULER_KERNEL_THREAD_H
#include <net/epoller.h>
#include <sys/pool_thread.h>
#include <scheduler/scheduler.h>
#include "message_bridge.h"
SCHED_NAMESPACE_BEGIN

class CKernelService;
class CKernelThread: public sys::CPoolThread
{
public:
	CKernelThread();
	~CKernelThread();

	void put_message(const TDistributedMessage* message);

private:
	virtual void run();
	virtual bool before_start();
	virtual void set_parameter(void* parameter);

private:
	CKernelService* _kernel_service;
	IMessageBridge* _message_bridge;
	net::CEpoller _epoller;
	typedef net::CEpollableQueue<util::CArrayQueue<const TDistributedMessage*> > CMessageQueue;
	CMessageQueue _request_queue;
	CMessageQueue _response_queue;
};

SCHED_NAMESPACE_END
#endif // MOOON_SCHEDULER_KERNEL_THREAD_H
