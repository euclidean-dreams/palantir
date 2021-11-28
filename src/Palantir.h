#ifndef PALANTIR_PALANTIR_H
#define PALANTIR_PALANTIR_H

#include <SDL.h>
#include <ImpresarioUtils.h>
#include "gizmo/Tchotchke.h"
#include "Constants.h"

namespace palantir {

class Palantir : public impresarioUtils::Circulable {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *createTexture(const ImpresarioSerialization::Luminary *luminary);

public:
    explicit Palantir(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket);

    ~Palantir() override;

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //PALANTIR_PALANTIR_H
