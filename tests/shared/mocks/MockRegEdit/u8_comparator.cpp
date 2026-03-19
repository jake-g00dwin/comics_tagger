#include "u8_comparator.hpp"
#include "CppUTest/SimpleString.h"

/*
class MyTypeComparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
        return object1 == object2;
    }
    virtual SimpleString valueToString(const void* object)
    {
        return StringFrom(object);
    }
};
*/

bool UInt8PointerComparator::isEqual(const void *object1, const void *object2)
{
    const uint8_t *ptr1 = reinterpret_cast<const uint8_t *>(object1);
    const uint8_t *ptr2 = reinterpret_cast<const uint8_t *>(object2);
    return std::memcmp(ptr1, ptr2, sizeof(uint8_t)) == 0;
}

SimpleString UInt8PointerComparator::valueToString(const void *object)
{
    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(object);
    return StringFromFormat("0x%02x", *ptr);
}

/*
bool UInt8PointerComparator::isEqual(const void* object1, const void* object2) const {
    const uint8_t* ptr1 = static_cast<const uint8_t*>(object1);
    const uint8_t* ptr2 = static_cast<const uint8_t*>(object2);
    return std::memcmp(ptr1, ptr2, sizeof(uint8_t)) == 0;
}

SimpleString UInt8PointerComparator::valueToString(const void* object) const {
    const uint8_t* ptr = static_cast<const uint8_t*>(object);
    return StringFromFormat("0x%02x", *ptr);
}
*/

bool UInt8Comparator::isEqual(const void *object1, const void *object2)
{
    return (uint8_t *)object1 == (uint8_t *)object2;
}

SimpleString UInt8Comparator::valueToString(const void *object)
{
    // uint8_t value = reinterpret_cast<uint8_t>(object);
    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(object);
    return StringFromFormat("0x%02x", *ptr);
}
