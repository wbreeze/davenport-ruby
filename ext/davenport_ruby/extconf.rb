#! ruby
require 'mkmf'

unless have_library('davenport', 'preference_graph_add_preference')
  abort 'Need libdavenport, see https://github.com/wbreeze/davenport'
end

create_header
create_makefile 'davenport/davenport_ruby'
