#ifndef SASS_EXPAND_H
#define SASS_EXPAND_H

#include <vector>

#include "ast.hpp"
#include "eval.hpp"
#include "operation.hpp"
#include "environment.hpp"

namespace Sass {

  class Listize;
  class Context;
  class Eval;
  typedef Environment<AST_Node*> Env;
  struct Backtrace;

  class Expand : public Operation_CRTP<Statement*, Expand> {
  public:

    Env* environment();
    Context& context();
    CommaSequence_Selector* selector();
    Backtrace* backtrace();

    Context&          ctx;
    Eval              eval;
    size_t            recursions;
    bool              in_keyframes;
    bool              at_root_without_rule;
    bool              old_at_root_without_rule;

    // it's easier to work with vectors
    std::vector<Env*>           env_stack;
    std::vector<Block*>         block_stack;
    std::vector<AST_Node*>      call_stack;
    std::vector<String*>        property_stack;
    std::vector<CommaSequence_Selector*> selector_stack;
    std::vector<Media_Block*>   media_block_stack;
    std::vector<Backtrace*>     backtrace_stack;

    Statement* fallback_impl(AST_Node* n);

  private:
    void expand_selector_list(Selector*, CommaSequence_Selector* extender);

  public:
    Expand(Context&, Env*, Backtrace*, std::vector<CommaSequence_Selector*>* stack = NULL);
    ~Expand() { }

    Statement* operator()(Block*);
    Statement* operator()(Ruleset*);
    Statement* operator()(Media_Block*);
    Statement* operator()(Supports_Block*);
    Statement* operator()(At_Root_Block*);
    Statement* operator()(Directive*);
    Statement* operator()(Declaration*);
    Statement* operator()(Assignment*);
    Statement* operator()(Import*);
    Statement* operator()(Import_Stub*);
    Statement* operator()(Warning*);
    Statement* operator()(Error*);
    Statement* operator()(Debug*);
    Statement* operator()(Comment*);
    Statement* operator()(If*);
    Statement* operator()(For*);
    Statement* operator()(Each*);
    Statement* operator()(While*);
    Statement* operator()(Return*);
    Statement* operator()(Extension*);
    Statement* operator()(Definition*);
    Statement* operator()(Mixin_Call*);
    Statement* operator()(Content*);

    template <typename U>
    Statement* fallback(U x) { return fallback_impl(x); }

    void append_block(Block*);
  };

}

#endif
