
namespace CppCommon {

inline Process Process::CurrentProcess()
{
    return Process(CurrentProcessId());
}

inline Process Process::ParentProcess()
{
    return Process(ParentProcessId());
}

inline void swap(Process& process1, Process& process2) noexcept
{
    process1.swap(process2);
}

} // namespace CppCommon
