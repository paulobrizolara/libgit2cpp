#include "git2cpp/revwalker.h"
#include "git2cpp/error.h"
#include "git2cpp/repo.h"

#include <git2/revwalk.h>

namespace git
{
    namespace revwalker {
    namespace sorting
    {
        const type none         (GIT_SORT_NONE);
        const type topological  (GIT_SORT_TOPOLOGICAL);
        const type time         (GIT_SORT_TIME);
        const type reverse      (GIT_SORT_REVERSE);
    }}

    RevWalker::~RevWalker()
    {
        git_revwalk_free(walker_);
    }

    void RevWalker::sort(revwalker::sorting::type s)
    {
        git_revwalk_sorting(walker_, s.value());
    }

    void RevWalker::simplify_first_parent()
    {
       git_revwalk_simplify_first_parent(walker_);
    }

    void RevWalker::push_head() const
    {
        if (git_revwalk_push_head(walker_))
            throw invalid_head_error();
    }

    void RevWalker::hide(git_oid const & obj) const
    {
        if (git_revwalk_hide(walker_, &obj))
            throw non_commit_object_error(obj);
    }

    void RevWalker::push(git_oid const & obj) const
    {
        if (git_revwalk_push(walker_, &obj))
            throw non_commit_object_error(obj);
    }

    Commit RevWalker::next() const
    {
        git_oid oid;
        if (git_revwalk_next(&oid, walker_) == 0)
            return repo_->commit_lookup(oid);
        else
            return Commit();
    }

    bool RevWalker::next(char * id_buffer) const
    {
        git_oid oid;
        bool valid = (git_revwalk_next(&oid, walker_) == 0);
        if (valid)
            git_oid_fmt(id_buffer, &oid);
        return valid;
    }
}

