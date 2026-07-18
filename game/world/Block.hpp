#pragma once

namespace Universe
{
    enum BlockType
    {
        None = 0,
        GRASS, DIRT
    };
    
    class Block
    {
    public:
        Block(BlockType type);
        ~Block() = default;

        BlockType GetType() const { return m_Type; }

    private:
        BlockType m_Type;
    };
}