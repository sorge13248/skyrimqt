#ifndef SHIELD_H
#define SHIELD_H

#include "../core.h"
#include "item.h"

namespace Skyrim {

    class Shield : public Item {
    private:
        ushort absorb;
    public:
        string const type = "Shield";

        explicit Shield(string name, ushort level = 1, ushort absorb = 12);
        ~Shield() = default;

        ushort getAbsorb() const;
    };
}

#endif // SHIELD_H
