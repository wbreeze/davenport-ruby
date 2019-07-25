Gem::Specification.new do |s|
  s.name = 'davenport'
  s.version = '1.0.1.pre'
  s.date = '2019-07-24'
  s.license = 'LGPL-3.0'
  s.summary = 'Ruby binding for the Davenport library'
  s.description = <<~DESCR.gsub("\n", ' ')
    Provides a Ruby interface for aggregating partial order expressions
    into a partial order with minimal Kemeny-Young distance
  DESCR
  s.author = 'Douglas Lovell <https://wbreeze.com/>'
  s.homepage = 'https://github.com/wbreeze/davenport-ruby'
  s.metadata = {
    'bug_tracker_uri' => 'https://github.com/wbreeze/davenport-ruby/issues',
    'changelog_uri' => 'https://github.com/wbreeze/davenport-ruby/pulls',
    'documentation_uri' => 'https://github.com/wbreeze/davenport-ruby',
    'homepage_uri' => 'https://github.com/wbreeze/davenport-ruby',
    'source_code_uri' => 'https://github.com/wbreeze/davenport-ruby'
  }
  s.files = [
    Dir.glob(File.join('lib', '**', '*.rb')),
    Dir.glob(File.join('ext', '**', '*.{rb,c,h}')),
    'README.rdoc',
    'Rakefile',
    'History.txt'
  ].flatten
  s.extensions << 'ext/davenport_ruby/extconf.rb'
  s.add_development_dependency 'rake-compiler', '~> 1.0'
  s.requirements << 'libdavenport'
end
