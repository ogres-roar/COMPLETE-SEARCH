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
    // todo Please start coding your solution here
    return board.getValues();
}
