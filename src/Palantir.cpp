#include "Palantir.h"

namespace palantir {

Palantir::Palantir(std::unique_ptr<impresarioUtils::NetworkSocket> cosmographerSocket)
        : cosmographerSocket{move(cosmographerSocket)} {
    auto initializationResult = SDL_Init(SDL_INIT_VIDEO);
    if (initializationResult != 0) {
        throw SDLFailure{};
    }
    window = SDL_CreateWindow("palantir", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              0);
    Tchotchke::assertNotNull(window);

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    Tchotchke::assertNotNull(renderer);
}

Palantir::~Palantir() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Palantir::activate() {
    auto serializedData = cosmographerSocket->receiveSerializedData();
    auto luminary = ImpresarioSerialization::GetLuminary(serializedData->getBuffer());
    SDL_RenderClear(renderer);
    auto texture = createTexture(luminary);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

SDL_Texture *Palantir::createTexture(const ImpresarioSerialization::Luminary *luminary) {
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

    auto glimpse = luminary->glimpse();
    auto pixels = (Uint32 *) surface->pixels;
    for (int luminaryIndex = 0; luminaryIndex < glimpse->size(); luminaryIndex++) {
        auto glimpseColor = (*glimpse)[luminaryIndex];
        auto surfaceColor = SDL_MapRGBA(surface->format, glimpseColor->red(), glimpseColor->green(),
                                        glimpseColor->blue(), 255);
        auto luminaryX = luminaryIndex % LUMINARY_WIDTH;
        auto luminaryY = (int) std::floor(luminaryIndex / LUMINARY_WIDTH);
        auto surfaceLowX = luminaryX * PIXEL_SIZE;
        auto surfaceLowY = luminaryY * PIXEL_SIZE;
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
    return 0;
}

bool Palantir::finished() {
    return false;
}

}
