//https://gist.github.com/jacky860226/c436c68beb07782ba91306544a392d9e
#include<vector>
#include<string>
#include<map>
#include<iostream>
using namespace std;

vector<int> encode(const string& ori) {
	map<string, int> dict;
	int dictSize = 256;
	for (int i = 0; i < dictSize; ++i)
		dict[string(1, i)] = i;
	vector<int> res;
	string s;
	for (char z : ori) {
		if (dict.count(s + z)) s += z;
		else {
			res.emplace_back(dict[s]);
			dict[s + z] = dictSize++;
			s = z;
		}
	}
	if (s.size()) res.emplace_back(dict[s]);
	return res;
}

string decode(const vector<int>& v) {
	map<int, string> inv_dict;
	int dictSize = 256;
	for (int i = 0; i < dictSize; ++i)
		inv_dict[i] = string(1, i);
	string s, entry, res;
	s = res = inv_dict[v[0]];
	for (size_t i = 1; i < v.size(); ++i) {
		int k = v[i];
		if (inv_dict.count(k))
			entry = inv_dict[k];
		else if (k == dictSize)
			entry = s + s[0];
		else throw "error";
		res += entry;
		inv_dict[dictSize++] = s + entry[0];
		s = entry;
	}
	return res;
}

void main()
{
	const string s = "ANNAABBAABABBAAAABAABBA";
	vector<int> vect = encode(s);
	string s2 = decode(vect);
	for (int i = 0; i < vect.size(); i++)
		cout << vect[i] << " ";
	cout << endl;
	cout << s2;
}