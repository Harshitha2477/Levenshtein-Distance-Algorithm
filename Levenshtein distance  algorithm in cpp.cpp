#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int min(int a, int b, int c) {
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

int levenshtein_distance(const string& s1, const string& s2) {
    int rows = s1.length() + 1;
    int cols = s2.length() + 1;
    vector<vector<int> > dist(rows, vector<int>(cols, 0));

    for (int i = 1; i < rows; i++)
        dist[i][0] = i;

    for (int j = 1; j < cols; j++)
        dist[0][j] = j;

    for (int col = 1; col < cols; col++) {
        for (int row = 1; row < rows; row++) {
            int cost = (s1[row - 1] == s2[col - 1]) ? 0 : 1;
            dist[row][col] = min(dist[row - 1][col] + 1,      // deletion
                                 dist[row][col - 1] + 1,      // insertion
                                 dist[row - 1][col - 1] + cost); // substitution
        }
    }

    return dist[rows - 1][cols - 1];
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    int num_inputs = lines.size() / 2;  
    for (int i = 0; i < num_inputs; i++) {
        string s1 = lines[i * 2];
        string s2 = lines[i * 2 + 1];
        s1.erase(remove(s1.begin(), s1.end(), '\n'), s1.end()); 
        s2.erase(remove(s2.begin(), s2.end(), '\n'), s2.end());

        int distance = levenshtein_distance(s1, s2);
        cout << "Levenshtein distance between '" << s1 << "' and '" << s2 << "' is: " << distance << endl;
    }

    return 0;
}

