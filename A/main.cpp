#include <bits/stdc++.h>

using std::string;
using std::unordered_set;
using std::vector;

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct cand_info_t {
    string surname;
    string name;
    string secondName;
    int    day, month, year;
};

cand_info_t parseCandInfo(string& s);
string      encodeCandidate(cand_info_t& c);

int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    vector<cand_info_t> candidates(n);
    vector<string>      encoded;
    for (auto& s : candidates) {
        string str;
        std::cin >> str;
        s = parseCandInfo(str);
        encoded.push_back(encodeCandidate(s));
    }

    for (auto c : encoded) {
        // std::cout << c << " ";
        printf("%s ", c.data());
    }

    return 0;
}

cand_info_t parseCandInfo(string& s) {
    std::stringstream ss(s);
    cand_info_t       candidate = {};
    getline(ss, candidate.surname, ',');
    getline(ss, candidate.name, ',');
    getline(ss, candidate.secondName, ',');

    string d, m, y;
    getline(ss, d, ',');
    getline(ss, m, ',');
    getline(ss, y, ',');

    candidate.day = atoi(d.data());
    candidate.month = atoi(m.data());
    candidate.year = atoi(y.data());

    return candidate;
}

string encodeCandidate(cand_info_t& c) {
    unordered_set<char> cs;
    int                 uniqueChars = 0;
    int                 dateSum = 0;
    int                 alphIdx = 0;

    auto getUnique = [&cs](string s) {
        for (auto ch : s) cs.insert(ch);
    };

    auto getDateSum = [&dateSum](int i) {
        while (i > 0) {
            dateSum += i % 10;
            i /= 10;
        }
    };

    getUnique(c.surname);
    getUnique(c.name);
    getUnique(c.secondName);
    uniqueChars = cs.size();

    getDateSum(c.day);
    getDateSum(c.month);
    alphIdx = (c.surname[0] - 'A') + 1;

    int resultDec = uniqueChars + (dateSum * 64) + (alphIdx * 256);

    char hex[20];
    sprintf(hex, "%X", resultDec);

    string resultHex(hex);

    if (resultHex.length() < 4) {
        int    lsize = 4 - resultHex.length();
        string leadingZeros(lsize, '0');
        resultHex = leadingZeros + resultHex;
    }

    resultHex.erase(resultHex.begin());

    return resultHex;
}
