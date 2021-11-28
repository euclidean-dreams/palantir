#include "Tchotchke.h"

namespace palantir {

void Tchotchke::assertNotNull(void *entity) {
    if (entity == nullptr) {
        throw SDLFailure{};
    }
}

}
