#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include "game.h"

vector<vector<int>> getValues(int row, int column)
{
    return vector<vector<int>>(row, vector<int>(column, -1));
}

vector<Region> getRegions(string content)
{
    vector<Region> regions;
    stringstream scontent(content);
    string item;

    while (getline(scontent, item, '\n'))
    {
        stringstream sitem(item);
        string ssize;
        sitem >> ssize;
        auto size = stoi(ssize);
        Region region(size);
        for (int i = 0; i < size; i++)
        {
            string cell;
            sitem >> cell;
            string v1 = cell.substr(cell.find_first_of('(') + 1, cell.find_first_of(',') - cell.find_first_of('(') - 1);
            string v2 = cell.substr(cell.find_first_of(',') + 1, cell.find_first_of(')') - cell.find_first_of(',') - 1);
            Cell new_cell(stoi(v1) - 1, stoi(v2) - 1);
            region.setCell(i, new_cell);
        }
        regions.push_back(region);
    }
    return regions;
}

vector<vector<int>> getResult(string content)
{
    vector<vector<int>> result;
    stringstream scontent(content);
    string item;
    while (getline(scontent, item, '\n'))
    {
        stringstream sitem(item);
        string scount;
        sitem >> scount;
        auto count = stoi(scount);
        vector<int> row;
        for (int i = 0; i < count; i++)
        {
            string word;
            sitem >> word;
            row.push_back(stoi(word));
        }
        result.push_back(row);
    }
    return result;
}

TEST(GameTest, test1)
{
    int row = 3;
    int column = 5;
    int region_num = 5;

    auto values = getValues(row, column);
    values[2][0] = 4;
    values[2][4] = 1;

    Board board(row, column, region_num);
    vector<Region> regions = getRegions("1 (1,1)\n2 (1,2) (1,3)\n5 (2,1) (2,2) (3,1) (3,2) (3,3)\n4 (2,3) (2,4) (1,4) (1,5)\n3 (3,4) (3,5) (2,5)");

    for (int i = 0; i < regions.size(); i++)
    {
        board.setRegion(i, regions[i]);
    }

    auto answer = solver(board);
    vector<vector<int>> res = getResult("5 1 2 1 2 1\n5 3 5 3 4 3\n5 4 2 1 2 1");
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
        {
            EXPECT_EQ(answer[i][j], res[i][j]);
        }
    }
}

TEST(GameTest, test2)
{
    int row = 7;
    int column = 7;
    int region_num = 14;

    auto values = getValues(row, column);
    values[1][0] = 4;
    values[1][5] = 5;
    values[3][3] = 3;

    Board board(row, column, region_num);
    vector<Region> regions = getRegions("5 (1,1) (2,1) (3,1) (2,2) (2,3)\n4 (2,4) (1,2) (1,3) (1,4)\n2 (1,5) (1,6)\n1 (1,7)\n4 (4,1) (5,1) (6,1) (5,2)\n1 (7,1)\n4 (3,2) (4,2) (4,3) (5,3)\n3 (7,3) (7,2) (6,2)\n4 (6,3) (6,4) (7,4) (7,5)\n6 (2,5) (3,5) (4,5) (3,6) (2,6) (2,7)\n4 (3,7) (4,7) (4,6) (5,6)\n1 (5,7)\n5 (7,7) (7,6) (6,7) (6,6) (6,5)\n5 (3,3) (3,4) (4,4) (5,4) (5,5)");

    for (int i = 0; i < regions.size(); i++)
    {
        board.setRegion(i, regions[i]);
    }

    auto answer = solver(board);
    vector<vector<int>> res = getResult("5 1 2 1 2 1\n5 3 5 3 4 3\n5 4 2 1 2 1");
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
        {
            EXPECT_EQ(answer[i][j], res[i][j]);
        }
    }
}

TEST(GameTest, test3)
{
    int row = 1;
    int column = 1;
    int region_num = 1;

    auto values = getValues(row, column);

    Board board(row, column, region_num);
    vector<Region> regions = getRegions("1 (1,1)");

    for (int i = 0; i < regions.size(); i++)
    {
        board.setRegion(i, regions[i]);
    }

    auto answer = solver(board);
    vector<vector<int>> res = getResult("1 1");
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
        {
            EXPECT_EQ(answer[i][j], res[i][j]);
        }
    }
}