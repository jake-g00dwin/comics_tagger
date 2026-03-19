#ifndef U8_COMPARATOR_H
#define U8_COMPARATOR_H

#include <cstdint>
#include <cstring>
#include <CppUTestExt/MockSupport.h>

class UInt8PointerComparator : public MockNamedValueComparator {
public:
    virtual bool isEqual(const void* object1, const void* object2) override;
    SimpleString valueToString(const void* object) override;
};

class UInt8Comparator : public MockNamedValueComparator {
    public:
        virtual bool isEqual(const void* object1, const void* object2) override;
        SimpleString valueToString(const void* object) override;
};

#endif //U8_COMPARATOR_H
