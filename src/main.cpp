#include <iostream>
#include <stdexcept>
#include <string>

#include "game.h"

using namespace std;

int main()
{
    int rows, columns;
    cin >> rows >> columns;
    vector<vector<int>> values(rows, vector<int>(columns, 0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            string value;
            cin >> value;
            if (value == "-")
            {
                values[i][j] = -1;
            }
            else
            {
                values[i][j] = stoi(value);
            }
        }
    }

    int regions;
    cin >> regions;

    Board board(rows, columns, regions);
    board.setValues(values);

    for (int i = 0; i < regions; i++)
    {
        int num_cells;
        cin >> num_cells;
        Region new_region(num_cells);
        for (int j = 0; j < num_cells; j++)
        {
            string cell;
            cin >> cell;
            string v1 = cell.substr(cell.find_first_of('(') + 1, cell.find_first_of(',') - cell.find_first_of('(') - 1);
            string v2 = cell.substr(cell.find_first_of(',') + 1, cell.find_first_of(')') - cell.find_first_of(',') - 1);
            Cell new_cell(stoi(v1) - 1, stoi(v2) - 1);
            new_region.setCell(j, new_cell);
        }
        board.setRegion(i, new_region);
    }

    auto answer = solver(board);
    for (int i = 0; i < answer.size(); i++)
    {
        for (int j = 0; j < answer[i].size(); j++)
        {
            cout << answer[i][j];
            if (j < answer[i].size() - 1)
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}