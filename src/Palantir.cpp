#include "Palantir.h"

namespace palantir {

Palantir::Palantir(std::shared_ptr<impresarioUtils::Arbiter<const impresarioUtils::Parcel>> glimpsology)
        : glimpsology{move(glimpsology)} {
    auto initializationResult = SDL_Init(SDL_INIT_VIDEO);
    if (initializationResult != 0) {
        throw SDLFailure{};
    }
    window = SDL_CreateWindow("palantir", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              0);
    Tchotchke::assertNotNull(window);

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    Tchotchke::assertNotNull(renderer);
}

Palantir::~Palantir() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Palantir::activate() {
    if (glimpsology->newDataAvailable()) {
        auto parcel = glimpsology->take();
        auto glimpse = impresarioUtils::Unwrap::Glimpse(*parcel);
        SDL_RenderClear(renderer);
        auto texture = createTexture(glimpse);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture *Palantir::createTexture(const ImpresarioSerialization::Glimpse *glimpse) {
    Uint32 redMask, greenMask, blueMask, alphaMask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    redMask = 0xff000000;
    greenMask = 0x00ff0000;
    blueMask = 0x0000ff00;
    alphaMask = 0x000000ff;
#else
    redMask = 0x000000ff;
    greenMask = 0x0000ff00;
    blueMask = 0x00ff0000;
    alphaMask = 0xff000000;
#endif
    auto surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, redMask, greenMask, blueMask,
                                        alphaMask);
    Tchotchke::assertNotNull(surface);

    auto colors = glimpse->colors();
    auto pixels = (Uint32 *) surface->pixels;
    for (int index = 0; index < colors->size(); index++) {
        auto glimpseColor = (*colors)[index];
        auto surfaceColor = SDL_MapRGBA(surface->format, glimpseColor->red(), glimpseColor->green(),
                                        glimpseColor->blue(), 255);
        auto glimpseX = index % GLIMPSE_WIDTH;
        auto glimpseY = (int) std::floor(index / GLIMPSE_WIDTH);
        auto surfaceLowX = glimpseX * PIXEL_SIZE;
        auto surfaceLowY = glimpseY * PIXEL_SIZE;
        auto surfaceHighX = surfaceLowX + PIXEL_SIZE - 1;
        auto surfaceHighY = surfaceLowY + PIXEL_SIZE - 1;
        for (int y = surfaceLowY; y <= surfaceHighY; y++) {
            for (int x = surfaceLowX; x <= surfaceHighX; x++) {
                auto pixelIndex = WINDOW_WIDTH * y + x;
                pixels[pixelIndex] = surfaceColor;
            }
        }
    }

    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    Tchotchke::assertNotNull(texture);
    SDL_FreeSurface(surface);

    return texture;
}

uint64_t Palantir::getTickInterval() {
    return 500;
}

bool Palantir::finished() {
    return false;
}

}
