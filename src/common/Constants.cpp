//
// Created by 云海 on 2017/3/28.
//
#include "Constants.h"
namespace DUBBOC{
    namespace COMMON{
         const string Constants::PROVIDER = "provider";

         const string Constants::CONSUMER = "consumer";

         const string Constants::REGISTER = "register";

         const string Constants::UNREGISTER = "unregister";

         const string Constants::SUBSCRIBE = "subscribe";

         const string Constants::UNSUBSCRIBE = "unsubscribe";

         const string Constants::CATEGORY_KEY = "category";

         const string Constants::PROVIDERS_CATEGORY = "providers";

         const string Constants::CONSUMERS_CATEGORY = "consumers";

         const string Constants::ROUTERS_CATEGORY = "routers";

         const string Constants::CONFIGURATORS_CATEGORY = "configurators";

         const string Constants::DEFAULT_CATEGORY = PROVIDERS_CATEGORY;

         const string Constants::ENABLED_KEY = "enabled";

         const string Constants::DISABLED_KEY = "disabled";

         const string Constants::VALIDATION_KEY = "validation";

         const string Constants::CACHE_KEY = "cache";

         const string Constants::DYNAMIC_KEY = "dynamic";

         const string Constants::DUBBOC_PROPERTIES_KEY = "dubboc.properties.file";

         const string Constants::DEFAULT_DUBBOC_PROPERTIES = "dubboc.properties";

         const string Constants::SENT_KEY = "sent";

         const bool Constants::DEFAULT_SENT = false;

         const string Constants::REGISTRY_PROTOCOL = "registry";

         const string Constants::$INVOKE = "$invoke";

         const string Constants::$ECHO = "$echo";

         const int Constants::DEFAULT_IO_THREADS = std::thread::hardware_concurrency() + 1;

         const string Constants::DEFAULT_PROXY = "javassist";

         const int Constants::DEFAULT_PAYLOAD = 8 * 1024 * 1024;                      // 8M

         const string Constants::DEFAULT_CLUSTER = "failover";

         const string Constants::DEFAULT_DIRECTORY = "dubbo";

         const string Constants::DEFAULT_LOADBALANCE = "random";

         const string Constants::DEFAULT_PROTOCOL = "dubbo";

         const string Constants::DEFAULT_EXCHANGER = "header";

         const string Constants::DEFAULT_TRANSPORTER = "netty";

         const string Constants::DEFAULT_REMOTING_SERVER = "netty";

         const string Constants::DEFAULT_REMOTING_CLIENT = "netty";

         const string Constants::DEFAULT_REMOTING_CODEC = "dubbo";

         const string Constants::DEFAULT_REMOTING_SERIALIZATION = "hessian2";

         const string Constants::DEFAULT_HTTP_SERVER = "servlet";

         const string Constants::DEFAULT_HTTP_CLIENT = "jdk";

         const string Constants::DEFAULT_HTTP_SERIALIZATION = "json";

         const string Constants::DEFAULT_CHARSET = "UTF-8";

         const int Constants::DEFAULT_WEIGHT = 100;

         const int Constants::DEFAULT_FORKS = 2;

         const string Constants::DEFAULT_THREAD_NAME = "Dubboc";

         const int Constants::DEFAULT_CORE_THREADS = 0;

         const int Constants::DEFAULT_THREADS = 200;

         const bool Constants::DEFAULT_KEEP_ALIVE = true;

         const int Constants::DEFAULT_QUEUES = 0;

         const int Constants::DEFAULT_ALIVE = 60 * 1000;

         const int Constants::DEFAULT_CONNECTIONS = 0;

         const int Constants::DEFAULT_ACCEPTS = 0;

         const int Constants::DEFAULT_IDLE_TIMEOUT = 600 * 1000;

         const int Constants::DEFAULT_HEARTBEAT = 60 * 1000;

         const int Constants::DEFAULT_TIMEOUT = 1000;

