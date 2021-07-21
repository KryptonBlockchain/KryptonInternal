

namespace CppCommon {

template <void (*construct)(), void (*destruct)()>
typename StaticConstructor<construct, destruct>::constructor StaticConstructor<construct, destruct>::instance;

} // namespace CppCommon
