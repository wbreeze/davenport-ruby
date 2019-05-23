require "minitest/autorun"
require "davenport"

class TestDavenport < Minitest::Test
  def test_sanity
    refute_nil(Davenport::VERSION)
  end

  def test_one_ranking
    node_ct = 4;
    pg = Davenport::PreferenceGraph.new(node_ct)
    expected_ranking = [1, 3, 2, 4];
    pg.add_preference(expected_ranking);
    assert_equal(expected_ranking, pg.davenport);
  end

  def test_constructor_type_error
    assert_raises(TypeError) do
      Davenport::PreferenceGraph.new(Object.new)
    end
  end

  def test_add_preference_type_error
    pg = Davenport::PreferenceGraph.new(4)
    assert_raises(TypeError) do
      pg.add_preference(Object.new)
    end
  end

  def test_add_preference_array_type_error
    pg = Davenport::PreferenceGraph.new(3)
    assert_raises(TypeError) do
      a = [Object.new, Object.new, Object.new];
      pg.add_preference(a)
    end
  end

  def test_add_preference_array_length_error
    pg = Davenport::PreferenceGraph.new(3)
    assert_raises(Davenport::PreferenceGraphCountException) do
      a = [1, 1];
      pg.add_preference(a)
    end
  end
end
