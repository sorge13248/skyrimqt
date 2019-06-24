#ifndef SHIELD_H
#define SHIELD_H

#include "item.h"

namespace Skyrim {

    class Shield : public Item {
    private:
        ushort absorb;
        const static string type;
        const static string image;

    public:
        explicit Shield(string name, ushort level = 1, ushort absorb = 12);
        ~Shield() = default;

        ushort getAbsorb() const;
        virtual string getType() const;
        virtual string getImage() const;
    };
}

#endif // SHIELD_H
