#pragma once

enum class ElementType
{
    TEXT,
    SWITCH
};

struct Item
{
    ElementType elementType;
    std::string itemName;
    uint8_t itemValue;
};

