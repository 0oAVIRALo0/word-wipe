#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <algorithm>
#include <iterator> 

using namespace std;

const int rows = 10;
const int columns = 10;

set<string> currentWords;
char grid[rows][columns];

vector<int> dr = {0, -1, 0, 1, -1, -1, 1, 1};
vector<int> dc = {-1, 0, 1, 0, -1, 1, -1, 1};

int generateRandomNumber(int n) {
    static std::random_device rd;   
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1); 

    return dis(gen); 
}

void removeElement(vector<int> &arr, int indexToRemove) {
    if (indexToRemove < 0 || indexToRemove >= arr.size()) {
        cerr << "Index out of bounds" << endl;
        return;
    }

    arr.erase(arr.begin() + indexToRemove);
}

void populateSet() {
    currentWords.insert("dashi");
    currentWords.insert("miso");
    currentWords.insert("tofu");
    currentWords.insert("tempura");
    currentWords.insert("ramen");
    currentWords.insert("sake");
    currentWords.insert("soba");
    currentWords.insert("umami");
    currentWords.insert("wasabi");
}

void constructGrid() {
    cout << "Constructing grid..." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j] = '-';
        }
    }
}

void fillGrid() {
    cout << "Filling grid..." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid[i][j] == '-') {
                grid[i][j] = 'a' + generateRandomNumber(26);
            }
        }
    }
}

void printGrid() {
    cout << "Printing grid..." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValid(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < columns && grid[r][c] == '-';
}

bool dfs(int r, int c, const string& word, int idx) {
    if (idx == word.size()) return true; 

    if (!isValid(r, c)) return false; 

    grid[r][c] = word[idx];
    cout << "row: " << r << " col: " << c << " letter: " << word[idx] << endl;

    vector<int> directions(dr.size());
    iota(directions.begin(), directions.end(), 0); 
    random_shuffle(directions.begin(), directions.end());

    for (int j : directions) {
        int newR = r + dr[j];
        int newC = c + dc[j];

        if (dfs(newR, newC, word, idx + 1)) {
            return true; 
        }
    }

    grid[r][c] = '-';
    return false;
}

int main() {
    populateSet();
    constructGrid();
    vector<string> words(currentWords.begin(), currentWords.end());
    shuffle(words.begin(), words.end(), std::mt19937{std::random_device{}()});\

    for (int i = 0; i < 3; i++) {
        cout << "Word: " << words[i] << endl;

        bool wordPlaced = false;
        int r = generateRandomNumber(rows);
        int c = generateRandomNumber(columns);
        if (grid[r][c] == '-') {
            wordPlaced = dfs(r, c, words[i], 0);
        }

        if (!wordPlaced) {
            cout << "Failed to place word: " << words[i] << endl;
        }
    }

    fillGrid();
    printGrid();

    return 0;
}
