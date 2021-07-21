

namespace CppCommon {

inline void Timespan::swap(Timespan& timespan) noexcept
{
    using std::swap;
    swap(_duration, timespan._duration);
}

inline void swap(Timespan& timespan1, Timespan& timespan2) noexcept
{
    timespan1.swap(timespan2);
}

} // namespace CppCommon

namespace std {

template <>
struct hash<CppCommon::Timespan>
{
    typedef CppCommon::Timespan argument_type;
    typedef size_t result_type;

    result_type operator() (const argument_type& value) const
    {
        result_type result = 17;
        result = result * 31 + std::hash<int64_t>()(value.total());
        return result;
    }
};

} // namespace std