         const int Constants::DEFAULT_CONNECT_TIMEOUT = 3000;

         const int Constants::DEFAULT_REGISTRY_CONNECT_TIMEOUT = 5000;

         const int Constants::DEFAULT_RETRIES = 2;

        // default buffer size is 8k.
         const int Constants::DEFAULT_BUFFER_SIZE = 8 * 1024;

         const int Constants::MAX_BUFFER_SIZE = 16 * 1024;

         const int Constants::MIN_BUFFER_SIZE = 1 * 1024;

         const string Constants::REMOVE_VALUE_PREFIX = "-";

         const string Constants::HIDE_KEY_PREFIX = ".";

         const string Constants::DEFAULT_KEY_PREFIX = "default.";

         const string Constants::DEFAULT_KEY = "default";

         const string Constants::LOADBALANCE_KEY = "loadbalance";

        // key for router type, for e.g., "script"/"file",  corresponding to ScriptRouterFactory.NAME, FileRouterFactory.NAME 
         const string Constants::ROUTER_KEY = "router";

         const string Constants::CLUSTER_KEY = "cluster";

         const string Constants::REGISTRY_KEY = "registry";

         const string Constants::MONITOR_KEY = "monitor";

         const string Constants::SIDE_KEY = "side";

         const string Constants::PROVIDER_SIDE = "provider";

         const string Constants::CONSUMER_SIDE = "consumer";

         const string Constants::DEFAULT_REGISTRY = "dubbo";

         const string Constants::BACKUP_KEY = "backup";

         const string Constants::DIRECTORY_KEY = "directory";

         const string Constants::DEPRECATED_KEY = "deprecated";

         const string Constants::ANYHOST_KEY = "anyhost";

         const string Constants::ANYHOST_VALUE = "0.0.0.0";

         const string Constants::LOCALHOST_KEY = "localhost";

         const string Constants::LOCALHOST_VALUE = "127.0.0.1";

         const string Constants::APPLICATION_KEY = "application";

         const string Constants::LOCAL_KEY = "local";

         const string Constants::STUB_KEY = "stub";

         const string Constants::MOCK_KEY = "mock";

         const string Constants::PROTOCOL_KEY = "protocol";

         const string Constants::PROXY_KEY = "proxy";

         const string Constants::WEIGHT_KEY = "weight";

         const string Constants::FORKS_KEY = "forks";

         const string Constants::DEFAULT_THREADPOOL = "limited";

         const string Constants::DEFAULT_CLIENT_THREADPOOL = "cached";

         const string Constants::THREADPOOL_KEY = "threadpool";

         const string Constants::THREAD_NAME_KEY = "threadname";

         const string Constants::IO_THREADS_KEY = "iothreads";

         const string Constants::CORE_THREADS_KEY = "corethreads";

         const string Constants::THREADS_KEY = "threads";

         const string Constants::QUEUES_KEY = "queues";

         const string Constants::ALIVE_KEY = "alive";

         const string Constants::EXECUTES_KEY = "executes";

         const string Constants::BUFFER_KEY = "buffer";

         const string Constants::PAYLOAD_KEY = "payload";

         const string Constants::REFERENCE_FILTER_KEY = "reference.filter";

         const string Constants::INVOKER_LISTENER_KEY = "invoker.listener";

         const string Constants::SERVICE_FILTER_KEY = "service.filter";

         const string Constants::EXPORTER_LISTENER_KEY = "exporter.listener";

         const string Constants::ACCESS_LOG_KEY = "accesslog";

         const string Constants::ACTIVES_KEY = "actives";

         const string Constants::CONNECTIONS_KEY = "connections";

         const string Constants::ACCEPTS_KEY = "accepts";

         const string Constants::IDLE_TIMEOUT_KEY = "idle.timeout";

         const string Constants::HEARTBEAT_KEY = "heartbeat";

