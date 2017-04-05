//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_MONITORSERVICE_H
#define DUBBOC_MONITORSERVICE_H

#include <string>
#include <list>
#include <memory>
#include <common/Constants.h>
#include <common/URL.h>

namespace DUBBOC {
    namespace MONITOR {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class IMonitorService {
        public:
            IMonitorService() = default;

            virtual ~IMonitorService() {}

        public:

            string APPLICATION = "application";

            string INTERFACE = "interface";

            string METHOD = "method";

            string GROUP = "group";

            string VERSION = "version";

            string CONSUMER = "consumer";

            string PROVIDER = "provider";

            string TIMESTAMP = "timestamp";

            string SUCCESS = "success";

            string FAILURE = "failure";

            string INPUT = Constants::INPUT_KEY;

            string OUTPUT = Constants::OUTPUT_KEY;

            string ELAPSED = "elapsed";

            string CONCURRENT = "concurrent";

            string MAX_INPUT = "max.input";

            string MAX_OUTPUT = "max.output";

            string MAX_ELAPSED = "max.elapsed";

            string MAX_CONCURRENT = "max.concurrent";

            /**
             * 监控数据采集.
             * 1. 支持调用次数统计：count://host/interface?application=foo&method=foo&provider=10.20.153.11:20880&success=12&failure=2&elapsed=135423423
             * 1.1 host,application,interface,group,version,method 记录监控来源主机，应用，接口，方法信息。
             * 1.2 如果是消费者发送的数据，加上provider地址参数，反之，加上来源consumer地址参数。
             * 1.3 success,faulure,elapsed 记录距上次采集，调用的成功次数，失败次数，成功调用总耗时，平均时间将用总耗时除以成功次数。
             *
             * @param statistics
             */
            virtual void collect(shared_ptr<URL> statistics) = 0;

            /**
             * 监控数据查询. 
             * 1. 支持按天查询：count://host/interface?application=foo&method=foo&side=provider&view=chart&date=2012-07-03
             * 1.1 host,application,interface,group,version,method 查询主机，应用，接口，方法的匹配条件，缺失的条件的表示全部，host用0.0.0.0表示全部。
             * 1.2 side=consumer,provider 查询由调用的哪一端采集的数据，缺省为都查询。
             * 1.3 缺省为view=summary，返回全天汇总信息，支持view=chart表示返回全天趋势图表图片的URL地址，可以进接嵌入其它系统的页面上展示。
             * 1.4 date=2012-07-03 指定查询数据的日期，缺省为当天。
             *
             * @param query
             * @return statistics
             */
            virtual list<shared_ptr<URL>> lookup(shared_ptr<URL> query) = 0;

        };
    }
}
#endif //DUBBOC_MONITORSERVICE_H
