#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            int len = board.size();

            // line
            for(auto && str : board) {
                map<char, int> hash;
                for (auto && c : str) {
                    if (c == '.') continue;
                    if (hash.count(c) > 0) return false;
                    hash[c] = 1;
                }
            }

            // row
            for(int i =0; i< len; i++) {
                map<char, int> hash;
                for (int j =0 ;j< len; j++) {
                    char c = board[j][i];
                    if (c == '.') continue;
                    if (hash.count(c) > 0) return false;
                    hash[c] = 1;
                }
            }

            // 9
            vector<int> range = {0,3,6};
            for ( auto &&r: range) {
                for (auto && rr: range) {
                    map<char, int> hash;
                    for (int i=r+0; i<r+3; i++) {
                        for (int j =rr+0; j<rr+3; j++) {
                            char c = board[i][j];
                            if (c == '.') continue;
                            if (hash.count(c) > 0) return false;
                            hash[c] = 1;
                        }
                    }
                }
            }

            return true;
        }
};

int main() {
    Solution o;
    {
        vector<string> input = {"....5..1.",".4.3.....",".....3..1","8......2.","..2.7....",".15......",".....2...",".2.9.....","..4......"};
        vector<vector<char>>board;
        int i =0;
        for(auto str : input) {
            board.push_back(vector<char>{});
            for (auto c: str) {
                board[i].push_back(c);
            }
            i++;
        }

        cout << o.isValidSudoku(board)<<endl;
    }

    {
        vector<string> input = {".87654321","2........","3........","4........","5........","6........","7........","8........","9........"};
        vector<vector<char>>board;
        int i =0;
        for(auto str : input) {
            board.push_back(vector<char>{});
            for (auto c: str) {
                board[i].push_back(c);
            }
            i++;
        }

        cout << o.isValidSudoku(board)<<endl;
    }
    return 0;
}