         const string Constants::HEARTBEAT_TIMEOUT_KEY = "heartbeat.timeout";

         const string Constants::CONNECT_TIMEOUT_KEY = "connect.timeout";

         const string Constants::TIMEOUT_KEY = "timeout";

         const string Constants::RETRIES_KEY = "retries";

         const string Constants::PROMPT_KEY = "prompt";

         const string Constants::DEFAULT_PROMPT = "dubbo>";

         const string Constants::CODEC_KEY = "codec";

         const string Constants::SERIALIZATION_KEY = "serialization";

        // modified by lishen
         const string Constants::EXTENSION_KEY = "extension";

        // modified by lishen
         const string Constants::KEEP_ALIVE_KEY = "keepalive";

        // modified by lishen
        // TODO change to a better name
         const string Constants::OPTIMIZER_KEY = "optimizer";

         const string Constants::EXCHANGER_KEY = "exchanger";

         const string Constants::TRANSPORTER_KEY = "transporter";

         const string Constants::SERVER_KEY = "server";

         const string Constants::CLIENT_KEY = "client";

         const string Constants::ID_KEY = "id";

         const string Constants::ASYNC_KEY = "async";

         const string Constants::RETURN_KEY = "return";

         const string Constants::TOKEN_KEY = "token";

         const string Constants::METHOD_KEY = "method";

         const string Constants::METHODS_KEY = "methods";

         const string Constants::CHARSET_KEY = "charset";

         const string Constants::RECONNECT_KEY = "reconnect";

         const string Constants::SEND_RECONNECT_KEY = "send.reconnect";

         const int Constants::DEFAULT_RECONNECT_PERIOD = 2000;

         const string Constants::SHUTDOWN_TIMEOUT_KEY = "shutdown.timeout";

         const int Constants::DEFAULT_SHUTDOWN_TIMEOUT = 1000 * 60 * 15;

         const string Constants::PID_KEY = "pid";

         const string Constants::TIMESTAMP_KEY = "timestamp";

         const string Constants::WARMUP_KEY = "warmup";

         const int Constants::DEFAULT_WARMUP = 10 * 60 * 1000;

         const string Constants::CHECK_KEY = "check";

         const string Constants::REGISTER_KEY = "register";

         const string Constants::SUBSCRIBE_KEY = "subscribe";

         const string Constants::GROUP_KEY = "group";

         const string Constants::PATH_KEY = "path";

         const string Constants::INTERFACE_KEY = "interface";

         const string Constants::GENERIC_KEY = "generic";

         const string Constants::FILE_KEY = "file";

         const string Constants::WAIT_KEY = "wait";

         const string Constants::CLASSIFIER_KEY = "classifier";

         const string Constants::VERSION_KEY = "version";

         const string Constants::REVISION_KEY = "revision";

         const string Constants::DUBBO_VERSION_KEY = "dubbo";

         const string Constants::HESSIAN_VERSION_KEY = "hessian.version";

         const string Constants::DISPATCHER_KEY = "dispatcher";

         const string Constants::CHANNEL_HANDLER_KEY = "channel.handler";

         const string Constants::DEFAULT_CHANNEL_HANDLER = "default";

         const string Constants::ANY_VALUE = "*";

         const string Constants::COMMA_SEPARATOR = ",";

         const string Constants::COMMA_SPLIT_PATTERN = "\\s*[,]+\\s*";

        const  string Constants::PATH_SEPARATOR = "/";

         const string Constants::REGISTRY_SEPARATOR = "|";

         const string Constants::REGISTRY_SPLIT_PATTERN = "\\s*[|;]+\\s*";

         const string Constants::SEMICOLON_SEPARATOR = ";";

         const string Constants::SEMICOLON_SPLIT_PATTERN = "\\s*[;]+\\s*";

         const string Constants::CONNECT_QUEUE_CAPACITY = "connect.queue.capacity";

