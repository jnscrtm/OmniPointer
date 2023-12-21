#include "OmniPointer.hpp"

OmniPointer::OmniPointer(OmniPointer&& var) noexcept : _ptr(var._ptr), destroyer(var.destroyer)
{
    var._ptr = nullptr;
    var.destroyer = nullptr;
}

void OmniPointer::Reset(std::nullptr_t) noexcept
{
    if (destroyer != nullptr)
        destroyer(_ptr);

    _ptr = nullptr;
    destroyer = nullptr;
}

void OmniPointer::Swap(OmniPointer& other) noexcept
{
    OmniPointer interm = std::forward<OmniPointer>(other);
    other = std::forward<OmniPointer>(*this);
    *this = std::forward<OmniPointer>(interm);
}

OmniPointer& OmniPointer::operator=(OmniPointer&& var) noexcept
{
    if (destroyer != nullptr)
        destroyer(_ptr);

    _ptr = var._ptr;
    destroyer = var.destroyer;

    var._ptr = nullptr;
    var.destroyer = nullptr;

    return *this;
}

OmniPointer& OmniPointer::operator=(std::nullptr_t) noexcept
{
    Reset(nullptr);
    return *this;
}

bool OmniPointer::operator==(const OmniPointer& other) const noexcept
{
    return _ptr == other._ptr;
}

bool OmniPointer::operator!=(const OmniPointer& other) const noexcept
{
    return _ptr != other._ptr;
}

OmniPointer::~OmniPointer() noexcept
{
    if (destroyer != nullptr)
        destroyer(_ptr);
}

template<>
void OmniPointer::destroy_pointer<void>(void*)
{
    return;
}