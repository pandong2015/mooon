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
#include "agent_context.h"
MOOON_NAMESPACE_BEGIN

//////////////////////////////////////////////////////////////////////////
// ģ����ں���
static sys::CLock g_agent_lock;
static CAgentContext* g_agent_context = NULL;
IAgent* get_agent()
{
    if (NULL == g_agent_context)
    {
        sys::CLockHelper lh(g_agent_lock);
        if (NULL == g_agent_context)
        {
            g_agent_context = new CAgentContext();
            if (!g_agent_context->create())
            {
                delete g_agent_context;
                g_agent_context = NULL;
            }
        }
    }
    
    g_agent_context->inc_refcount();
    return g_agent_context;        
}

void release_agent()
{
    sys::CLockHelper lh(g_agent_lock);
    if (g_agent_context->dec_refcount())
    {
        g_agent_context->destroy();
        g_agent_context = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
// CAgentImpl

CAgentContext::CAgentContext()
    :_agent_thread(NULL)
    ,_resource_thread(NULL)
{
}

CAgentContext::~CAgentContext()
{

}

bool CAgentContext::create()
{
    // Agent�߳�
    _agent_thread = new CAgentThread;
    _agent_thread->inc_refcount();

    // Resouce�߳�
    _resource_thread = new CResourceThread;
    _resource_thread->inc_refcount();
}

void CAgentContext::destroy()
{
    // Agent�߳�
    _agent_thread->stop();
    _agent_thread->dec_refcount();

    // Resouce�߳�
    _resource_thread->stop();
    _resource_thread->dec_refcount();
}

void CAgentContext::report(const char* data, size_t data_size)
{    
    _agent_thread->report(data,data_size);
}

void CAgentContext::add_center(const net::ip_address_t& ip_address)
{
    _agent_thread->add_center(ip_address);
}

void CAgentContext::deregister_config_observer(const char* config_name)
{
    _agent_thread->deregister_config_observer(config_name);
}

bool CAgentContext::register_config_observer(const char* config_name, IConfigObserver* config_observer)
{
    return _agent_thread->register_config_observer(config_name, config_observer);
}

MOOON_NAMESPACE_END