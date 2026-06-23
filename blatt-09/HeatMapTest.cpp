// Copyright 2026, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//         Christoph Ullinger <ullingec@cs.uni-freiburg.de>

#include "./HeatMap.h"
#include <gtest/gtest.h>

// ___________________________________________________________________________
TEST(HeatMap, ReadPointsFromFile) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");

  const auto &p = heatMap.points();
  ASSERT_EQ(6u, p.size());

  ASSERT_FLOAT_EQ(0.0, p[0].longitude_);
  ASSERT_FLOAT_EQ(0.0, p[0].latitude_);

  ASSERT_FLOAT_EQ(6.0, p[5].longitude_);
  ASSERT_FLOAT_EQ(4.0, p[5].latitude_);
}

// ___________________________________________________________________________
TEST(HeatMap, ComputeHeatMapMaxWidth) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");
  heatMap.computeHeatMap(6, 3, 1.0f);

  const auto &m = heatMap.heatMap();
  ASSERT_EQ(5u, m.size());

  ASSERT_TRUE(m.count(Cell{3, 0}));
  ASSERT_TRUE(m.count(Cell{3, 2}));
  ASSERT_TRUE(m.count(Cell{1, 0}));
  ASSERT_TRUE(m.count(Cell{1, 2}));
  ASSERT_EQ(2u, m.at(Cell{1, 2}));
  ASSERT_TRUE(m.count(Cell{2, 1}));
}

// ___________________________________________________________________________
TEST(HeatMap, ComputeHeatMapMaxHeight) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");
  heatMap.computeHeatMap(3, 6, 1.0f);

  const auto &m = heatMap.heatMap();
  ASSERT_EQ(5u, m.size());

  ASSERT_TRUE(m.count(Cell{2, 0}));
  ASSERT_TRUE(m.count(Cell{2, 4}));
  ASSERT_TRUE(m.count(Cell{0, 0}));
  ASSERT_TRUE(m.count(Cell{0, 4}));
  ASSERT_EQ(2u, m.at(Cell{0, 4}));
  ASSERT_TRUE(m.count(Cell{1, 2}));
}

// ___________________________________________________________________________
TEST(HeatMap, ComputeHeatMapAspectRatio) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");
  heatMap.computeHeatMap(6, 3, 0.5f);

  const auto &m = heatMap.heatMap();
  ASSERT_EQ(5u, m.size());

  ASSERT_TRUE(m.count(Cell{4, 0}));
  ASSERT_TRUE(m.count(Cell{4, 2}));
  ASSERT_TRUE(m.count(Cell{0, 0}));
  ASSERT_TRUE(m.count(Cell{0, 2}));
  ASSERT_EQ(2u, m.at(Cell{0, 2}));
  ASSERT_TRUE(m.count(Cell{2, 1}));
}
