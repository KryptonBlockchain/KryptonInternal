
namespace CppCommon {

template <typename T>
inline T GCD(T a, T b)
{
    T c = a % b;

    while (c != 0)
    {
        a = b;
        b = c;
        c = a % b;
    }

    return b;
}

template <typename T>
inline T Math::RoundUp(T a, T k)
{
    return ((a + k - 1) / k) * k;
}

} // namespace CppCommon
