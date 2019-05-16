require "minitest/autorun"
require "davenport"

class TestDavenport < Minitest::Test
  def test_sanity
    refute_nil(Davenport::VERSION)
  end
end
