#include "project/exercise.hpp"
#include <algorithm>
#include <utility>
#include <stdexcept> // for throwing function

// ✅ TODO: Implement default constructor.
DynamicBuffer::DynamicBuffer()
{
    data_ = nullptr;
    size_ = 0;
}

// ✅ TODO: Implement allocation and initialization.
// Use a C++ array allocated with new[] and zero-initialize the contents.
DynamicBuffer::DynamicBuffer(size_t capacity)
{
    data_ = new int[capacity]{}; // dynamically creates an array of capacity integers initialized to 0
    size_ = capacity;            // stores the number of elements
}

// ✅ TODO: Implement deep-copy constructor.
DynamicBuffer::DynamicBuffer(const DynamicBuffer &other)
{
    size_ = other.size_;

    // Allocate new memory for the object 'other'
    data_ = new int[size_];

    // Use for loop to copy the data into the array
    for (int i = 0; i < size_; i++)
        data_[i] = other.data_[i];
}

// ✅ TODO: Implement move constructor.
DynamicBuffer::DynamicBuffer(DynamicBuffer &&other) noexcept
{
    // Steal the pointer from the source object 'other'
    this->data_ = other.data_;
    this->size_ = other.size_;

    // Reset the source object so its destructor won't delete the memory
    other.data_ = nullptr;
    other.size_ = 0;
}

// ✅ TODO: Implement destructor with proper cleanup.
DynamicBuffer::~DynamicBuffer()
{
    // Clean-up code goes directly in the function body
    delete[] data_;
}

// ✅ TODO: Implement copy assignment with self-assignment protection.
DynamicBuffer &DynamicBuffer::operator=(const DynamicBuffer &other)
{
    if (this != &other)
    {                           // check for self-assignment: ex: num1 = num2
        delete[] data_;         // delete old memory
        size_ = other.size_;    // copy the size
        data_ = new int[size_]; // allocate new memory

        // copy each element
        for (int i = 0; i < size_; i++)
            data_[i] = other.data_[i];
    }

    return *this; // returns a reference to the current object
}

// ✅ TODO: Implement move assignment.
DynamicBuffer &DynamicBuffer::operator=(DynamicBuffer &&other) noexcept
{
    // Check for self-assignment
    if (this != &other)
    {
        // Free old memory
        delete[] data_;

        // Steal resources from the source object
        data_ = other.data_;
        size_ = other.size_;

        // Reset the source to nullptr
        other.data_ = nullptr;
        other.size_ = 0;
    }

    return *this; // return a reference to the current object
}

// ✅ TODO: Return the current managed size.
size_t DynamicBuffer::size() const noexcept
{
    return size_;
}

// ✅ TODO: Return true if the buffer is empty.
bool DynamicBuffer::empty() const noexcept
{
    return size_ == 0; // If size_ = 0, returns true!
}

// ✅ TODO: Implement resize with resource ownership and exception safety.
// Keep all existing values up to the minimum of old and new sizes.
void DynamicBuffer::resize(size_t newSize)
{
    // Case 1: Same size, do nothing
    if (newSize == size_)
        return;

    // Case 2:  Smaller, keep the first newSize elements
    if (newSize < size_)
    {
        size_ = newSize;
        return;
    }

    // Case 3: Larger, allocate a new array, copy the old values, and initialize
    //         the new elements to 0
    int *newData = new int[newSize]{}; // Empty brackets = 0 initialization

    for (size_t i = 0; i < size_; i++)
    {
        newData[i] = data_[i];
    }

    delete[] data_; // Clear memory

    data_ = newData; // Assign the new data
    size_ = newSize; // Assign the new size
}

// ✅ TODO: Fill all elements with the given value.
void DynamicBuffer::fill(int value)
{
    // Loop through each element of the array and fill each element with 'value'
    for (size_t i = 0; i < size_; i++)
    {
        data_[i] = value;
    }
}

// ✅ TODO: Validate index and assign the value.
void DynamicBuffer::setAt(size_t index, int value)
{
    // If index is invalid:
    if (index < 0 || index >= size_)
        throw std::out_of_range("Error, index is invalid.\n");

    // If index is valid:
    data_[index] = value;
}

// ✅ TODO: Return element at index with bounds checking.
int DynamicBuffer::at(size_t index) const
{
    // If index is invalid:
    if (index < 0 || index >= size_)
        throw std::out_of_range("Error, index is invalid.\n");

    return data_[index];
}

// ✅ TODO: Return a reference without bounds checking.
int &DynamicBuffer::operator[](size_t index)
{
    return data_[index];
}

// ✅  TODO: Return const reference without bounds checking.
const int &DynamicBuffer::operator[](size_t index) const
{
    return data_[index];
}

// ✅  TODO: Compare size and elements.
bool DynamicBuffer::operator==(const DynamicBuffer &other) const
{
    // Compare size
    if (size_ != other.size_)
        return false;

    // Compare elements
    for (size_t i = 0; i < size_; i++)
    {
        if (data_[i] != other.data_[i])
            return false;
    }

    return true;
}

// ✅ TODO: Implement inequality comparison.
bool DynamicBuffer::operator!=(const DynamicBuffer &other) const
{
    return !(*this == other);
}

// ✅ TODO: Return true when the buffer owns valid memory.
DynamicBuffer::operator bool() const noexcept
{
    return data_ != nullptr;
}

// ✅ TODO: Delete allocated memory and reset state.
void DynamicBuffer::release()
{
    delete[] data_;

    data_ = nullptr;
    size_ = 0;
}

// ✅TODO: Deep-copy the other object's contents.
void DynamicBuffer::copyFrom(const DynamicBuffer &other)
{
    // allocate size
    size_ = other.size_;

    // check if 'other' is empty
    if (size_ == 0)
    {
        data_ = nullptr;
        return;
    }

    // allocate memeory
    data_ = new int[size_];

    // copy contents into the 'other' object
    for (size_t i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];
    }
}

// ✅ TODO: Swap the resources of two buffers.
void DynamicBuffer::swap(DynamicBuffer &other) noexcept
{
    // use the 'swap' function the swap the data and the size
    // of the 'other' object
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}
