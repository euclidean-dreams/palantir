#include <zmq.hpp>
#include <ImpresarioUtils.h>
#include "percipient/CosmographerPercipient.h"
#include "Constants.h"
#include "Palantir.h"

namespace palantir {

int bootstrap() {
    std::string configFilePath = "./config.yml";
    impresarioUtils::Bootstrapper bootstrapper(configFilePath, 1);

    auto glimpsology = std::make_shared<impresarioUtils::Arbiter<const impresarioUtils::Parcel>>();
    auto cosmographerSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            bootstrapper.getZmqContext(),
            COSMOGRAPHER_ENDPOINT,
            zmq::socket_type::sub,
            false
    );
    cosmographerSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::glimpse);
    auto cosmographerPercipient = std::make_unique<CosmographerPercipient>(move(cosmographerSocket), glimpsology);
    auto cosmographerPercipientThread = impresarioUtils::Circlet::begin(move(cosmographerPercipient));

    auto palantirInstance = std::make_unique<Palantir>(move(glimpsology));
    auto palantirThread = impresarioUtils::Circlet::begin(move(palantirInstance));

    SDL_Event event;
    bool running = true;
    while (running) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            running = false;
    }

    palantirThread->join();
    cosmographerPercipientThread->join();
    return 0;
}

}

int main() {
    return palantir::bootstrap();
}
