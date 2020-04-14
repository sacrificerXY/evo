#pragma once

template <typename T>
class Id
{
public:
    int get()
    {
        return count++;
    }
    int test() const
    {
        return count;
    }
private:
    int count = 0; 
};
