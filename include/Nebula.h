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

#ifndef NEBULA_H_
#define NEBULA_H_

#include "OpenNebulaTemplate.h"
#include "SystemDB.h"

#include "DefaultQuotas.h"
#include "UserPool.h"

class LogDB;
class FedLogDB;
class User;

class ClusterPool;
class DatastorePool;
class DocumentPool;
class GroupPool;
class HookPool;
class HostPool;
class ImagePool;
class MarketPlacePool;
class MarketPlaceAppPool;
class SecurityGroupPool;
class VdcPool;
class VMGroupPool;
class VMTemplatePool;
class VNTemplatePool;
class VirtualMachinePool;
class VirtualNetworkPool;
class VirtualRouterPool;
class ZonePool;

class AclManager;
class AuthManager;
class DispatchManager;
class FedReplicaManager;
class HookLog;
class HookManager;
class ImageManager;
class InformationManager;
class IPAMManager;
class LifeCycleManager;
class MarketPlaceManager;
class RaftManager;
class RequestManager;
class TransferManager;
class VirtualMachineManager;

/**
 *  This is the main class for the OpenNebula daemon oned. It stores references
 *  to the main modules and data pools. It also includes functions to bootstrap
 *  the system and start all its components.
 */
class Nebula
{
public:

    static Nebula& instance()
    {
        static Nebula nebulad;

        return nebulad;
    };

    // --------------------------------------------------------------
    // Pool Accessors
    // --------------------------------------------------------------
    LogDB * get_logdb()
    {
        return logdb;
    };

    VirtualMachinePool * get_vmpool()
    {
        return vmpool;
    };

    HostPool * get_hpool()
    {
        return hpool;
    };

    VirtualNetworkPool * get_vnpool()
    {
        return vnpool;
    };

    UserPool * get_upool()
    {
        return upool;
    };

    ImagePool * get_ipool()
    {
        return ipool;
    };

    GroupPool * get_gpool()
    {
        return gpool;
    };

    VMTemplatePool * get_tpool()
    {
        return tpool;
    };

    DatastorePool * get_dspool()
    {
        return dspool;
    };

    ClusterPool * get_clpool()
    {
        return clpool;
    };

    DocumentPool * get_docpool()
    {
        return docpool;
    };

    ZonePool * get_zonepool()
    {
        return zonepool;
    };

    SecurityGroupPool * get_secgrouppool()
    {
        return secgrouppool;
    };

    VdcPool * get_vdcpool()
    {
        return vdcpool;
    };

    VirtualRouterPool * get_vrouterpool()
    {
        return vrouterpool;
    };

    MarketPlacePool * get_marketpool()
    {
        return marketpool;
    };

    MarketPlaceAppPool * get_apppool()
    {
        return apppool;
    };

    VMGroupPool * get_vmgrouppool()
    {
        return vmgrouppool;
    };

    VNTemplatePool * get_vntpool()
    {
        return vntpool;
    }

    HookPool * get_hkpool()
    {
        return hkpool;
    }
    // --------------------------------------------------------------
    // Manager Accessors
    // --------------------------------------------------------------

    VirtualMachineManager * get_vmm()
    {
        return vmm;
    };

    LifeCycleManager * get_lcm()
    {
        return lcm;
    };

    InformationManager * get_im()
    {
        return im;
    };

    TransferManager * get_tm()
    {
        return tm;
    };

    DispatchManager * get_dm()
    {
        return dm;
    };

    HookManager * get_hm()
    {
        return hm;
    };

    HookLog * get_hl()
    {
        return hl;
    };

    AuthManager * get_authm()
    {
        return authm;
    };

    ImageManager * get_imagem()
    {
        return imagem;
    };

    AclManager * get_aclm()
    {
        return aclm;
    };

    MarketPlaceManager * get_marketm()
    {
        return marketm;
    };

    IPAMManager * get_ipamm()
    {
        return ipamm;
    };

    RaftManager * get_raftm()
    {
        return raftm;
    };

    FedReplicaManager * get_frm()
    {
        return frm;
    };

    RequestManager * get_rm()
    {
        return rm;
    };

    // --------------------------------------------------------------
    // Environment & Configuration
    // --------------------------------------------------------------

