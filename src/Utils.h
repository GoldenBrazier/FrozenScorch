#pragma once

#include <memory>

#ifndef PACKED
#define PACKED __attribute__((packed))
#endif // PACKED

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE __attribute__((always_inline))
#endif // ALWAYS_INLINE

#ifndef NORETURN
#define NORETURN __attribute__((noreturn))
#endif // NORETURN

#define CONSTRUCTIBLE(class_name)                                                        \
public:                                                                                  \
    template <class... Args>                                                             \
    static inline std::shared_ptr<class_name> construct(Args&&... args)                  \
    {                                                                                    \
        return std::shared_ptr<class_name>(new class_name(std::forward<Args>(args)...)); \
    }
