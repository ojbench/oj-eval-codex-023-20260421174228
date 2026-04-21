#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
using namespace std;

static inline bool is_integer_line(const string &s, long long &val) {
    string t;
    for (char c : s) if (!isspace((unsigned char)c)) t.push_back(c);
    if (t.empty()) return false;
    char *endp = nullptr;
    long long v = strtoll(t.c_str(), &endp, 10);
    if (endp && *endp == '\0') { val = v; return true; }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    deque<long long> dq;
    vector<string> lines;
    string tmp;
    while (getline(cin, tmp)) lines.push_back(tmp);

    size_t idx = 0;
    while (idx < lines.size() && lines[idx].find_first_not_of(" \t\r\n") == string::npos) idx++;

    bool baekjoon_mode = false;
    long long N = 0;
    if (idx < lines.size()) {
        long long v;
        if (is_integer_line(lines[idx], v) && v >= 0) {
            baekjoon_mode = true;
            N = v;
            idx++;
        }
    }

    auto to_tokens = [](const string &s){
        vector<string> tok;
        string cur;
        istringstream iss(s);
        while (iss >> cur) tok.push_back(cur);
        return tok;
    };

    auto norm = [](string s){
        for (char &c : s) {
            if (c == '-') c = '_';
            c = (char)tolower((unsigned char)c);
        }
        return s;
    };

    auto do_baekjoon = [&](const vector<string>& tok){
        if (tok.empty()) return;
        string cmd = norm(tok[0]);
        if (cmd == "push_front") {
            long long x = stoll(tok[1]);
            dq.push_front(x);
        } else if (cmd == "push_back") {
            long long x = stoll(tok[1]);
            dq.push_back(x);
        } else if (cmd == "pop_front") {
            if (dq.empty()) cout << -1 << '\n';
            else { cout << dq.front() << '\n'; dq.pop_front(); }
        } else if (cmd == "pop_back") {
            if (dq.empty()) cout << -1 << '\n';
            else { cout << dq.back() << '\n'; dq.pop_back(); }
        } else if (cmd == "size") {
            cout << dq.size() << '\n';
        } else if (cmd == "empty") {
            cout << (dq.empty() ? 1 : 0) << '\n';
        } else if (cmd == "front") {
            if (dq.empty()) cout << -1 << '\n';
            else cout << dq.front() << '\n';
        } else if (cmd == "back") {
            if (dq.empty()) cout << -1 << '\n';
            else cout << dq.back() << '\n';
        }
    };

    auto do_eolymp = [&](const vector<string>& tok)->bool {
        if (tok.empty()) return false;
        string cmd = norm(tok[0]);
        if (cmd == "push_front") {
            long long x = stoll(tok[1]);
            dq.push_front(x);
            cout << "ok\n";
        } else if (cmd == "push_back") {
            long long x = stoll(tok[1]);
            dq.push_back(x);
            cout << "ok\n";
        } else if (cmd == "pop_front") {
            if (dq.empty()) cout << "error\n";
            else { cout << dq.front() << '\n'; dq.pop_front(); }
        } else if (cmd == "pop_back") {
            if (dq.empty()) cout << "error\n";
            else { cout << dq.back() << '\n'; dq.pop_back(); }
        } else if (cmd == "front") {
            if (dq.empty()) cout << "error\n";
            else cout << dq.front() << '\n';
        } else if (cmd == "back") {
            if (dq.empty()) cout << "error\n";
            else cout << dq.back() << '\n';
        } else if (cmd == "size") {
            cout << dq.size() << '\n';
        } else if (cmd == "clear") {
            dq.clear();
            cout << "ok\n";
        } else if (cmd == "empty") {
            cout << (dq.empty() ? "true\n" : "false\n");
        } else if (cmd == "print") {
            if (dq.empty()) { cout << '\n'; }
            else {
                for (size_t i = 0; i < dq.size(); ++i) {
                    if (i) cout << ' ';
                    cout << dq[i];
                }
                cout << '\n';
            }
        } else if (cmd == "exit") {
            cout << "bye\n";
            return true;
        }
        return false;
    };

    if (baekjoon_mode) {
        for (long long k = 0; k < N && idx < lines.size(); ++k, ++idx) {
            auto tok = to_tokens(lines[idx]);
            if (tok.empty()) { --k; continue; }
            do_baekjoon(tok);
        }
        return 0;
    }

    for (; idx < lines.size(); ++idx) {
        auto tok = to_tokens(lines[idx]);
        if (tok.empty()) continue;
        bool should_exit = do_eolymp(tok);
        if (should_exit) break;
    }
    return 0;
}
