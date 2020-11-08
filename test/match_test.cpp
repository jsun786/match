/**
 * Unit tests for match.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "match/match.h"

#include <gtest/gtest.h>

#include "data/data.h"

// Test if the pairs are all male to female
TEST(Match, pair0) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.2},
                         {false, 0.3},
                         {ENGLISH, 0.4},
                         {CHRISTIAN, 0.5},
                         {false, 0.6}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {CANADA, 0.6},
                         {NONVEGETARIAN, 0.5},
                         {false, 0.4},
                         {ENGLISH, 0.3},
                         {CHRISTIAN, 0.2},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(int(pairs.count(uint32_t(100000))), 1);
  EXPECT_EQ(int(pairs.count(uint32_t(100002))), 1);
  EXPECT_EQ(int(pairs.size()), 2);
  std::map<uint32_t, uint32_t> femaleMalePairs;
  for (auto& pair : pairs) {
    femaleMalePairs[pair.second] = pair.first;
  };
  EXPECT_EQ(int(femaleMalePairs.count(uint32_t(100001))), 1);
  EXPECT_EQ(int(femaleMalePairs.count(uint32_t(100003))), 1);
}

// Test if the users are correctly paired by country
TEST(Match, pair1) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {USA, 0.3},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.2},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(pairs[100000], uint32_t(100001));
  EXPECT_EQ(pairs[100002], uint32_t(100003));
}

// Test if the users are correctly paired by diet
TEST(Match, pair2) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {VEGAN, 0.3},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.2},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(pairs[100000], uint32_t(100001));
  EXPECT_EQ(pairs[100002], uint32_t(100003));
}

// Test if the users are correctly paired by drinking
TEST(Match, pair3) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {true, 0.2},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.2},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(pairs[100000], uint32_t(100001));
  EXPECT_EQ(pairs[100002], uint32_t(100003));
}

// Test if the users are correctly paired by language
TEST(Match, pair4) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {FRENCH, 0.3},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.2},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.2},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(pairs[100000], uint32_t(100001));
  EXPECT_EQ(pairs[100002], uint32_t(100003));
}

// Test if the users are correctly paired by religion
TEST(Match, pair5) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.2},
                         {false, 0.1}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {JEWISH, 0.3},
                         {false, 0.1}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(pairs[100000], uint32_t(100001));
  EXPECT_EQ(pairs[100002], uint32_t(100003));
}

// Test if the users are correctly paired by smoking
TEST(Match, pair6) {
  std::vector<Profile> userProfiles;
  userProfiles.push_back({100000,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.2}});
  userProfiles.push_back({100001,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100002,
                         MALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {false, 0.1}});
  userProfiles.push_back({100003,
                         FEMALE,
                         {CANADA, 0.1},
                         {NONVEGETARIAN, 0.1},
                         {false, 0.1},
                         {ENGLISH, 0.1},
                         {CHRISTIAN, 0.1},
                         {true, 0.3}});

  std::map<uint32_t, uint32_t> pairs = Match::pairs(userProfiles);
  EXPECT_EQ(pairs[100000], uint32_t(100001));
  EXPECT_EQ(pairs[100002], uint32_t(100003));
}