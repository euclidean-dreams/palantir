#include <zmq.hpp>
#include <ImpresarioUtils.h>
#include "percipient/CosmographerPercipient.h"
#include "framework/Constants.h"
#include "Palantir.h"

namespace palantir {

int bootstrap(std::string configFilePath) {
    impresarioUtils::Bootstrapper bootstrapper(configFilePath, 1);
    Constants constants{};

    auto glimpsology = std::make_shared<impresarioUtils::Arbiter<const impresarioUtils::Parcel>>();
    auto cosmographerSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            bootstrapper.getZmqContext(),
            constants.percipiaEndpoint,
            zmq::socket_type::sub,
            false
    );
    cosmographerSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::glimpse);
    auto cosmographerPercipient = std::make_unique<CosmographerPercipient>(move(cosmographerSocket), glimpsology);
    auto cosmographerPercipientThread = impresarioUtils::Circlet::begin(move(cosmographerPercipient));

    auto palantirInstance = std::make_unique<Palantir>(move(glimpsology), constants);
    auto palantirThread = impresarioUtils::Circlet::beginTicking(move(palantirInstance));

    SDL_Event event;
    bool running = true;
    while (running) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            running = false;
    }

    return 0;
}

}

int main(int argc, char *argv[]) {
    std::string configFilePath;
    if (argc == 1) {
        configFilePath = "./palantir.yml";
    } else if (argc == 2) {
        configFilePath = argv[1];
    } else {
        return 1;
    }
    return palantir::bootstrap(configFilePath);
}
