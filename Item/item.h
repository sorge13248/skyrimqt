#ifndef ITEM_H
#define ITEM_H

#include "../core.h"

namespace Skyrim {
    class Item {
    protected:
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
        const static string type;

    public:
        explicit Item(string, ushort);
        virtual ~Item() = default;

        string getName() const;
        ushort getLevel() const;
        Quality getQuality() const;
        virtual string getType() const = 0;

        void setName(string);
        void setLevel(ushort);
    };
}

#endif // ITEM_H
