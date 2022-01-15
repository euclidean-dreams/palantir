#ifndef PALANTIR_PALANTIR_H
#define PALANTIR_PALANTIR_H

#include <SDL.h>
#include <ImpresarioUtils.h>
#include "gizmo/Tchotchke.h"
#include "Constants.h"

#define WINDOW_WIDTH GLIMPSE_WIDTH * PIXEL_SIZE
#define WINDOW_HEIGHT GLIMPSE_HEIGHT * PIXEL_SIZE

namespace palantir {

class Palantir : public impresarioUtils::TickingCirculable {
private:
    std::shared_ptr<impresarioUtils::Arbiter<const impresarioUtils::Parcel>> glimpsology;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *createTexture(const ImpresarioSerialization::Glimpse *glimpse);

public:
    explicit Palantir(std::shared_ptr<impresarioUtils::Arbiter<const impresarioUtils::Parcel>> glimpsology);

    ~Palantir() override;

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //PALANTIR_PALANTIR_H
