#include <ruby.h>
#include "davenport/davenport.h"
#include "davenport/network.h"
#include "extconf.h"

static VALUE initialize(VALUE self, VALUE node_ct)
{
  Check_Type(node_ct, T_FIXNUM);
  return self;
}

VALUE add_preference(VALUE self, VALUE pref_array)
{
  Check_Type(pref_array, T_ARRAY);
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
  VALUE cPg = rb_define_class_under(mDv, "PreferenceGraph", rb_cObject);
  rb_define_method(cPg, "initialize", initialize, 1);
  rb_define_method(cPg, "add_preference", add_preference, 1);
  rb_define_method(cPg, "davenport", davenport, 0);
}
