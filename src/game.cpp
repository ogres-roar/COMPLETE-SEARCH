#include <functional>
#include "game.h"

Cell::Cell(int row, int column)
{
    row_ = row;
    column_ = column;
}

int Cell::getColumn()
{
    return column_;
}

int Cell::getRow()
{
    return row_;
}

Region::Region(int num_cells)
{
    num_cells_ = num_cells;
    matrix_ = vector<Cell>(num_cells);
}

vector<Cell> Region::getCells()
{
    return matrix_;
}

void Region::setCell(int pos, Cell cell)
{
    matrix_[pos] = cell;
}

Board::Board(int num_rows, int num_columns, int num_regions)
{
    num_rows_ = num_rows;
    num_columns_ = num_columns;
    num_regions_ = num_regions;
    values_ = vector<vector<int>>(num_rows, vector<int>(num_columns, 0));
    regions_ = vector<Region>(num_regions);
}

vector<vector<int>> Board::getValues()
{
    return values_;
}

int Board::getValue(int row, int column)
{
    return values_[row][column];
}

Region Board::getRegion(int index)
{
    return regions_[index];
}

vector<Region> Board::getRegions()
{
    return regions_;
}

void Board::setValue(int row, int column, int value)
{
    values_[row][column] = value;
}

void Board::setRegion(int index, Region region)
{
    regions_[index] = region;
}

void Board::setValues(vector<vector<int>> values)
{
    values_ = values;
}

vector<vector<int>> solver(Board board)
{
    // Is suduku finished?
    bool finish = false;
    function<void(int, int)> dfs;
    dfs = [&](int region_num, int index)
    {
        auto region = board.getRegion(region_num);
        auto n = region.getCells().size();
        auto cell = region.getCells()[index];
        bool changable = board.getValue(cell.getRow(), cell.getColumn()) == -1;

        if (!changable)
        {
            if (index < region.getCells().size() - 1)
            {
                dfs(region_num, index + 1);
            }
            else if (region_num < board.getRegions().size() - 1)
            {
                dfs(region_num + 1, 0);
            }
            else
            {
                finish = true;
                return;
            }
        }
        else
        {
            vector<bool> used(false, n);
            for (int i = 0; i < n; i++)
            {
                auto rcell = region.getCells()[i];
                auto value = board.getValue(rcell.getRow(), rcell.getColumn());
                if (value != -1)
                {
                    used[value - 1] = true;
                }
            }

            for (int i = 0; i < n; i++)
            {
                if (!used[i])
                {
                    used[i] = true;
                    board.setValue(cell.getRow(), cell.getColumn(), i + 1);
                    for (int j = -1; j < 2; j++)
                    {
                        for (int k = -1; k < 2; k++)
                        {
                            if (k == 0 && j == 0)
                            {
                                continue;
                            }
                            if (cell.getRow() + j < 0 || cell.getRow() + j >= board.getValues().size())
                            {
                                continue;
                            }
                            if (cell.getColumn() + k < 0 || cell.getColumn() + k >= board.getValues()[0].size())
                            {
                                continue;
                            }
                            if (board.getValues()[cell.getRow()][cell.getColumn()] == board.getValues()[cell.getRow() + j][cell.getColumn() + k])
                            {
                                used[i] = false;
                                board.setValue(cell.getRow(), cell.getColumn(), -1);
                                return;
                            }
                        }
                    }

                    if (index < region.getCells().size() - 1)
                    {
                        dfs(region_num, index + 1);
                    }
                    else if (region_num < board.getRegions().size() - 1)
                    {
                        dfs(region_num + 1, 0);
                    }
                    else
                    {
                        finish = true;
                        return;
                    }

                    if (finish)
                    {
                        return;
                    }

                    used[i] = false;
                    board.setValue(cell.getRow(), cell.getColumn(), -1);
                }
            }
        }
    };
    dfs(0, 0);
    return board.getValues();
}
