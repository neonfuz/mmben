#include <SDL2/SDL.h>
#include "../c-vector/vec.h"
#include "bnl.h"

static
AST parse(Lexed l) {
  AST ast = { vector_create(), l.body };
  Object *obj = vector_add_asg(&ast.objs);
  obj->type = OBJ_NULL;
  for (unsigned t=0; t<vector_size(l.tokens); ++t) {

  }
  return ast;
}

AST BNL_Parse(char *bnl) {
  return parse(BNL_lex(bnl));
}
