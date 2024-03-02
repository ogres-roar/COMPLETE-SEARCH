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

int Board::getRows()
{
    return num_rows_;
}

int Board::getColumns()
{
    return num_columns_;
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

        function<void()> setValue;
        setValue = [&]()
        {
            vector<bool> used(n, false);
            for (int i = 0; i < n; i++)
            {
                auto rcell = region.getCells()[i];
                auto value = board.getValue(rcell.getRow(), rcell.getColumn());
                if (value != -1)
                {
                    used[value - 1] = true;
                }
            }

            for (int num = 0; num < n; num++)
            {
                if (used[num])
                {
                    continue;
                }
                board.setValue(cell.getRow(), cell.getColumn(), num + 1);
                used[num] = true;
                for (int i = -1; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        if (i == 0 && j == 0)
                        {
                            continue;
                        }
                        if (cell.getRow() + i < 0 || cell.getRow() + i >= board.getRows())
                        {
                            continue;
                        }
                        if (cell.getColumn() + j < 0 || cell.getColumn() + j >= board.getColumns())
                        {
                            continue;
                        }
                        if (board.getValue(cell.getRow(), cell.getColumn()) ==
                            board.getValue(cell.getRow() + i, cell.getColumn() + j))
                        {
                            board.setValue(cell.getRow(), cell.getColumn(), -1);
                            used[num] = false;
                            break;
                        }
                    }
                }

                if (used[num])
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
                if (finish)
                {
                    return;
                }
                used[num] = false;
                board.setValue(cell.getRow(), cell.getColumn(), -1);
            }
            return;
        };

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
            setValue();
        }
    };
    dfs(0, 0);
    return board.getValues();
}
