
namespace CppCommon {

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, Color color)
{
    Console::SetColor(color);
    return stream;
}

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, std::pair<Color, Color> colors)
{
    Console::SetColor(colors.first, colors.second);
    return stream;
}

} // namespace CppCommon