         const string Constants::CONNECT_QUEUE_WARNING_SIZE = "connect.queue.warning.size";

         const int Constants::DEFAULT_CONNECT_QUEUE_WARNING_SIZE = 1000;

         const string Constants::CHANNEL_ATTRIBUTE_READONLY_KEY = "channel.readonly";

         const string Constants::CHANNEL_READONLYEVENT_SENT_KEY = "channel.readonly.sent";

         const string Constants::CHANNEL_SEND_READONLYEVENT_KEY = "channel.readonly.send";

         const string Constants::COUNT_PROTOCOL = "count";

         const string Constants::TRACE_PROTOCOL = "trace";

         const string Constants::EMPTY_PROTOCOL = "empty";

         const string Constants::ADMIN_PROTOCOL = "admin";

         const string Constants::PROVIDER_PROTOCOL = "provider";

         const string Constants::CONSUMER_PROTOCOL = "consumer";

         const string Constants::ROUTE_PROTOCOL = "route";

         const string Constants::SCRIPT_PROTOCOL = "script";

         const string Constants::CONDITION_PROTOCOL = "condition";

         const string Constants::MOCK_PROTOCOL = "mock";

         const string Constants::RETURN_PREFIX = "return ";

         const string Constants::THROW_PREFIX = "throw";

         const string Constants::FAIL_PREFIX = "fail:";

         const string Constants::FORCE_PREFIX = "force:";

         const string Constants::FORCE_KEY = "force";

         const string Constants::MERGER_KEY = "merger";

        /**
         * 集群时是否排除非available的invoker
         */
         const string Constants::CLUSTER_AVAILABLE_CHECK_KEY = "cluster.availablecheck";

        /**
         */
         const bool Constants::DEFAULT_CLUSTER_AVAILABLE_CHECK = true;

        /**
         * 集群时是否启用sticky策略
         */
         const string Constants::CLUSTER_STICKY_KEY = "sticky";

        /**
         * sticky默认值.
         */
         const bool Constants::DEFAULT_CLUSTER_STICKY = false;

        /**
         * 创建client时，是否先要建立连接。
         */
         const string Constants::LAZY_CONNECT_KEY = "lazy";

        /**
         * lazy连接的初始状态是连接状态还是非连接状态？
         */
         const string Constants::LAZY_CONNECT_INITIAL_STATE_KEY = "connect.lazy.initial.state";

        /**
         * lazy连接的初始状态默认是连接状态.
         */
         const bool Constants::DEFAULT_LAZY_CONNECT_INITIAL_STATE = true;

        /**
         * 注册中心是否同步存储文件，默认异步
         */
         const string Constants::REGISTRY_FILESAVE_SYNC_KEY = "save.file";

        /**
         * 注册中心失败事件重试事件
         */
         const string Constants::REGISTRY_RETRY_PERIOD_KEY = "retry.period";

        /**
         * 重试周期
         */
         const int Constants::DEFAULT_REGISTRY_RETRY_PERIOD = 5 * 1000;

        /**
         * 注册中心自动重连时间
         */
         const string Constants::REGISTRY_RECONNECT_PERIOD_KEY = "reconnect.period";

         const int Constants::DEFAULT_REGISTRY_RECONNECT_PERIOD = 3 * 1000;

         const string Constants::SESSION_TIMEOUT_KEY = "session";

         const int Constants::DEFAULT_SESSION_TIMEOUT = 60 * 1000;

        /**
         * 注册中心导出URL参数的KEY
         */
         const string Constants::EXPORT_KEY = "export";

        /**
         * 注册中心引用URL参数的KEY
         */
         const string Constants::REFER_KEY = "refer";

        /**
         * callback inst id
         */
         const string Constants::CALLBACK_SERVICE_KEY = "callback.service.instid";

        /**
         * 每个客户端同一个接口 callback服务实例的限制
         */
         const string Constants::CALLBACK_INSTANCES_LIMIT_KEY = "callbacks";