    /**
     *  Returns the value of LOG->DEBUG_LEVEL in oned.conf file
     *      @return the debug level, to instantiate Log'ers
     */
    Log::MessageType get_debug_level() const;

    /**
     *  Returns the value of LOG->SYSTEM in oned.conf file
     *      @return the logging system CERR, FILE_TS or SYSLOG
     */
    NebulaLog::LogType get_log_system() const;

    /**
     *  Returns the value of ONE_LOCATION env variable. When this variable is
     *  not defined the nebula location is "/".
     *      @return the nebula location.
     */
    const string& get_nebula_location()
    {
        return nebula_location;
    };

    /**
     *  Returns the path where mad executables are stored, if ONE_LOCATION is
     *  defined this path points to $ONE_LOCATION/bin, otherwise it is
     *  /usr/lib/one/mads.
     *      @return the mad execs location.
     */
    const string& get_mad_location()
    {
        return mad_location;
    };

    /**
     *  Returns the path where defaults for mads are stored, if ONE_LOCATION is
     *  defined this path points to $ONE_LOCATION/etc, otherwise it is /etc/one
     *      @return the mad defaults location.
     */
    const string& get_defaults_location()
    {
        return etc_location;
    };

    /**
     *  Returns the path where logs (oned.log, schedd.log,...) are generated
     *  if ONE_LOCATION is defined this path points to $ONE_LOCATION/var,
     *  otherwise it is /var/log/one.
     *      @return the log location.
     */
    const string& get_log_location()
    {
        return log_location;
    };

    /**
     *  Returns the default var location. When ONE_LOCATION is defined this path
     *  points to $ONE_LOCATION/var, otherwise it is /var/lib/one.
     *      @return the log location.
     */
    const string& get_var_location()
    {
        return var_location;
    };

    /**
     *  Returns the default share location. When ONE_LOCATION is defined this path
     *  points to $ONE_LOCATION/share, otherwise it is /usr/share/one.
     *      @return the log location.
     */
    const string& get_share_location()
    {
        return share_location;
    };

    /**
     *
     *
     */
    void get_ds_location(string& dsloc);

    /**
     *  Returns the default vms location. When ONE_LOCATION is defined this path
     *  points to $ONE_LOCATION/var/vms, otherwise it is /var/lib/one/vms. This
     *  location stores vm related files: deployment, transfer, context, and
     *  logs (in self-contained mode only)
     *      @return the vms location.
     */
    const string& get_vms_location()
    {
        return vms_location;
    };

    /**
     *  Returns the path of the log file for a VM, depending where OpenNebula is
     *  installed,
     *     $ONE_LOCATION/var/$VM_ID/vm.log
     *  or
     *     /var/log/one/$VM_ID.log
     *  @return the log location for the VM.
     */
    string get_vm_log_filename(int oid);

    /**
     *  Returns the name of the host running oned
     *    @return the name
     */
    const string& get_nebula_hostname()
    {
        return hostname;
    };

    /**
     *  Returns the version of oned
     *    @return the version
     */
    static string version()
    {
       ostringstream os;
       os << "OpenNebula " << code_version();
       os << " (" << GITVERSION << ")";

       return os.str();
    };

    /**
     *  Returns the version of oned
     * @return
     */
    static string code_version()
    {
        return "5.12.0.4"; // bump version
    }

    /**
     * Version needed for the DB, shared tables
     * @return
     */
    static string shared_db_version()
    {
        return "5.12.0";
    }

    /**
     * Version needed for the DB, local tables
     * @return
     */
    static string local_db_version()
    {
        return "5.12.0";
    }

    /**
     *  Starts all the modules and services for OpenNebula
     */
    void start(bool bootstrap_only=false);

    /**
     *  Initialize the database
     */
    void bootstrap_db()
    {
        start(true);
    }

    // --------------------------------------------------------------
    // Federation
    // --------------------------------------------------------------

    bool is_federation_enabled()
    {
        return federation_enabled;
    };

    bool is_federation_master()
    {
        return federation_master;

    };

    bool is_federation_slave()
    {
        return federation_enabled && !federation_master;
    };

    bool is_cache()
    {
        return cache;
    };

    int get_zone_id()
    {
        return zone_id;
    };

