#pragma once

#include "util/DetailedArray.h"

struct BufferAttrib
{
    enum Normalized
    {
        bool_type_true = GL_TRUE,
        bool_type_false = GL_FALSE
    };
    unsigned int layout;
    unsigned int divisor;
    unsigned int size;
    bool normalized;
    unsigned int stride;
    size_t offset;

    int glNormalized()
    {
        if (normalized)
            return GL_TRUE;
        return GL_FALSE;
    }
};

struct BufferPayload
{
    enum DrawType
    {
        static_draw = GL_STATIC_DRAW,
        dynamic_draw = GL_DYNAMIC_DRAW,
        stream_draw = GL_STREAM_DRAW
    };
    bool isNotEmpty = false;
    unsigned int bufferId;
    DetailedArray<float> dataArray;
    DrawType drawType;
    DetailedArray<BufferAttrib> attributes;

    void make_from(BufferPayload &other)
    {
        bufferId = other.bufferId;
        drawType = other.drawType;
        dataArray.make_from(other.dataArray);
        attributes.make_from(other.attributes);
    }
};