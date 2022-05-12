#ifndef PALANTIR_CONSTANTS_H
#define PALANTIR_CONSTANTS_H

#include "Libs.h"

namespace palantir {

class Constants : public NonCopyable {
public:
    std::string percipiaEndpoint = Config::getInstance().getString("percipiaEndpoint");
    int percipiaWidth = Config::getInstance().getInt("percipiaWidth");
    int percipiaHeight = Config::getInstance().getInt("percipiaHeight");
    int pixelSize = Config::getInstance().getInt("pixelSize");
    bool fullscreen = Config::getInstance().getBool("fullscreen");
};

}

#endif //PALANTIR_CONSTANTS_H
