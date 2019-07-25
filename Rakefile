require 'rubygems'
require 'rake/extensiontask'

spec = Gem::Specification.load('davenport.gemspec')

Rake::ExtensionTask.new "davenport", spec do |ext|
  ext.name = 'davenport_ruby'
  ext.lib_dir = 'lib/davenport'
end
