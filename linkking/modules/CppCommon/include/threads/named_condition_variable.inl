
namespace CppCommon {

template <typename TPredicate>
void NamedConditionVariable::Wait(TPredicate predicate)
{
    while (!predicate())
        Wait();
}

template <typename TPredicate>
bool NamedConditionVariable::TryWaitFor(const Timespan& timespan, TPredicate predicate)
{
    Timestamp timeout = UtcTimestamp() + timespan;
    while (!predicate())
        if (!TryWaitFor(timeout - UtcTimestamp()))
            return predicate();
    return true;
}

} // namespace CppCommon
