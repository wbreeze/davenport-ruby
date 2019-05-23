#include <ruby.h>
#include <ruby/intern.h>
#include "davenport/davenport.h"
#include "davenport/network.h"
#include "extconf.h"

typedef struct RbDavenport {
  int node_ct;
  int *preference_graph;
} RbDavenport;

static void pg_deallocate(void *data)
{
  RbDavenport *rbdv = (RbDavenport *)data;
  if (rbdv->preference_graph != NULL) free(rbdv->preference_graph);
  free(rbdv);
}

static size_t pg_report_size(const void *data)
{
  RbDavenport *rbdv = (RbDavenport *)data;
  return sizeof(RbDavenport) + ESZ(rbdv->node_ct);
}

static const rb_data_type_t rb_davenport_type = {
  .wrap_struct_name = "RbDavenport",
  .function = {
    .dmark = NULL,
    .dfree = pg_deallocate,
    .dsize = pg_report_size,
  },
  .data = NULL,
  .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE pg_allocate(VALUE self)
{
  RbDavenport *rbdv = malloc(sizeof(RbDavenport));
  rbdv->node_ct = 0;
  rbdv->preference_graph = NULL;
  return TypedData_Wrap_Struct(self, &rb_davenport_type, rbdv);
}

static VALUE initialize(VALUE self, VALUE node_ct)
{
  Check_Type(node_ct, T_FIXNUM);
  RbDavenport *rbdv;
  TypedData_Get_Struct(self, RbDavenport, &rb_davenport_type, rbdv);
  rbdv->node_ct = FIX2INT(node_ct);
  rbdv->preference_graph = edge_array_calloc(rbdv->node_ct);
  return self;
}

VALUE add_preference(VALUE self, VALUE pref_array)
{
  Check_Type(pref_array, T_ARRAY);
  RbDavenport *rbdv;
  TypedData_Get_Struct(self, RbDavenport, &rb_davenport_type, rbdv);
  long len = RARRAY_LEN(pref_array);
  if (len != rbdv->node_ct) {
    // says "define" but actually does lookup
    VALUE mDv = rb_define_module("Davenport");
    VALUE exc_cl = rb_define_class_under(mDv,
      "PreferenceGraphCountException", rb_eStandardError);
    rb_raise(exc_cl,
      "Expected array of length %d, given %ld", rbdv->node_ct, len);
  }
  for (long i = 0; i < len; ++i) {
    VALUE vi = rb_ary_entry(pref_array, i);
    Check_Type(vi, T_FIXNUM);
  }
  return Qnil;
}

VALUE davenport(VALUE self)
{
  VALUE pref = rb_ary_new();
  rb_ary_push(pref, INT2NUM(1));
  rb_ary_push(pref, INT2NUM(3));
  rb_ary_push(pref, INT2NUM(2));
  rb_ary_push(pref, INT2NUM(4));
  return pref;
}

void Init_davenport()
{
  VALUE mDv = rb_define_module("Davenport");
  VALUE cPg = rb_define_class_under(mDv, "PreferenceGraph", rb_cData);
  rb_define_alloc_func(cPg, pg_allocate);
  rb_define_method(cPg, "initialize", initialize, 1);
  rb_define_method(cPg, "add_preference", add_preference, 1);
  rb_define_method(cPg, "davenport", davenport, 0);
}
