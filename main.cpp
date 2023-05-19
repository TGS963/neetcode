#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <typeinfo>

using namespace std;

class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        return nums.size() > unordered_set<int>(nums.begin(), nums.end()).size();
    }
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
        {
            return false;
        }
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i)
        {
            int complement = target - nums[i];
            if (map.find(complement) != map.end())
            {
                return {map[complement], i};
            }
            map[nums[i]] = i;
        }
        return {};
        // for (int i = 0; i < nums.size(); ++i)
        // {
        //     int complement = target - nums[i];
        //     for (int j = i + 1; j < nums.size(); ++j)
        //     {
        //         if (nums[j] == complement)
        //         {
        //             return {i, j};
        //         }
        //     }
        // }
        // return {};
    }
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> map;
        for (int i = 0; i < strs.size(); ++i)
        {
            string temp = strs[i];
            sort(temp.begin(), temp.end());
            map[temp].push_back(strs[i]);
        }
        vector<vector<string>> v;
        for (auto i : map)
        {
            v.push_back(i.second);
        }
        return v;
    }
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> map;
        for (auto i : nums)
        {
            map[i]++;
        }
        vector<vector<int>> v;
        for (auto i : map)
        {
            v.push_back({i.second, i.first});
        }
        sort(v.rbegin(), v.rend());
        vector<int> res;
        for (int i = 0; i < k; ++i)
        {
            res.push_back(v[i][1]);
        }
        return res;
    }
    vector<int> productExceptSelf(vector<int> &nums)
    {
        /*
        [a, b, c, d]

1 [a, 					a*b, 		a*b*c, a*b*c*d]

  [a*b*c*d, b*c*d, c*d, 		d]       1

[b*c*d, a*c*d, a*b*d, a*b*c]
        */
        int n = nums.size();
        vector<int> result(n, 1);
        int prefix = 1;
        int postfix = 1;
        vector<int> prefix_arr;
        vector<int> postfix_arr(n, 1);
        for (int i = 0; i < n; i++)
        {
            prefix_arr.push_back(nums[i] * prefix);
            prefix *= nums[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            postfix_arr[i] = nums[i] * postfix;
            postfix *= nums[i];
        }
        for (int i = 0; i < n; ++i)
        {
            if (i == 0)
                result[i] = 1 * postfix_arr[i + 1];
            else if (i == n - 1)
                result[i] = prefix_arr[i - 1] * 1;
            else
                result[i] = prefix_arr[i - 1] * postfix_arr[i + 1];
        }

        return result;
    }
    bool isValidSudoku(vector<vector<char>> &board)
    {
        int row_elements = 0;
        int col_elements = 0;
        int box_elements = 0;

        unordered_set<int> row;
        unordered_set<int> col;
        unordered_set<int> box;

        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (j % 3 == 0)
                {
                    if (box.size() != box_elements)
                        return false;

                    box.clear();
                    box_elements = 0;
                }
                if (i % 3 == 0)
                {
                    if (board[i][j] != '.')
                    {
                        box.insert(board[i][j]);
                        box_elements++;
                    }
                    if (board[i + 1][j] != '.')
                    {
                        box.insert(board[i + 1][j]);
                        box_elements++;
                    }
                    if (board[i + 2][j] != '.')
                    {
                        box.insert(board[i + 2][j]);
                        box_elements++;
                    }
                }
                if (board[i][j] != '.')
                {
                    row_elements++;
                    row.insert(board[i][j]);
                }
                if (board[j][i] != '.')
                {
                    col_elements++;
                    col.insert(board[j][i]);
                }
            }
            if (row_elements != row.size() || col_elements != col.size())
                return false;
            row_elements = 0;
            col_elements = 0;
            row.clear();
            col.clear();
        }

        return true;
    }
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        sort(nums.begin(), nums.end());
        int sequence_length = 0;
        int max_length = 0;
        for (const int &i : nums)
        {
            cout << i - 1 << " ";
        }
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i != 0)
            {
                if (nums[i] - nums[i - 1] == 1)
                {
                    sequence_length++;
                }
                else
                {
                    if (max_length <= sequence_length)
                        max_length = sequence_length;
                    sequence_length = 0;
                }
                if (max_length <= sequence_length)
                    max_length = sequence_length;
            }
        }
        return max_length + 1;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {1, 2, 0, 1};
    int ole = solution.longestConsecutive(nums);
    cout << "Longest: " << ole << endl;
    return 0;
}