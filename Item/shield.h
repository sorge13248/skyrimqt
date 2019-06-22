#ifndef SHIELD_H
#define SHIELD_H

#include "../core.h"
#include "item.h"

namespace Skyrim {

    class Shield : public Item {
    private:
        ushort absorb;
        const static string type;

    public:
        explicit Shield(string name, ushort level = 1, ushort absorb = 12);
        ~Shield() = default;

        ushort getAbsorb() const;
        virtual string getType() const;
    };
}

#endif // SHIELD_H
