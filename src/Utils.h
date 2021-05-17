#pragma once

#include <memory>

#define CONSTRUCTIBLE(class_name)                                                        \
public:                                                                                  \
    template <class... Args>                                                             \
    static inline std::shared_ptr<class_name> construct(Args&&... args)                  \
    {                                                                                    \
        return std::shared_ptr<class_name>(new class_name(std::forward<Args>(args)...)); \
    }
