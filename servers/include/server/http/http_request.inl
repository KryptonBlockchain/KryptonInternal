

namespace std {

template <>
struct hash<LinkKing::HTTP::HTTPRequest>
{
    typedef LinkKing::HTTP::HTTPRequest argument_type;
    typedef size_t result_type;

    result_type operator() (const argument_type& value) const
    {
        result_type result = 17;
        result = result * 31 + std::hash<std::string>()(value.cache());
        return result;
    }
};

} // namespace std
