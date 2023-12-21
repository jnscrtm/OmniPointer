#pragma once

#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

/// @brief A pointer that can point to basically any type of object. Each `OmniPointer` shall uniquely own an object, if any.
/// @author Jean-Valentin Auguste
/// @date December 2023
/// @warning Cannot be used for pointers of dynamically-allocated array.
class OmniPointer
{
private:
    template <class T>
    static void destroy_pointer(void* ptr)
    {
        if(ptr != nullptr)
            delete reinterpret_cast<T*>(ptr);
    }

    void* _ptr;
    void(*destroyer)(void*);

public:
    /// @brief Construct an empty OmniPointer.
    constexpr OmniPointer() noexcept : _ptr(nullptr), destroyer(nullptr) {}

    /// @brief Has the same effect as the default constructor.
    constexpr OmniPointer(std::nullptr_t) noexcept : OmniPointer() {}

    /// @brief Deleted. A copy mechanism of `OmniPointer` shall not be allowed.
    OmniPointer(const OmniPointer&) = delete;

    /// @brief Constructs an `OmniPointer` and moves in every information contained by the specified `OmniPointer`.
    /// @param var The other `OmniPointer`.
    OmniPointer(OmniPointer&&) noexcept;

    /// @brief Constructs an OmniPointer from the given pointer.
    /// @tparam T The type of the object the given pointer is pointing at.
    /// @param pvar The given pointer.
    /// @warning Assigning a local raw pointer is not recommended for it may cause dangling pointers in case two `OmniPointer`s are constructed from the same raw pointer or it is itself a dangling or wild pointer. Assigning a pointer of a dynamic array is also not recommended for the deletion mechanism will most likely be invalid.
    template <class T>
    OmniPointer(T* pvar) : _ptr((void*)pvar), destroyer(destroy_pointer<T>) {}

    /// @brief Gets the address of the object the `OmniPointer` is pointing to.
    /// @tparam T The desired type
    /// @return A `T` pointer containing the address the `OmniPointer` is pointing at.
    /// @exception std::logic_error when `T` does not match the information stored in the `OmniPointer` unless `T` is `void`.
    template <class T>
    T* Get() const
    {
        if(std::is_void<T>::value)
            return _ptr;
        else if (destroyer == destroy_pointer<T>)
            return reinterpret_cast<T*>(_ptr);
        else
            throw std::logic_error("The latest stored object is not of the requested type.");
    }

    /// @brief Releases the ownership of object, if any.
    /// @tparam T The desired type
    /// @return A `T` pointer containing the address the `OmniPointer` was previously pointing at.
    /// @exception std::logic_error when `T` does not match the information stored in the `OmniPointer` unless `T` is `void`.
    /// @note A null pointer may be returned if the `OmniPointer` previously had no stored object.
    template <class T>
    T* Release()
    {
        if (std::is_void<T>::value || destroyer == destroy_pointer<T>)
        {
            T* res = reinterpret_cast<T*>(_ptr);

            _ptr = nullptr;
            destroyer = nullptr;

            return res;
        }
        else
            throw std::logic_error("The latest stored object is not of the requested type.");
    }

    /// @brief Resets the `OmniPointer` and changes the ownership of object if `tptr` is not null.
    /// @tparam T The desired type
    /// @param tptr The pointer to the object to be acquired ownership of
    template <class T>
    void Reset(T* tptr = (T*) nullptr)
    {
        void* old_ptr = _ptr;
        _ptr = (void*)tptr;

        if (destroyer != nullptr)
            destroyer(old_ptr);

        destroyer = destroy_pointer<T>;
    }

    /// @brief Resets the `OmniPointer`.
    void Reset(std::nullptr_t) noexcept;

    /// @brief Swaps the ownerships between the `OmniPointer` and the other.
    /// @param other The other `OmniPointer` to swap ownerships with
    void Swap(OmniPointer& other) noexcept;

    /// @brief Resets the `OmniPointer` and moves in every information contained by the other `OmniPointer`.
    /// @param var The other `OmniPointer`.
    OmniPointer& operator=(OmniPointer&& var) noexcept;

    /// @brief Deleted. A copy mechanism of `OmniPointer` shall not be allowed.
    OmniPointer& operator=(const OmniPointer&) = delete;

    /// @brief Has the same effect as `OmniPointer::Reset(std::nullptr_t)`.
    OmniPointer& operator=(std::nullptr_t) noexcept;

    /// @brief Determines if two `OmniPointer`s are pointing at the same address.
    bool operator==(const OmniPointer& other) const noexcept;

    /// @brief Determines if two `OmniPointer`s are pointing at different addresses.
    bool operator!=(const OmniPointer& other) const noexcept;

    /// @brief The same as `OmniPointer::Get<T>()`.
    /// @tparam T The desired type
    /// @exception std::logic_error when `T` does not match the information stored in the `OmniPointer`.
    template <class T>
    operator T* () const
    {
        return Get<T>();
    }

    /// @brief Destroys the `OmniPointer` and the stored object therein, if any.
    ~OmniPointer() noexcept;
};

template<>
void OmniPointer::destroy_pointer<void>(void*);