    int get_server_id()
    {
        return server_id;
    };

    const string& get_master_oned()
    {
        return master_oned;
    };

    // -----------------------------------------------------------------------
    // Configuration attributes (read from oned.conf)
    // -----------------------------------------------------------------------

    /**
     *  Gets a configuration attribute for oned
     *    @param name of the attribute
     *    @param value of the attribute
     */
    template<typename T>
    void get_configuration_attribute(const string& name, T& value) const
    {
        nebula_configuration->get(name, value);
    };

    /**
     *  Gets a user-configurable attribute for oned. Users (and groups) may
     *  store oned attributes in the "OPENNEBULA" vector. This function gets
     *  the value querying first the user, then the group and finally oned.conf
     *    @param uid of the user, if -1 the user template is not considered
     *    @param gid of the group
     *    @param name of the attribute
     *    @param value of the attribute
     *
     *    @return 0 on success -1 otherwise
     */
    template<typename T>
    int get_configuration_attribute(int uid, int gid, const std::string& name,
            T& value) const
    {
        if ( uid != -1 )
        {
            User * user = upool->get_ro(uid);

            if ( user == 0 )
            {
                return -1;
            }

            const VectorAttribute * uconf;

            uconf = user->get_template_attribute("OPENNEBULA");

            if ( uconf != 0 )
            {
                if ( uconf->vector_value(name, value) == 0 )
                {
                    user->unlock();
                    return 0;
                }
            }

            user->unlock();
        }

        Group * group = gpool->get_ro(gid);

        if ( group == 0 )
        {
            return -1;
        }

        const VectorAttribute * gconf;

        gconf = group->get_template_attribute("OPENNEBULA");

        if ( gconf != 0 )
        {
            if ( gconf->vector_value(name, value) == 0 )
            {
                group->unlock();
                return 0;
            }
        }

        group->unlock();

        nebula_configuration->get(name, value);

        return 0;
    }

    /**
     *  Gets a DS configuration attribute
     */
    int get_ds_conf_attribute(const std::string& ds_name,
        const VectorAttribute* &value) const
    {
        return get_conf_attribute("DS_MAD_CONF", ds_name, value);
    };

    /**
     * Gets a VN configuration attribute
     */
    int get_vn_conf_attribute(const std::string& vn_name,
        const VectorAttribute* &value) const
    {
        return get_conf_attribute("VN_MAD_CONF", vn_name, value);
    }

    /**
     *  Gets a TM configuration attribute
     */
    int get_tm_conf_attribute(const string& tm_name,
        const VectorAttribute* &value) const
    {
        return get_conf_attribute("TM_MAD_CONF", tm_name, value);
    };

    /**
     *  Gets a Market configuration attribute
     */
    int get_market_conf_attribute( const string& mk_name,
        const VectorAttribute* &value) const
    {
        return get_conf_attribute("MARKET_MAD_CONF", mk_name, value);
    };

    /**
     *  Gets an Auth driver configuration attribute
     */
    template<typename T>
    int get_auth_conf_attribute(const string& driver, const string& attribute,
        T& value) const
    {
        return get_conf_attribute("AUTH_MAD_CONF", driver, attribute, value);
    };

    /**
     *  Return the Authorization operation for a VM action
     *
     */
    AuthRequest::Operation get_vm_auth_op(VMActions::Action action)
    {
        return nebula_configuration->get_vm_auth_op(action);
    }

    /**
     *  Gets an XML document with all of the configuration attributes
     *    @return the XML
     */
    string get_configuration_xml() const
    {
        string xml;
        return nebula_configuration->to_xml(xml);
    };

    /**
     *  Gets the database backend type
     *    @return database backend type
     */
    string get_db_backend() const
    {
        return db_backend_type;
    }

    // -----------------------------------------------------------------------
    // Default Quotas
    // -----------------------------------------------------------------------

    /**
     *  Get the default quotas for OpenNebula users
     *    @return the default quotas
     */
    const DefaultQuotas& get_default_user_quota()
    {
        return default_user_quota;
    };

