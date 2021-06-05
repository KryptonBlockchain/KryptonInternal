

namespace CppCommon {

template <typename TPredicate>
void ConditionVariable::Wait(CriticalSection& cs, TPredicate predicate)
{
    while (!predicate())
        Wait(cs);
}

template <typename TPredicate>
bool ConditionVariable::TryWaitFor(CriticalSection& cs, const Timespan& timespan, TPredicate predicate)
{
    Timestamp timeout = UtcTimestamp() + timespan;
    while (!predicate())
        if (!TryWaitFor(cs, timeout - UtcTimestamp()))
            return predicate();
    return true;
}

} // namespace CppCommon
