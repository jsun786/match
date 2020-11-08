/**
 * Implementation for Match.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "match/match.h"

#include <algorithm>   // std::find, std::sort
#include <map>
#include <utility>  // std::pair, std::make_pair
#include <vector>

// Declarations of helper functions
double compatibilityScore(Profile, Profile);
template <class T>
double attributeScore(std::tuple<T, double>, std::tuple<T, double>);

// Return a map of male-female pairs representing the best compatibility
// among all the users, if by any chance there are pairs with the same
// compatibility score, the pair in which the users appear first in the profile
// vector will be kept. Pairs are sorted in the alphabetical order of the
// males' IDs
std::map<uint32_t, uint32_t> Match::pairs(std::vector<Profile>& profiles) {
  std::vector<Profile*> males;
  std::vector<Profile*> females;
  std::vector<std::pair<std::pair<Profile*, Profile*>, double>> allCombinations;
  // A map is by default sorted by std::less on the key values, so the map
  // is automatically sorted alphabetically by male IDs. If there is need to
  // sort in another order, either specify a comparator function in the map
  // declaration (which in this project requires changes in the header file),
  // or export the pairs of the map into another container to sort, such as
  // a vector
  std::map<uint32_t, uint32_t> result;
  for (auto& profile : profiles) {
    profile.gender == MALE ? males.push_back(&profile)
                           : females.push_back(&profile);
  }
  for (auto& male : males) {
    for (auto& female : females) {
      allCombinations.push_back(
          {{male, female}, compatibilityScore(*male, *female)});
    }
  }
  // sort the vector so it starts from the greatest compatibility score to the
  // lowest, a lambda expression is used for the comparator function
  std::sort(allCombinations.begin(), allCombinations.end(),
            [](const std::pair<std::pair<Profile*, Profile*>, double>& pair0,
               const std::pair<std::pair<Profile*, Profile*>, double>& pair1) {
              return pair0.second > pair1.second;
            });
  while (!(allCombinations.empty())) {
    uint32_t firstMaleID = allCombinations[0].first.first->id;
    uint32_t firstFemaleID = allCombinations[0].first.second->id;
    result.insert({firstMaleID, firstFemaleID});
    for (int i = 0; i < int(allCombinations.size());) {
      if ((allCombinations[i].first.first->id == firstMaleID) ||
          (allCombinations[i].first.second->id == firstFemaleID)) {
        allCombinations.erase(allCombinations.begin() + i);
      } else {
        i++;
      }
    }
  }
  return result;
}

// Return the compatibility score of two users
double compatibilityScore(Profile profile0, Profile profile1) {
  double score = 0;
  score += attributeScore(profile0.country, profile1.country);
  score += attributeScore(profile0.diet, profile1.diet);
  score += attributeScore(profile0.drinking, profile1.drinking);
  score += attributeScore(profile0.language, profile1.language);
  score += attributeScore(profile0.religion, profile1.religion);
  score += attributeScore(profile0.smoking, profile1.smoking);
  return score;
}

// Return the sum of the weights of an attribute from two users if they
// match, otherwise return 0
template <class T>
double attributeScore(std::tuple<T, double> attribute0,
                      std::tuple<T, double> attribute1) {
  if (std::get<0>(attribute0) == std::get<0>(attribute1)) {
    return (std::get<1>(attribute0) + std::get<1>(attribute1));
  } else {
    return 0;
  }
}