    /**
     *  Set the default quotas for OpenNebula users
     *    @param tmpl template with the default quotas
     *    @param error describes the error if any
     *
     *    @return 0 if success
     */
    int set_default_user_quota(Template *tmpl, string& error)
    {
        int rc = default_user_quota.set(tmpl, error);

        if ( rc == 0 )
        {
            rc = default_user_quota.update();
        }

        return rc;
    };

    /**
     *  Get the default quotas for OpenNebula for groups
     *    @return the default quotas
     */
    const DefaultQuotas& get_default_group_quota()
    {
        return default_group_quota;
    };

    /**
     *  Set the default quotas for OpenNebula groups
     *    @param tmpl template with the default quotas
     *    @param error describes the error if any
     *
     *    @return 0 if success
     */
    int set_default_group_quota(Template *tmpl, string& error)
    {
        int rc = default_group_quota.set(tmpl, error);

        if ( rc == 0 )
        {
            rc = default_group_quota.update();
        }

        return rc;
    };

    // -----------------------------------------------------------------------
    // System attributes
    // -----------------------------------------------------------------------
    /**
     *  Reads a System attribute from the DB
     *    @param attr_name name of the attribute
     *    @param cb Callback that will receive the attribute in XML
     *    @return 0 on success
     */
    int select_sys_attribute(const string& attr_name, string& attr_xml)
    {
        return system_db->select_sys_attribute(attr_name, attr_xml);
    };

    /**
     *  Writes a system attribute in the database.
     *    @param db pointer to the db
     *    @return 0 on success
     */
    int insert_sys_attribute(
        const string& attr_name,
        const string& xml_attr,
        string&       error_str)
    {
        return system_db->insert_sys_attribute(attr_name, xml_attr, error_str);
    };

    /**
     *  Updates the system attribute in the database.
     *    @param db pointer to the db
     *    @return 0 on success
     */
    int update_sys_attribute(
        const string& attr_name,
        const string& xml_attr,
        string&       error_str)
    {
        return system_db->update_sys_attribute(attr_name, xml_attr, error_str);
    };

private:

    // -----------------------------------------------------------------------
    //Constructors and = are private to only access the class through instance
    // -----------------------------------------------------------------------

    Nebula():nebula_configuration(0),
        default_user_quota( "DEFAULT_USER_QUOTAS",
                            "/DEFAULT_USER_QUOTAS/DATASTORE_QUOTA",
                            "/DEFAULT_USER_QUOTAS/NETWORK_QUOTA",
                            "/DEFAULT_USER_QUOTAS/IMAGE_QUOTA",
                            "/DEFAULT_USER_QUOTAS/VM_QUOTA"),
        default_group_quota("DEFAULT_GROUP_QUOTAS",
                            "/DEFAULT_GROUP_QUOTAS/DATASTORE_QUOTA",
                            "/DEFAULT_GROUP_QUOTAS/NETWORK_QUOTA",
                            "/DEFAULT_GROUP_QUOTAS/IMAGE_QUOTA",
                            "/DEFAULT_GROUP_QUOTAS/VM_QUOTA"),
        system_db(0), db_backend_type("sqlite"), logdb(0), fed_logdb(0),
        vmpool(0), hpool(0), vnpool(0), upool(0), ipool(0), gpool(0), tpool(0),
        dspool(0), clpool(0), docpool(0), zonepool(0), secgrouppool(0),
        vdcpool(0), vrouterpool(0), marketpool(0), apppool(0), vmgrouppool(0),
        vntpool(0), hkpool(0), lcm(0), vmm(0), im(0), tm(0), dm(0), rm(0), hm(0),
        hl(0), authm(0), aclm(0), imagem(0), marketm(0), ipamm(0), raftm(0), frm(0)
    {
        const char * nl = getenv("ONE_LOCATION");

        if (nl == 0) //OpenNebula installed under root directory
        {
            nebula_location = "/";

            mad_location     = "/usr/lib/one/mads/";
            etc_location     = "/etc/one/";
            log_location     = "/var/log/one/";
            var_location     = "/var/lib/one/";
            remotes_location = "/var/lib/one/remotes/";
            vms_location     = "/var/lib/one/vms/";
            share_location   = "/usr/share/one";
        }
        else
        {
            nebula_location = nl;

            if ( nebula_location.at(nebula_location.size()-1) != '/' )
            {
                nebula_location += "/";
            }

            mad_location     = nebula_location + "lib/mads/";
            etc_location     = nebula_location + "etc/";
            log_location     = nebula_location + "var/";
            var_location     = nebula_location + "var/";
            remotes_location = nebula_location + "var/remotes/";
            vms_location     = nebula_location + "var/vms/";
            share_location   = nebula_location + "share/";
        }
    };

