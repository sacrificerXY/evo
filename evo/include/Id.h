#pragma once

template <typename T>
class Id
{
public:
    using Type = int;
    static Id::Type get()
    {
        return count++;
    }
private:
    inline static Id::Type count = 0; 
};
