#ifndef PALANTIR_PALANTIR_H
#define PALANTIR_PALANTIR_H

#include <SDL.h>
#include "Default.h"
#include "gizmo/Tchotchke.h"

namespace palantir {

class Palantir : public TickingCirculable {
private:
    std::shared_ptr<Arbiter<const Parcel>> glimpsology;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Constants &constants;
    int windowWidth;
    int windowHeight;

    SDL_Texture *createTexture(const ImpresarioSerialization::Glimpse *glimpse);

public:
    explicit Palantir(
            std::shared_ptr<Arbiter<const Parcel>> glimpsology,
            Constants &constants
    );

    ~Palantir() override;

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //PALANTIR_PALANTIR_H
