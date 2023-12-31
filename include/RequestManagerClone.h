/* -------------------------------------------------------------------------- */
/* Copyright 2002-2020, OpenNebula Project, OpenNebula Systems                */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#ifndef REQUEST_MANAGER_CLONE_H
#define REQUEST_MANAGER_CLONE_H

#include "Request.h"
#include "RequestManagerVMTemplate.h"
#include "Nebula.h"

#include "DocumentPool.h"
#include "SecurityGroupPool.h"
#include "VNTemplatePool.h"

using namespace std;

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

class RequestManagerClone: public Request
{
protected:
    RequestManagerClone(const string& method_name, const string& help,
        const string& params = "A:sis"):
        Request(method_name,params,help){};

    ~RequestManagerClone(){};

    /* -------------------------------------------------------------------- */

    void request_execute(xmlrpc_c::paramList const& _paramList,
            RequestAttributes& att) override;

    /* -------------------------------------------------------------------- */
    /* Especialization Functions for specific Clone actions                 */
    /* -------------------------------------------------------------------- */

	/**
     *  Function to clone the object
     */
    virtual ErrorCode clone(int source_id, const string &name, int &new_id,
            bool recursive, const string& s_uattr, RequestAttributes& att);

	/**
     *  Function to clone the base template
     */
    virtual Template * clone_template(PoolObjectSQL* obj) = 0;

	/**
     *  Function to merge user/additional attributes in the cloned object
     */
    virtual ErrorCode merge(Template * tmpl, const string &str_uattrs,
            RequestAttributes& att)
    {
        return SUCCESS;
    }

	/**
     *  Function to allocated the new clone object
     */
    virtual int pool_allocate(int source_id, Template * tmpl, int& id,
            RequestAttributes& att) = 0;
};

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

class VMTemplateClone : public RequestManagerClone
{
public:
    VMTemplateClone():
        RequestManagerClone("one.template.clone",
                "Clone a virtual machine template", "A:sisb")
    {
        Nebula& nd  = Nebula::instance();
        pool        = nd.get_tpool();

        auth_object = PoolObjectSQL::TEMPLATE;
        auth_op     = AuthRequest::USE;
    };

    ~VMTemplateClone(){};

    ErrorCode request_execute(int source_id, const string &name, int &new_id,
            bool recursive, const string& s_uattrs, RequestAttributes& att)
    {
        return clone(source_id, name, new_id, recursive, s_uattrs, att);
    };

protected:

    ErrorCode clone(int source_id, const string &name, int &new_id,
            bool recursive, const string& s_a, RequestAttributes& att) override;

    Template * clone_template(PoolObjectSQL* obj) override
    {
        return static_cast<VMTemplate*>(obj)->clone_template();
    };

    int pool_allocate(int sid, Template * tmpl, int& id, RequestAttributes& att) override
    {
        VMTemplatePool * tpool     = static_cast<VMTemplatePool *>(pool);
        VirtualMachineTemplate * t = static_cast<VirtualMachineTemplate*>(tmpl);

        return tpool->allocate(att.uid, att.gid, att.uname, att.gname, att.umask,
                t, &id, att.resp_msg);
    };

    ErrorCode merge(Template * tmpl, const string &s_a, RequestAttributes& att) override
    {
        VMTemplateInstantiate vm_instantiate;

        return vm_instantiate.merge(tmpl, s_a, att);
    };

    static const std::vector<const char*> REMOVE_DISK_ATTRS;
};

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

class VNTemplateClone : public RequestManagerClone
{
public:
    VNTemplateClone():
        RequestManagerClone("one.vntemplate.clone",
                "Clone a virtual network template", "A:sis")
    {
        Nebula& nd  = Nebula::instance();
        pool        = nd.get_vntpool();

        auth_object = PoolObjectSQL::VNTEMPLATE;
        auth_op     = AuthRequest::USE;
    };

    ~VNTemplateClone(){};

    ErrorCode request_execute(int source_id, const string &name, int &new_id,
            const string& s_uattrs, RequestAttributes& att)
    {
        return clone(source_id, name, new_id, false, s_uattrs, att);
    };

protected:

    Template * clone_template(PoolObjectSQL* obj) override
    {
        return static_cast<VNTemplate*>(obj)->clone_template();
    };

    int pool_allocate(int sid, Template * tmpl, int& id, RequestAttributes& att) override
    {
        VNTemplatePool * tpool     = static_cast<VNTemplatePool *>(pool);
        VirtualNetworkTemplate * t = static_cast<VirtualNetworkTemplate*>(tmpl);

        return tpool->allocate(att.uid, att.gid, att.uname, att.gname, att.umask,
                t, &id, att.resp_msg);
    };

};

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

class DocumentClone : public RequestManagerClone
{
public:
    DocumentClone():
        RequestManagerClone("one.document.clone", "Clone existing document")
    {
        Nebula& nd  = Nebula::instance();
        pool        = nd.get_docpool();

        auth_object = PoolObjectSQL::DOCUMENT;
        auth_op     = AuthRequest::USE;
    };

    ~DocumentClone(){};

protected:

    Template * clone_template(PoolObjectSQL* obj) override
    {
        return static_cast<Document*>(obj)->clone_template();
    };

    int pool_allocate(int sid, Template * tmpl, int& id, RequestAttributes& att) override
    {
        DocumentPool * docpool = static_cast<DocumentPool *>(pool);
        Document * doc         = docpool->get_ro(sid);

        if ( doc == 0 )
        {
            return -1;
        }

        int dtype = doc->get_document_type();

        doc->unlock();

        return docpool->allocate(att.uid, att.gid, att.uname, att.gname,
            att.umask, dtype, tmpl, &id, att.resp_msg);
    };
};

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

class SecurityGroupClone : public RequestManagerClone
{
public:
    SecurityGroupClone():
        RequestManagerClone("one.secgroup.clone", "Clone a security group")
    {
        Nebula& nd  = Nebula::instance();
        pool        = nd.get_secgrouppool();

        auth_object = PoolObjectSQL::SECGROUP;
        auth_op     = AuthRequest::USE;
    };

    ~SecurityGroupClone(){};

protected:

    Template * clone_template(PoolObjectSQL* obj) override
    {
        return static_cast<SecurityGroup*>(obj)->clone_template();
    };

    int pool_allocate(int sid, Template * tmpl, int& id, RequestAttributes& att) override
    {
        SecurityGroupPool * sg = static_cast<SecurityGroupPool *>(pool);

        return sg->allocate(att.uid, att.gid, att.uname, att.gname, att.umask,
                tmpl, &id, att.resp_msg);
    };
};

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

#endif
