#ifndef QCONTAINER_H
#define QCONTAINER_H

#include "core.h"
#include "Item/item.h"

namespace FrancescoSorge {
    template<class T>
    class QContainer {
    private:
        ushort count;

        class node {
        public:
            T info;
            node *prev,*next;
            explicit node(const T& t, node* p=0, node* n=0): info(t), prev(p), next(n) {}
            ~node() {if(next) delete next;}
        };

        node *first, *last;

        static bool lexCompare(node* f1, node* f2) {
            if(!f2) return false;
            if(!f1) return true;
            return f1->info < f2->info || (f1->info == f2->info && lexCompare(f1->next,f2->next));
        }

    public:
        explicit QContainer() : count(0) {

        }

        QContainer(const QContainer& dl) {
            first = copy(dl.first, last);
            count = dl.count;
        }

        QContainer& operator=(const QContainer& dl) {
            if(this != &dl) {
                if(first) delete first;
                first = copy(dl.first, last);
                count = dl.count;
            }
            return *this;
        }
        ~QContainer() {if(first) delete first;}

        void insertFront(const T& t) {
            first = new node(t,nullptr,first);
            if(last == nullptr) {last = first;}
            else {(first->next)->prev = first;}
            count++;
        }

        void insertBack(const T& t) {
            last = new node(t,last,nullptr);
            if(first == nullptr) {first = last;}
            else {(last->prev)->next = last;}
            count++;
        }

        explicit QContainer(int k, const T& t): first(nullptr), last(nullptr) {
            for(int i=0; i<k; ++i) insertBack(t);
        }

        bool operator<(const QContainer& dl) const {
            return lexCompare(first,dl.first);
        }

        ushort getCount() const {
            return count;
        }

        class constiterator {
            friend class QContainer<T>;
        private:
            const node* pt;
            bool pte; // true if past-the-end
            explicit constiterator(node* p, bool b=false): pt(p), pte(b) {}
        public:
            explicit constiterator(): pt(nullptr), pte(false) {}

            constiterator& operator++() {
                if(!pte && pt) {
                    if(pt->next == nullptr) {pt = pt+1; pte=true;}
                    else pt = pt->next;
                }
                return *this;
            }

            constiterator& operator--() {
                if(pte) {pt = pt-1; pte=false;}
                else if(pt) {pt = pt->prev;}
                return *this;
            }

            const T& operator*() const {
                return pt->info;
            }
            const T* operator->() const {
                return &(pt->info);
            }
            bool operator==(const constiterator& x) const {
                return pt == x.pt;
            }
            bool operator!=(const constiterator& x) const {
                return pt != x.pt;
            }
        };

        T const getByIndex(ushort index) const {
            ushort i = 0;
            for (constiterator it = begin(); it != end(); ++it) {
                if (i == index) {
                    return (*it);
                }
            }
            return nullptr;
        }

        constiterator begin() const {
            return constiterator(first);
        }

        constiterator end() const {
            if(first==nullptr) return constiterator(nullptr);
            return constiterator(last+1,true);
        }

        T operator[](constiterator it) const {
            return it.pt->info;
        }

    };
}

#endif // QCONTAINER_H
