#include <zmq.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <ImpresarioUtils.h>
#include "Constants.h"
#include "Palantir.h"

void initializeLogger() {
    spdlog::stdout_color_mt(LOGGER_NAME);
}

std::unique_ptr<std::thread> initializePalantir(zmq::context_t &context) {
    auto cosmographerSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            context,
            COSMOGRAPHER_ENDPOINT,
            zmq::socket_type::sub,
            false
    );
    cosmographerSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::luminary);
    auto palantirInstance = std::make_unique<palantir::Palantir>(move(cosmographerSocket));
    auto palantirThread = impresarioUtils::Circlet::begin(move(palantirInstance));
    return palantirThread;
}

int main() {
    initializeLogger();
    zmq::context_t context(1);
    auto palantirThread = initializePalantir(context);

    palantirThread->join();
    return 0;
}
