#pragma once


struct Genome;

class Random
{
public:
    auto weight() const -> float;
    auto from(const Genome& g) const -> int;
    auto to(const Genome& g) const -> int;
private:
    static constexpr float weight_range = 2.0f;
};