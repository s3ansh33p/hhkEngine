class RandomGenerator {
    public:
        void SetSeed(uint32_t seed);
        uint32_t Generate(uint32_t max);
        uint32_t m_x = 0;
        uint32_t m_mul = 0;
        uint32_t m_add = 0;
};

void RandomGenerator::SetSeed(uint32_t seed)
{
    this->m_x = seed;
    this->m_mul = (1566083941 << 32) + 1812433253;
    this->m_add = 2531011;
}

uint32_t RandomGenerator::Generate(uint32_t max) {
    this->m_x = this->m_mul * this->m_x + this->m_add;
    if (max == 0)
    {
        return int(this->m_x >> 32);
    }
    else
    {
        return int(this->m_x >> 32) % max;
    }
}
