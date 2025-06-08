#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  // Find whitespace
  std::vector<std::string::iterator> whitespace = find_all(source.begin(), source.end(), 
                                                          [](char c) { return std::isspace(static_cast<unsigned char>(c)); });
  // Initialize corpus
  Corpus tokens;

  // Define lambda function
  auto buildToken = [&source] (std::string::iterator it1, std::string::iterator it2) {
    return Token(source, it1, it2);
  };

  // Build tokens and store
  std::transform(whitespace.begin(), whitespace.end() - 1, whitespace.begin() + 1, std::inserter(tokens, tokens.end()), buildToken);

  // Delete empty tokens
  auto isEmpty = [] (Token token) {return token.content.empty();};
  std::erase_if(tokens, isEmpty);

  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  // Filter out misspelled words
  auto view = source 
      | std::ranges::views::filter([&dictionary] (Token token) {
        return !dictionary.contains(token.content);
      }) 
      | std::ranges::views::transform([&dictionary] (Token token) {
        // Nest a filter
        auto view_sug = dictionary | std::ranges::views::filter([&token] (const std::string& word) {
          return levenshtein(word, token.content) == 1;
        });
        // Create a set
        std::set<std::string> suggestions(view_sug.begin(), view_sug.end());
        return Misspelling{token, suggestions};
      })
      | std::ranges::views::filter([] (Misspelling x) {
        return !x.suggestions.empty();
      });

  return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"
