require "minitest/autorun"
require "davenport"

class TestDavenport < Minitest::Test
  def test_sanity
    refute_nil(Davenport::VERSION)
  end

  def test_one_ranking
    node_ct = 4;
    pg = Davenport::PreferenceGraph.new  #(node_ct)
    expected_ranking = [1, 3, 2, 4];
    pg.add_preference(expected_ranking);
    assert_equal(expected_ranking, pg.davenport);
  end
end
