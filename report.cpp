/**
 * Generate report for an integration test.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

#include "data/data.h"
#include "match/match.h"

// helpers from match/match.cpp
double compatibilityScore(Profile, Profile);
template <class T>
double attributeScore(std::tuple<T, double>, std::tuple<T, double>);

// Return the compatibility score of two users identified by their IDs from a
// vector of profiles, return -1 if any of the IDs is not found in the vector
double compatibilityScore(uint32_t id0, uint32_t id1,
                          std::vector<Profile>& users) {
  Profile* user0Ptr = nullptr;
  Profile* user1Ptr = nullptr;
  for (auto& user : users) {
    if (user.id == id0) {
      user0Ptr = &user;
      break;
    }
  }
  for (auto& user : users) {
    if (user.id == id1) {
      user1Ptr = &user;
      break;
    }
  }
  if ((user0Ptr != nullptr) && (user1Ptr != nullptr)) {
    return compatibilityScore(*user0Ptr, *user1Ptr);
  } else {
    return -1;
  }
}

int main() {
  std::vector<Profile> users = profiles(100);
  std::map<uint32_t, uint32_t> pairs = Match::pairs(users);
  printf("-----------------------------------------------\n");
  printf("Male ID      Female ID      Compatibility Score\n");
  printf("-----------------------------------------------\n");
  for (auto& pair : pairs) {
    uint32_t maleID = pair.first;
    uint32_t femaleID = pair.second;
    printf("%-13d%-15d%lf\n", maleID, femaleID,
           compatibilityScore(maleID, femaleID, users));
  }
  printf("-----------------------------------------------\n");
}