        /**
         * 每个客户端同一个接口 callback服务实例的限制
         */
         const int Constants::DEFAULT_CALLBACK_INSTANCES = 1;

         const string Constants::CALLBACK_SERVICE_PROXY_KEY = "callback.service.proxy";

         const string Constants::IS_CALLBACK_SERVICE = "is_callback_service";

        /**
         * channel中callback的invokers
         */
         const string Constants::CHANNEL_CALLBACK_KEY = "channel.callback.invokers.key";

         const string Constants::SHUTDOWN_WAIT_KEY = "dubbo.service.shutdown.wait";

         const string Constants::IS_SERVER_KEY = "isserver";

        /**
         * 默认值毫秒，避免重新计算.
         */
         const int Constants::DEFAULT_SERVER_SHUTDOWN_TIMEOUT = 10000;

         const string Constants::ON_CONNECT_KEY = "onconnect";

         const string Constants::ON_DISCONNECT_KEY = "ondisconnect";

         const string Constants::ON_INVOKE_METHOD_KEY = "oninvoke.method";

         const string Constants::ON_RETURN_METHOD_KEY = "onreturn.method";

         const string Constants::ON_THROW_METHOD_KEY = "onthrow.method";

         const string Constants::ON_INVOKE_INSTANCE_KEY = "oninvoke.instance";

         const string Constants::ON_RETURN_INSTANCE_KEY = "onreturn.instance";

         const string Constants::ON_THROW_INSTANCE_KEY = "onthrow.instance";

         const string Constants::OVERRIDE_PROTOCOL = "override";

         const string Constants::PRIORITY_KEY = "priority";

         const string Constants::RULE_KEY = "rule";

         const string Constants::TYPE_KEY = "type";

         const string Constants::RUNTIME_KEY = "runtime";

        // when ROUTER_KEY's value is set to ROUTER_TYPE_CLEAR, RegistryDirectory will clean all current routers
         const string Constants::ROUTER_TYPE_CLEAR = "clean";

         const string Constants::DEFAULT_SCRIPT_TYPE_KEY = "javascript";

         const string Constants::STUB_EVENT_KEY = "dubbo.stub.event";

         const bool Constants::DEFAULT_STUB_EVENT = false;

         const string Constants::STUB_EVENT_METHODS_KEY = "dubbo.stub.event.methods";

        //invocation attachment属性中如果有此值，则选择mock invoker
         const string Constants::INVOCATION_NEED_MOCK = "invocation.need.mock";

         const string Constants::LOCAL_PROTOCOL = "injvm";

         const string Constants::AUTO_ATTACH_INVOCATIONID_KEY = "invocationid.autoattach";

         const string Constants::SCOPE_KEY = "scope";

         const string Constants::SCOPE_LOCAL = "local";

         const string Constants::SCOPE_REMOTE = "remote";

         const string Constants::SCOPE_NONE = "none";

         const string Constants::RELIABLE_PROTOCOL = "napoli";

         const string Constants::TPS_LIMIT_RATE_KEY = "tps";

         const string Constants::TPS_LIMIT_INTERVAL_KEY = "tps.interval";

         const long Constants::DEFAULT_TPS_LIMIT_INTERVAL = 60 * 1000;

         const string Constants::DECODE_IN_IO_THREAD_KEY = "decode.in.io";

         const bool Constants::DEFAULT_DECODE_IN_IO_THREAD = true;

         const string Constants::INPUT_KEY = "input";

         const string Constants::OUTPUT_KEY = "output";

//          const string EXECUTOR_SERVICE_COMPONENT_KEY      = ExecutorService.class.getName();

         const string Constants::GENERIC_SERIALIZATION_NATIVE_JAVA = "nativejava";

         const string Constants::GENERIC_SERIALIZATION_DEFAULT = "true";

         const string Constants::GENERIC_SERIALIZATION_BEAN = "bean";
    }
}