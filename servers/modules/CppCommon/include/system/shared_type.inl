

namespace CppCommon {

template <typename T>
inline SharedType<T>::SharedType(const std::string& name) : _shared(name, sizeof(T))
{
    // Check for the owner flag
    if (_shared.owner())
    {
        // Call in place constructor
        new (_shared.ptr()) T();
    }
}

} // namespace CppCommon
