#include "../templates/base_template.hpp"

auto string_split = [](const string &s, const string &delims) {
  size_t prv = 0, pos;
  vector<string> parsed;
  while ((pos = s.find_first_of(delims, prv)) != string::npos) {
    if (pos > prv) parsed.push_back(s.substr(prv, pos - prv));
    prv = pos + 1;
  }
  if (prv < size(s)) parsed.push_back(s.substr(prv, string::npos));
  return parsed;
};
