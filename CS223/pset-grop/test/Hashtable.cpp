/**
 * Hashtable.cpp
 *
 *      Implementation of Hashtable, using chaining.
 *      Interface mostly follows std::unordered_map
 *
 * Alan Weide
 * CPSC 223
 * Spring 2023
 *
 */
#include "Hashtable.h"
#include <iostream>
#include <vector>
#include <functional>

template <class Value>
Hashtable<Value>::Hashtable() : Hashtable(initial_capacity) {}

template <class Value>
Hashtable<Value>::Hashtable(size_t tablesize)
{
    table.resize(tablesize);
    table_size = tablesize;
}

template <class Value>
Value *Hashtable<Value>::insert(const Key &key, const Value &to_insert)
{
    size_t index = index_of(key);
    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].key == key) {
            table[index][i] = KeyValue(key, to_insert);
            return &(table[index][i].val);
        }
    }

    // Check if load factor exceeds the max, if so call expand
    if (load_factor() > max_load_factor) {
        expand();
    }

    table[index].push_back(KeyValue(key, to_insert));
    return &(table[index].back().val);
}

template <class Value>
void Hashtable<Value>::expand()
{
    size_t new_table_size = table_size * 2;
    std::vector<std::vector<KeyValue>> new_table(new_table_size);

    for (size_t i = 0; i < table_size; i++) {
        for (size_t j = 0; j < table[i].size(); j++) {
            insert(table[i][j].key, table[i][j].val);
        }
    }

    table = new_table;
    table_size = new_table_size;
}

template <class Value>
Value &Hashtable<Value>::at(const Key &key)
{
    Value *to_return = find(key);
    if (to_return == nullptr)
    {
        throw std::runtime_error("Key not in table");
    }
    return *to_return;
}

template <class Value>
const Value &Hashtable<Value>::at(const Key &key) const
{
    const Value *to_return = find(key);
    if (to_return == nullptr)
    {
        throw std::runtime_error("Key not in table");
    }
    return *to_return;
}

template <class Value>
Value *Hashtable<Value>::find(const Key &key)
{
    size_t index = index_of(key);

    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].key == key) {
            return &(table[index][i].val);
        }
    }

    return nullptr;
}

template <class Value>
const Value *Hashtable<Value>::find(const Key &key) const
{
    size_t index = index_of(key);

    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].key == key) {
            return &(table[index][i].val);
        }
    }

    return nullptr;
}

template <class Value>
Value &Hashtable<Value>::operator[](const Key &key)
{
    if (find(key) == nullptr) {
        insert(key, Value());
    }

    return *(find(key));
}

template <class Value>
size_t Hashtable<Value>::index_of(const Key &key) const
{
    return hash(key) % table_size;
}

template <class Value>
size_t Hashtable<Value>::size() const
{
    return num_elm;
}

template <class Value>
double Hashtable<Value>::load_factor() const
{
    return (double) (num_elm / table_size);
}

// Explicit template specialization for "string"s
template class Hashtable<std::string>;

// Explicit template specialization for "Entry"s
#include "Entry.h"
template class Hashtable<std::vector<Entry>>;
