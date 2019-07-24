Gem::Specification.new do |s|
  s.name = 'davenport'
  s.version = '1.0.1'
  s.date = '2019-07-24'
  s.summary = 'Ruby binding for the Davenport library'
  s.description = <<~DESCR
    Provides a Ruby interface for aggregating partial order expressions
    into a partial order with minimal Kemeny-Young distance
  DESCR
  s.authors = ['Douglas Lovell <https://wbreeze.com/>']
  s.files = [
    Dir.glob(File.join('lib', '**', '*.rb')),
    Dir.glob(File.join('ext', '**', '*.{rb,c,h}')),
    'README.rdoc',
    'Rakefile'
  ].flatten
  s.extensions = %w(ext/davenport/extconf.rb)
  s.add_development_dependency 'rake-compiler', '~> 1'
  s.license = 'LGPL-3.0'
end
