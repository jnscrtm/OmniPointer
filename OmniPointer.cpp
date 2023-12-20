#include "OmniPointer.hpp"

OmniPointer::OmniPointer(OmniPointer&& var) noexcept : _ptr(var._ptr), type_hash(var.type_hash), destroyer(var.destroyer)
{
    var._ptr = nullptr;
    var.type_hash = 0;
    var.destroyer = nullptr;
}

void OmniPointer::Reset(std::nullptr_t) noexcept
{
    if (destroyer != nullptr)
        destroyer(_ptr);

    _ptr = nullptr;
    type_hash = 0;
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
    type_hash = var.type_hash;
    destroyer = var.destroyer;

    var._ptr = nullptr;
    var.type_hash = 0;
    var.destroyer = nullptr;

    return *this;
}

OmniPointer& OmniPointer::operator=(std::nullptr_t) noexcept
{
    Reset(nullptr);
    return *this;
}

OmniPointer::~OmniPointer() noexcept
{
    if (destroyer != nullptr)
        destroyer(_ptr);
}