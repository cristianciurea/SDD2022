//https://ro.wikipedia.org/wiki/Criptare
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

const int INF = INT_MAX / 2;

void func(string& s1) {
	for (int i = 0; i < s1.length(); i++) {
		s1[i] = tolower(s1[i]);
	}
}

int main() {
	set <pair <string, int>> ans;
	string::size_type k = 0;

	string s;
	int cnt = 1;
	while (getline(cin, s)) {
		s += " ";
		k = s.find(" ");
		while (k != string::npos) {

			string s1 = s.substr(0, k);
			func(s1);
			s.erase(0, k + 1);
			if (s1.length() == 0) {
				k = s.find(" ");
				continue;
			}
			bool f = false;
			set <pair <string, int>> ::iterator  it = ans.lower_bound(make_pair(s1, -INF));
			if (it != ans.end() && (*it).first == s1) {
				cout << (*it).second << ' ';
				f = true;
			}
			if (!f) {
				ans.insert(make_pair(s1, cnt));
				cout << cnt << ' ';
				cnt++;
			}
			k = s.find(" ");
		}
	}
	return 0;
}