#pragma once

namespace AttributePayloadStatic
{
    static void PrintI(unsigned int *indices, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            std::cout << "[" << i << "] " << indices[i] << ", ";
            if ((i + 1) % 4 == 0)
                std::cout << "\n";
        }
    }
    static void PrintIAttr(InstanceAttr *attrs, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            attrs[i].print();
            std::cout << "\n";
        }
    }
} // namespace AttributePayloadStatic

struct AttributePayload
{
    std::unique_ptr<unsigned int[]> indices;
    std::unique_ptr<float[]> vertices;
    std::unique_ptr<InstanceAttr[]> instances;
    unsigned int indicesCount, verticesCount, instancesCount;

    unsigned int getIndicesSize() { return indicesCount * getIndicesTypeSize(); }
    std::size_t getIndicesTypeSize() { return sizeof(unsigned int); }
    unsigned int getVerticesSize() { return verticesCount * getVerticesTypeSize(); }
    std::size_t getVerticesTypeSize() { return sizeof(float); }
    unsigned int getInstancesSize() { return instancesCount * getInstancesTypeSize(); }
    std::size_t getInstancesTypeSize() { return sizeof(InstanceAttr); }

    void release()
    {
        indices.release();
        vertices.release();
        instances.release();
    }
    void print()
    {
        // AttributePayloadStatic::PrintI(indices.get(), indicesCount);
        AttributePayloadStatic::PrintIAttr(instances.get(), instancesCount);
    }
};