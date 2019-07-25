#include <ruby.h>
#include <ruby/intern.h>
#include "davenport/aggregate_solution.h"
#include "davenport/davenport.h"
#include "davenport/network.h"
#include "davenport/preference_graph.h"
#include "extconf.h"

typedef struct RbDavenport {
  int node_ct;
  int *preference_graph;
} RbDavenport;

static void pg_deallocate(void *data)
{
  RbDavenport *dvdata = (RbDavenport *)data;
  if (dvdata->preference_graph != NULL) free(dvdata->preference_graph);
  free(dvdata);
}

static size_t pg_report_size(const void *data)
{
  RbDavenport *dvdata = (RbDavenport *)data;
  return sizeof(RbDavenport) + ESZ(dvdata->node_ct);
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
  RbDavenport *dvdata = malloc(sizeof(RbDavenport));
  dvdata->node_ct = 0;
  dvdata->preference_graph = NULL;
  return TypedData_Wrap_Struct(self, &rb_davenport_type, dvdata);
}

static VALUE initialize(VALUE self, VALUE node_ct)
{
  Check_Type(node_ct, T_FIXNUM);
  RbDavenport *dvdata;
  TypedData_Get_Struct(self, RbDavenport, &rb_davenport_type, dvdata);
  dvdata->node_ct = FIX2INT(node_ct);
  dvdata->preference_graph = edge_array_calloc(dvdata->node_ct);
  return self;
}

VALUE add_preference(VALUE self, VALUE pref_array)
{
  Check_Type(pref_array, T_ARRAY);
  RbDavenport *dvdata;
  TypedData_Get_Struct(self, RbDavenport, &rb_davenport_type, dvdata);
  const long len = RARRAY_LEN(pref_array);
  if (len != dvdata->node_ct) {
    // says "define" but actually does lookup
    VALUE mDv = rb_define_module("Davenport");
    VALUE exc_cl = rb_define_class_under(mDv,
      "PreferenceGraphCountException", rb_eStandardError);
    rb_raise(exc_cl,
      "Expected array of length %d, given %ld", dvdata->node_ct, len);
  }
  const int node_ct = dvdata->node_ct;
  int rankings[node_ct];
  for (int i = 0; i < node_ct; ++i) {
    VALUE vi = rb_ary_entry(pref_array, i);
    Check_Type(vi, T_FIXNUM);
    rankings[i] = FIX2LONG(vi);
  }
  preference_graph_add_preference(dvdata->preference_graph, rankings, node_ct);
  return Qnil;
}

VALUE davenport(VALUE self)
{
  RbDavenport *dvdata;
  TypedData_Get_Struct(self, RbDavenport, &rb_davenport_type, dvdata);
  int node_ct = dvdata->node_ct;

  int *majority_graph = edge_array_calloc(node_ct);
  preference_graph_to_majority_graph(
    dvdata->preference_graph, majority_graph, node_ct);

  AggregateSolution *asol = aggregate_solution_create(node_ct);
  Davenport *dv = davenport_create(majority_graph, node_ct);
  davenport_set_solution_callback(dv, &aggregate_solution_add_solution, asol);
  davenport_compute(dv);
  dv = davenport_destroy(dv);

  int *r = aggregate_solution_ranking(asol);
  VALUE pref = rb_ary_new();
  for (int i = 0; i < node_ct; ++i) {
    rb_ary_push(pref, INT2NUM(r[i]));
  }

  asol = aggregate_solution_destroy(asol);
  free(majority_graph);
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
