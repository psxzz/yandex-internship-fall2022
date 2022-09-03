#include <bits/stdc++.h>

using std::map;
using std::string;
using std::vector;

using log_map_t = map<int, int>;

struct log_record_t {
    int  day;
    int  hour;
    int  minutes;
    int  id;
    char status;
};

vector<int> getTotalTime(vector<log_record_t>& l);

int main() {
    int n = 0;
    std::cin >> n;

    vector<log_record_t> log(n);
    for (auto& r : log) {
        string day, hour, minutes, id, status;
        std::cin >> day >> hour >> minutes >> id >> status;

        r = {.day = atoi(day.data()),
             .hour = atoi(hour.data()),
             .minutes = atoi(minutes.data()),
             .id = atoi(id.data()),
             .status = status[0]};
    }

    auto res = getTotalTime(log);

    for (auto t : res) {
        printf("%d ", t);
    }

    return 0;
}

vector<int> getTotalTime(vector<log_record_t>& l) {
    vector<int> res;
    log_map_t   m;

    for (auto rec : l) {
        if (!m[rec.id]) m[rec.id] = 0;

        if (rec.status == 'A') {
            m[rec.id] -= (rec.day * 24 * 60 + rec.hour * 60 + rec.minutes);
        } else if (rec.status == 'C' || rec.status == 'S') {
            m[rec.id] += (rec.day * 24 * 60 + rec.hour * 60 + rec.minutes);
        }
    }

    for (auto it = m.begin(); it != m.end(); ++it) {
        res.push_back(it->second);
    }

    return res;
}
