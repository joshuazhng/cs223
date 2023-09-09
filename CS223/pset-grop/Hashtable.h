/**
 * Hashtable.h
 *
 *      Interface of Hashtable, using chaining.
 *      Interface mostly follows std::unordered_map
 *
 * Alan Weide
 * CPSC 223
 * Spring 2023
 *
 */
#pragma once

#include <string>
#include <vector>
/**
 * @brief A hashtable implementation
 *
 * Uses the roughly the same interface as std::unordered_map
 */
template <class Value>
class Hashtable
{
public:
    typedef std::string Key;

    /**
     * @brief Default constructor. Creates a table with size initial_capacity
     */
    Hashtable();

    /**
     * @brief  Parameterized constructor. Initializes table with tablesize buckets
     *
     * @param tablesize
     */
    Hashtable(size_t tablesize);

    /**
     * @brief Inserts the Key Value pair into this hashtable, updating the existing value if that key is already in the table
     *
     * @param key       Key associated with value to insert
     * @param to_insert  Value to insert to table
     * @return Value*   Pointer to inserted value
     */
    Value *insert(const Key &key, const Value &to_insert);

    /**
     * @brief Returns a reference to key's corresponding value in the table
     * @throws runtime_error if key is not in table
     *
     * @param key
     * @return Value&
     */
    Value &at(const Key &key);
    const Value &at(const Key &key) const;

    /**
     * @brief Checks if this table has a stored value for key
     *        Returns nullptr if not found.
     *
     * @param key
     * @return Value* or const Value*
     */
    Value *find(const Key &key);
    const Value *find(const Key &key) const;

    /**
     * @brief Gets value corresponding to provided key;
     *        If value doesn't exist, a default one is inserted into this hash table and returned
     *        (Just like unordered_map::operator[])
     *
     * @param key
     * @return Value&
     */
    Value &operator[](const Key &key);

    /**
     * @brief Returns load_factor of hashtable
     *
     * @tparam Value
     * @return double
     */
    double load_factor() const;

    /**
     * @brief Returns number of elements stored in hashtable
     *
     * @return size_t
     */
    size_t size() const;

private:
    static constexpr int initial_capacity = 1024;
    static constexpr double max_load_factor = 0.5;

    /**
     * @brief Doubles the size of the table
     */
    void expand();

    /**
     * @brief Computes the index of provided key
     *
     * @param key         The key
     * @return size_t The corresponding index of provided key
     */
    size_t index_of(const Key &key) const;

    /**
     * @brief A struct to store Hashtable elements as a Key-Value pair
     *
     */
    struct KeyValue
    {
        KeyValue(const Key &k, const Value &v) : key(k), val(v) {}
        Key key;
        Value val;
    };

    // Add private members for implementation

    // Array of vectors to implement the chained table
    std::vector<std::vector<KeyValue>> table;

    // Keep track of the size of the array of vectors
    size_t table_size;

    // Keep track of the number of elements in the table
    size_t num_elm;

    // Declare Hash function
    std::hash<Key> hash;
};
