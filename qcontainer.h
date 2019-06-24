#ifndef QCONTAINER_H
#define QCONTAINER_H

#include "core.h"

namespace FrancescoSorge {
    template<class T>
    class QContainer {
    private:

        class node {
        public:
            T info;
            node* prev;
            node* next;
            explicit node(const T& t, node* p=0, node* n=0): info(t), prev(p), next(n) {}
            ~node() {
                if(next) delete next;
            }
        };

        node* first;
        node* last;
        ushort count;
    public:
        explicit QContainer() : first(0), last(0), count(0) { }

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
            for (constiterator it = begin(); it != end(); ++it, ++i) {
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

        bool remove(ushort index) {
            ushort i = 0;
            node* temp = first;
            while (temp) {
                if (i == index) {
                    if(temp->prev) {
                        (temp->prev)->next = temp->next;
                    } else {
                        first = temp->next;
                    }
                    if (temp->next) {
                        (temp->next)->prev = temp->prev;
                    } else {
                        last = temp->prev;
                    }
                    count--;
                    temp = nullptr;
                    return true;
                }
                temp = temp->next;
                i++;
            }
            return false;
        }
    };
}

#endif // QCONTAINER_H
