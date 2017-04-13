//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_CONSTANTS_H
#define DUBBOC_CONSTANTS_H

#include <iostream>
#include <thread>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class Constants {
        public:

            static const string PROVIDER;

            static const string CONSUMER;

            static const string REGISTER;

            static const string UNREGISTER;

            static const string SUBSCRIBE;

            static const string UNSUBSCRIBE;

            static const string CATEGORY_KEY;

            static const string PROVIDERS_CATEGORY;

            static const string CONSUMERS_CATEGORY;

            static const string ROUTERS_CATEGORY;

            static const string CONFIGURATORS_CATEGORY;

            static const string DEFAULT_CATEGORY;

            static const string ENABLED_KEY;

            static const string DISABLED_KEY;

            static const string VALIDATION_KEY;

            static const string CACHE_KEY;

            static const string DYNAMIC_KEY;

            static const string DUBBOC_PROPERTIES_KEY;

            static const string DEFAULT_DUBBOC_PROPERTIES;

            static const string SENT_KEY;

            static const bool DEFAULT_SENT;

            static const string REGISTRY_PROTOCOL;

            static const string $INVOKE;

            static const string $ECHO;

            static const int DEFAULT_IO_THREADS;

            static const string DEFAULT_PROXY;

            static const int DEFAULT_PAYLOAD;                      // 8M

            static const string DEFAULT_CLUSTER;

            static const string DEFAULT_DIRECTORY;

            static const string DEFAULT_LOADBALANCE;

            static const string DEFAULT_PROTOCOL;

            static const string DEFAULT_EXCHANGER;

            static const string DEFAULT_TRANSPORTER;

            static const string DEFAULT_REMOTING_SERVER;

            static const string DEFAULT_REMOTING_CLIENT;

            static const string DEFAULT_REMOTING_CODEC;

            static const string DEFAULT_REMOTING_SERIALIZATION;

            static const string DEFAULT_HTTP_SERVER;

            static const string DEFAULT_HTTP_CLIENT;

            static const string DEFAULT_HTTP_SERIALIZATION;

            static const string DEFAULT_CHARSET;

            static const int DEFAULT_WEIGHT;

            static const int DEFAULT_FORKS;

            static const string DEFAULT_THREAD_NAME;

            static const int DEFAULT_CORE_THREADS;

            static const int DEFAULT_THREADS;

            static const bool DEFAULT_KEEP_ALIVE;

            static const int DEFAULT_QUEUES;

            static const int DEFAULT_ALIVE;

            static const int DEFAULT_CONNECTIONS;

            static const int DEFAULT_ACCEPTS;

            static const int DEFAULT_IDLE_TIMEOUT;

            static const int DEFAULT_HEARTBEAT;

            static const int DEFAULT_TIMEOUT;

            static const int DEFAULT_CONNECT_TIMEOUT;

            static const int DEFAULT_REGISTRY_CONNECT_TIMEOUT;

            static const int DEFAULT_RETRIES;

            // default buffer size is 8k.
            static const int DEFAULT_BUFFER_SIZE;

            static const int MAX_BUFFER_SIZE;

            static const int MIN_BUFFER_SIZE;

            static const string REMOVE_VALUE_PREFIX;

            static const string HIDE_KEY_PREFIX;

            static const string DEFAULT_KEY_PREFIX;

            static const string DEFAULT_KEY;

            static const string LOADBALANCE_KEY;

            // key for router type, for e.g., "script"/"file",  corresponding to ScriptRouterFactory.NAME, FileRouterFactory.NAME
            static const string ROUTER_KEY;

            static const string CLUSTER_KEY;

            static const string REGISTRY_KEY;

            static const string MONITOR_KEY;

            static const string SIDE_KEY;

            static const string PROVIDER_SIDE;

            static const string CONSUMER_SIDE;

            static const string DEFAULT_REGISTRY;

            static const string BACKUP_KEY;

            static const string DIRECTORY_KEY;

            static const string DEPRECATED_KEY;

            static const string ANYHOST_KEY;

            static const string ANYHOST_VALUE;

            static const string LOCALHOST_KEY;

            static const string LOCALHOST_VALUE;

            static const string APPLICATION_KEY;

            static const string LOCAL_KEY;

            static const string STUB_KEY;

            static const string MOCK_KEY;

            static const string PROTOCOL_KEY;

            static const string PROXY_KEY;

            static const string WEIGHT_KEY;

            static const string FORKS_KEY;

            static const string DEFAULT_THREADPOOL;

            static const string DEFAULT_CLIENT_THREADPOOL;

            static const string THREADPOOL_KEY;

            static const string THREAD_NAME_KEY;

            static const string IO_THREADS_KEY;

            static const string CORE_THREADS_KEY;

            static const string THREADS_KEY;

            static const string QUEUES_KEY;

            static const string ALIVE_KEY;

            static const string EXECUTES_KEY;

            static const string BUFFER_KEY;

            static const string PAYLOAD_KEY;

            static const string REFERENCE_FILTER_KEY;

            static const string INVOKER_LISTENER_KEY;

            static const string SERVICE_FILTER_KEY;

            static const string EXPORTER_LISTENER_KEY;

            static const string ACCESS_LOG_KEY;

            static const string ACTIVES_KEY;

            static const string CONNECTIONS_KEY;

            static const string ACCEPTS_KEY;

            static const string IDLE_TIMEOUT_KEY;

            static const string HEARTBEAT_KEY;

            static const string HEARTBEAT_TIMEOUT_KEY;

            static const string CONNECT_TIMEOUT_KEY;

            static const string TIMEOUT_KEY;

            static const string RETRIES_KEY;

            static const string PROMPT_KEY;

            static const string DEFAULT_PROMPT;

            static const string CODEC_KEY;

            static const string SERIALIZATION_KEY;

            // modified by lishen
            static const string EXTENSION_KEY;

            // modified by lishen
            static const string KEEP_ALIVE_KEY;

            // modified by lishen
            // TODO change to a better name
            static const string OPTIMIZER_KEY;

            static const string EXCHANGER_KEY;

            static const string TRANSPORTER_KEY;

            static const string SERVER_KEY;

            static const string CLIENT_KEY;

            static const string ID_KEY;

            static const string ASYNC_KEY;

            static const string RETURN_KEY;

            static const string TOKEN_KEY;

            static const string METHOD_KEY;

            static const string METHODS_KEY;

            static const string CHARSET_KEY;

            static const string RECONNECT_KEY;

            static const string SEND_RECONNECT_KEY;

            static const int DEFAULT_RECONNECT_PERIOD;

            static const string SHUTDOWN_TIMEOUT_KEY;

            static const int DEFAULT_SHUTDOWN_TIMEOUT;

            static const string PID_KEY;

            static const string TIMESTAMP_KEY;

            static const string WARMUP_KEY;

            static const int DEFAULT_WARMUP;

            static const string CHECK_KEY;

            static const string REGISTER_KEY;

            static const string SUBSCRIBE_KEY;

            static const string GROUP_KEY;

            static const string PATH_KEY;

            static const string INTERFACE_KEY;

            static const string GENERIC_KEY;

            static const string FILE_KEY;

            static const string WAIT_KEY;

            static const string CLASSIFIER_KEY;

            static const string VERSION_KEY;

            static const string REVISION_KEY;

            static const string DUBBOC_VERSION_KEY;

            static const string HESSIAN_VERSION_KEY;

            static const string DISPATCHER_KEY;

            static const string CHANNEL_HANDLER_KEY;

            static const string DEFAULT_CHANNEL_HANDLER;

            static const string ANY_VALUE ;

            static const string COMMA_SEPARATOR;

            static const string COMMA_SPLIT_PATTERN;

            const static string PATH_SEPARATOR;

            static const string REGISTRY_SEPARATOR;

            static const string REGISTRY_SPLIT_PATTERN;

            static const string SEMICOLON_SEPARATOR;

            static const string SEMICOLON_SPLIT_PATTERN;

            static const string CONNECT_QUEUE_CAPACITY;

            static const string CONNECT_QUEUE_WARNING_SIZE;

            static const int DEFAULT_CONNECT_QUEUE_WARNING_SIZE;

            static const string CHANNEL_ATTRIBUTE_READONLY_KEY;

            static const string CHANNEL_READONLYEVENT_SENT_KEY;

            static const string CHANNEL_SEND_READONLYEVENT_KEY;

            static const string COUNT_PROTOCOL;

            static const string TRACE_PROTOCOL;

            static const string EMPTY_PROTOCOL;

            static const string ADMIN_PROTOCOL;

            static const string PROVIDER_PROTOCOL;

            static const string CONSUMER_PROTOCOL;

            static const string ROUTE_PROTOCOL;

            static const string SCRIPT_PROTOCOL;

            static const string CONDITION_PROTOCOL;

            static const string MOCK_PROTOCOL;

            static const string RETURN_PREFIX;

            static const string THROW_PREFIX;

            static const string FAIL_PREFIX ;

            static const string FORCE_PREFIX;

            static const string FORCE_KEY;

            static const string MERGER_KEY;

            static const string OBJECT_MARK_KRY;

            /**
             * 集群时是否排除非available的invoker
             */
            static const string CLUSTER_AVAILABLE_CHECK_KEY;

            /**
             */
            static const bool DEFAULT_CLUSTER_AVAILABLE_CHECK;

            /**
             * 集群时是否启用sticky策略
             */
            static const string CLUSTER_STICKY_KEY;

            /**
             * sticky默认值.
             */
            static const bool DEFAULT_CLUSTER_STICKY;

            /**
             * 创建client时，是否先要建立连接。
             */
            static const string LAZY_CONNECT_KEY;

            /**
             * lazy连接的初始状态是连接状态还是非连接状态？
             */
            static const string LAZY_CONNECT_INITIAL_STATE_KEY;

            /**
             * lazy连接的初始状态默认是连接状态.
             */
            static const bool DEFAULT_LAZY_CONNECT_INITIAL_STATE;

            /**
             * 注册中心是否同步存储文件，默认异步
             */
            static const string REGISTRY_FILESAVE_SYNC_KEY;

            /**
             * 注册中心失败事件重试事件
             */
            static const string REGISTRY_RETRY_PERIOD_KEY;

            /**
             * 重试周期
             */
            static const int DEFAULT_REGISTRY_RETRY_PERIOD ;

            /**
             * 注册中心自动重连时间
             */
            static const string REGISTRY_RECONNECT_PERIOD_KEY ;

            static const int DEFAULT_REGISTRY_RECONNECT_PERIOD;

            static const string SESSION_TIMEOUT_KEY;

            static const int DEFAULT_SESSION_TIMEOUT;

            /**
             * 注册中心导出URL参数的KEY
             */
            static const string EXPORT_KEY;

            /**
             * 注册中心引用URL参数的KEY
             */
            static const string REFER_KEY;

            /**
             * callback inst id
             */
            static const string CALLBACK_SERVICE_KEY;

            /**
             * 每个客户端同一个接口 callback服务实例的限制
             */
            static const string CALLBACK_INSTANCES_LIMIT_KEY;

            /**
             * 每个客户端同一个接口 callback服务实例的限制
             */
            static const int DEFAULT_CALLBACK_INSTANCES;

            static const string CALLBACK_SERVICE_PROXY_KEY;

            static const string IS_CALLBACK_SERVICE;

            /**
             * channel中callback的invokers
             */
            static const string CHANNEL_CALLBACK_KEY;

            static const string SHUTDOWN_WAIT_KEY;

            static const string IS_SERVER_KEY;

            /**
             * 默认值毫秒，避免重新计算.
             */
            static const int DEFAULT_SERVER_SHUTDOWN_TIMEOUT;

            static const string ON_CONNECT_KEY;

            static const string ON_DISCONNECT_KEY;

            static const string ON_INVOKE_METHOD_KEY;

            static const string ON_RETURN_METHOD_KEY ;

            static const string ON_THROW_METHOD_KEY;

            static const string ON_INVOKE_INSTANCE_KEY;

            static const string ON_RETURN_INSTANCE_KEY;

            static const string ON_THROW_INSTANCE_KEY ;

            static const string OVERRIDE_PROTOCOL ;

            static const string PRIORITY_KEY;

            static const string RULE_KEY;

            static const string TYPE_KEY;

            static const string RUNTIME_KEY;

            // when ROUTER_KEY's value is set to ROUTER_TYPE_CLEAR, RegistryDirectory will clean all current routers
            static const string ROUTER_TYPE_CLEAR;

            static const string DEFAULT_SCRIPT_TYPE_KEY;

            static const string STUB_EVENT_KEY;

            static const bool DEFAULT_STUB_EVENT;

            static const string STUB_EVENT_METHODS_KEY;

            //invocation attachment属性中如果有此值，则选择mock invoker
            static const string INVOCATION_NEED_MOCK ;

            static const string LOCAL_PROTOCOL ;

            static const string AUTO_ATTACH_INVOCATIONID_KEY;

            static const string SCOPE_KEY;

            static const string SCOPE_LOCAL;

            static const string SCOPE_REMOTE;

            static const string SCOPE_NONE;

            static const string RELIABLE_PROTOCOL;

            static const string TPS_LIMIT_RATE_KEY;

            static const string TPS_LIMIT_INTERVAL_KEY;

            static const long DEFAULT_TPS_LIMIT_INTERVAL;

            static const string DECODE_IN_IO_THREAD_KEY;

            static const bool DEFAULT_DECODE_IN_IO_THREAD;

            static const string INPUT_KEY;

            static const string OUTPUT_KEY;

//         static const string EXECUTOR_SERVICE_COMPONENT_KEY      = ExecutorService.class.getName();

            static const string GENERIC_SERIALIZATION_NATIVE_JAVA;

            static const string GENERIC_SERIALIZATION_DEFAULT;

            static const string GENERIC_SERIALIZATION_BEAN;

            /*
             * private Constants(){ }
             */
        };
    }
}
#endif //DUBBOC_CONSTANTS_H
