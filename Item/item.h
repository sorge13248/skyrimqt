#ifndef ITEM_H
#define ITEM_H

#include "../core.h"

namespace Skyrim {
// ITEMS
    class Item {
    protected:
        // QUALITY
        enum Quality {
            Normal = 1,
            NotCommon = 2,
            Rare = 3,
            Epic = 4,
            Legendary = 5
        };
        string name;
        ushort level;
        Quality quality;

    public:
        string const type;

        explicit Item(string, ushort);
        virtual ~Item() = default;

        string getName() const;

        ushort getLevel() const;

        Quality getQuality() const;
    };
}

#endif // ITEM_H
