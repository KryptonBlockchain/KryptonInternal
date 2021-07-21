
namespace CppCommon {

inline std::ostream& operator<<(std::ostream& os, const SourceLocation& source_location)
{
    if ((source_location.filename() == nullptr) || (source_location.line() == 0))
        return os;

    return os << source_location.filename() << ':' << source_location.line();
}

} // namespace CppCommon
