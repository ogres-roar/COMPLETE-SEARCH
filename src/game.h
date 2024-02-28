#include <vector>

using namespace std;
class Cell
{
public:
    Cell() = default;
    Cell(int row, int column);
    int getRow();
    int getColumn();

private:
    int row_ = 0;
    int column_ = 0;
};

class Region
{
public:
    Region() = default;
    Region(int num_cells);
    vector<Cell> getCells();
    void setCell(int pos, Cell cell);

private:
    vector<Cell> matrix_;
    int num_cells_;
};

class Board
{
public:
    Board(int num_rows, int num_columns, int num_regions);
    vector<vector<int>> getValues();
    int getValue(int row, int column);
    Region getRegion(int index);
    vector<Region> getRegions();
    void setValue(int row, int column, int value);
    void setRegion(int index, Region initial_region);
    void setValues(vector<vector<int>> values);

private:
    vector<vector<int>> values_;
    vector<Region> regions_;
    int num_rows_;
    int num_columns_;
    int num_regions_;
};

vector<vector<int>> solver(Board board);