    ~Nebula();

    Nebula& operator=(Nebula const&){return *this;};

    // ---------------------------------------------------------------
    // Environment variables
    // ---------------------------------------------------------------

    string  nebula_location;

    string  mad_location;
    string  etc_location;
    string  log_location;
    string  var_location;
    string  remotes_location;
    string  vms_location;
    string  share_location;

    string  hostname;

    // ---------------------------------------------------------------
    // Configuration
    // ---------------------------------------------------------------

    OpenNebulaTemplate * nebula_configuration;

    // ---------------------------------------------------------------
    // Federation - HA
    // ---------------------------------------------------------------

    bool    federation_enabled;
    bool    federation_master;
    bool    cache;
    int     zone_id;
    int     server_id;
    string  master_oned;

    // ---------------------------------------------------------------
    // Default quotas
    // ---------------------------------------------------------------

    DefaultQuotas default_user_quota;
    DefaultQuotas default_group_quota;

    // ---------------------------------------------------------------
    // The system database
    // ---------------------------------------------------------------

    SystemDB * system_db;
    string     db_backend_type;

    // ---------------------------------------------------------------
    // Nebula Pools
    // ---------------------------------------------------------------

    LogDB              * logdb;
    FedLogDB           * fed_logdb;
    VirtualMachinePool * vmpool;
    HostPool           * hpool;
    VirtualNetworkPool * vnpool;
    UserPool           * upool;
    ImagePool          * ipool;
    GroupPool          * gpool;
    VMTemplatePool     * tpool;
    DatastorePool      * dspool;
    ClusterPool        * clpool;
    DocumentPool       * docpool;
    ZonePool           * zonepool;
    SecurityGroupPool  * secgrouppool;
    VdcPool            * vdcpool;
    VirtualRouterPool  * vrouterpool;
    MarketPlacePool    * marketpool;
    MarketPlaceAppPool * apppool;
    VMGroupPool        * vmgrouppool;
    VNTemplatePool     * vntpool;
    HookPool           * hkpool;
    // ---------------------------------------------------------------
    // Nebula Managers
    // ---------------------------------------------------------------

    LifeCycleManager *      lcm;
    VirtualMachineManager * vmm;
    InformationManager *    im;
    TransferManager *       tm;
    DispatchManager *       dm;
    RequestManager *        rm;
    HookManager *           hm;
    HookLog *               hl;
    AuthManager *           authm;
    AclManager *            aclm;
    ImageManager *          imagem;
    MarketPlaceManager *    marketm;
    IPAMManager *           ipamm;
    RaftManager *           raftm;
    FedReplicaManager *     frm;

    // ---------------------------------------------------------------
    // Implementation functions
    // ---------------------------------------------------------------

    friend void nebula_signal_handler (int sig);

    // ---------------------------------------------------------------
    // Helper functions
    // ---------------------------------------------------------------

    /**
     *  Gets a Generic configuration attribute
     *  @param key String that identifies the configuration parameter group name
     *  @param name Name of the specific configuration parameter
     *  @param value Value of the specific configuration parameter
     *  @return a reference to the generated string
     */
    int get_conf_attribute(
        const std::string& key,
        const std::string& name,
        const VectorAttribute* &value) const;

    /**
     *  Gets a Generic configuration attribute
     *  @param key String that identifies the configuration parameter group name
     *  @param name Name of the specific configuration parameter
     *  @param value Value of the specific configuration parameter
     *  @return a reference to the generated string
     */
    template<typename T>
    int get_conf_attribute(
        const std::string& key,
        const std::string& name,
        const std::string& vname,
        T& value) const
    {
        const VectorAttribute* vattr;

        if ( get_conf_attribute(key, name, vattr) != 0 )
        {
            return -1;
        }

        return vattr->vector_value(vname, value);
    }
};

#endif /*NEBULA_H_*/
