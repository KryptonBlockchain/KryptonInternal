
namespace CppCommon {

inline void Directory::swap(Directory& directory) noexcept
{
    using std::swap;
    Path::swap(directory);
}

inline void swap(Directory& directory1, Directory& directory2) noexcept
{
    directory1.swap(directory2);
}

} // namespace CppCommon
