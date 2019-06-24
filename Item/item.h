#ifndef ITEM_H
#define ITEM_H

#include "../core.h"

namespace Skyrim {
    class Item {
    protected:
        string name;
        ushort level;
        const static string type;
        const static string image;

    public:
        explicit Item(string, ushort);
        virtual ~Item() = default;

        string getName() const;
        ushort getLevel() const;
        virtual string getImage() const = 0;
        virtual string getType() const = 0;

        void setName(string);
        void setLevel(ushort);
    };
}

#endif // ITEM_H
