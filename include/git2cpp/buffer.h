#pragma once

#include <git2/buffer.h>

namespace git
{
    struct Buffer
    {
        Buffer              (Buffer const &) = delete;
        Buffer& operator =  (Buffer const &) = delete;

        Buffer(Buffer &&);

        explicit Buffer(git_buf buf)
            : buf_(buf)
        {}

        ~Buffer();

        explicit operator bool() const { return ptr(); }

        const char * ptr() const { return buf_.ptr; }

    private:
        git_buf buf_;
    };
}
