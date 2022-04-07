#ifndef PALANTIR_CONSTANTS_H
#define PALANTIR_CONSTANTS_H

#include "Libs.h"

namespace palantir {

class Constants : public NonCopyable {
public:
    std::string cosmographerEndpoint = Config::getInstance().getString("cosmographerEndpoint");
    int glimpseWidth = Config::getInstance().getInt("glimpseWidth");
    int glimpseHeight = Config::getInstance().getInt("glimpseHeight");
    int pixelSize = Config::getInstance().getInt("pixelSize");
    bool fullscreen = Config::getInstance().getBool("fullscreen");
};

}

#endif //PALANTIR_CONSTANTS_H
