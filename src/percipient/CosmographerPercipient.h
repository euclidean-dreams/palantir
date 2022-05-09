#ifndef PALANTIR_COSMOGRAPHERPERCIPIENT_H
#define PALANTIR_COSMOGRAPHERPERCIPIENT_H

#include <ImpresarioUtils.h>

namespace palantir {

class CosmographerPercipient : public impresarioUtils::Circulable {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> socket;
    std::shared_ptr<impresarioUtils::Arbiter<const impresarioUtils::Parcel>> glimpsology;
    bool receivedFirstGlimpse = false;

public:
    CosmographerPercipient(
            std::unique_ptr<impresarioUtils::NetworkSocket> socket,
            std::shared_ptr<impresarioUtils::Arbiter<const impresarioUtils::Parcel>> glimpsology
    );

    void activate() override;

    bool finished() override;
};

}

#endif //PALANTIR_COSMOGRAPHERPERCIPIENT_H
