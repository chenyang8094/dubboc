//
// Created by 云海 on 2017/3/27.
//
#include "TransporterAdaptive.h"
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace DUBBOC::CONTAINER;

        shared_ptr<IServer>
        TransporterAdaptive::bind(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {

            if (url == nullptr) {
                throw std::invalid_argument("url == null");
            }

            std::string extName = url->getParameter("client", url->getParameter("transporter", std::string("wangle")));
            if (extName.empty()) {
                throw std::invalid_argument("url == null");
            }

            std::shared_ptr<ITransporter> extension = ExtensionLoader::getInstance()->LoadExtension<ITransporter>(
                    extName);
            return extension->bind(url, handler);
        }

        shared_ptr<IClient>
        TransporterAdaptive::connect(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {
            if (url == nullptr) {
                throw std::invalid_argument("url == null");
            }

            std::string extName = url->getParameter("server", url->getParameter("transporter", std::string("wangle")));
            if (extName.empty()) {
                throw std::invalid_argument("url == null");
            }

            std::shared_ptr<ITransporter> extension = ExtensionLoader::getInstance()->LoadExtension<ITransporter>(
                    extName);
            return extension->connect(url, handler);
        }

        EXTENSION_ADAPTIVE_REGISTER(ITransporter, TransporterAdaptive);
    }
}