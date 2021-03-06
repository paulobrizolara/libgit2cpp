#pragma once

#include <functional>

struct git_index;
struct git_repository;
struct git_strarray;
struct git_index_entry;

namespace git
{
    struct Index
    {
        explicit Index(git_repository * repo);
        explicit Index(const char * dir);

        ~Index();

        size_t entrycount() const;
        git_index_entry const * operator[] (size_t i) const;

        typedef std::function<int (const char * path, const char * mathched_pathspec)> matched_path_callback_t;
        
        void update_all (git_strarray const & pathspec, matched_path_callback_t cb);
        void add_all    (git_strarray const & pathspec, matched_path_callback_t cb, unsigned int flags = 0);

        git_oid write_tree() const;

        void write() const;

        Index               (Index const &) = delete;
        Index& operator =   (Index const &) = delete;

        Index(Index && other);

    private:
        git_index * index_;
    };
}
