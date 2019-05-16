# -*- ruby -*-

require 'rubygems'
require 'hoe'
require 'rake/extensiontask'

# Hoe.plugin :compiler
# Hoe.plugin :gem_prelude_sucks
# Hoe.plugin :inline
# Hoe.plugin :minitest
# Hoe.plugin :racc
# Hoe.plugin :rcov
# Hoe.plugin :rdoc

HOE = Hoe.spec "davenport" do
  developer("Douglas Lovell", "doug@wbreeze.com")
  license "LGPL-3.0"
  self.spec_extras = {
    extensions: ['ext/davenport/extconf.rb']
  }
end

Rake::ExtensionTask.new('davenport', HOE.spec) do |ext|
  ext.lib_dir = File.join('lib', 'davenport')
end

Rake::Task[:test].prerequisites << :compile

# vim: syntax=ruby
