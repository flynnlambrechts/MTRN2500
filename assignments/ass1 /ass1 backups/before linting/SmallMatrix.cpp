#include "SmallMatrix.hpp"
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>

namespace mtrn2500 {
double const EPS {0.0000001};

// Helper Functions

bool checkEqual(const double &lhs, const double &rhs) {
    return std::abs(lhs - rhs) < EPS;
}

void checkInRange(const SmallMatrix *matrix, int nRow = 0, int nCol = 0) {
    if (matrix->size() == std::make_pair(0, 0)) {
        throw std::out_of_range("attempting to access a 0 x 0 matrix.");
    } else if (nRow >= matrix->size().first || nRow < 0 ||
               nCol >= matrix->size().second || nCol < 0) {
        std::string message = "the specified row " + 
                              std::to_string(nRow) + " and column " + 
                              std::to_string(nCol) + " is outside the range (" + 
                              std::to_string(matrix->size().first) + " " + 
                              std::to_string(matrix->size().second) + ")";

        throw std::out_of_range(message);
    } 
}

void checkSizesMatch(const SmallMatrix &m1, const SmallMatrix &m2) {
    if (m1.size() != m2.size()) {
        throw std::invalid_argument("number of rows and columns on the left-hand\
                                     side is not equal to the number of rows and\
                                     columns on the right-hand side respectively.");
    }
}

void checkRowsMatchCols(int lhs_cols, int rhs_rows) {
    if (lhs_cols != rhs_rows) {
        throw std::invalid_argument("the number of columns on the left-hand\
                                     side is not equal to the number of rows\
                                      on the right-hand side.");
    }
}

void checkInsertInput(int const index, std::vector<double> const &vec, double const max_index, int const length) {
    if (index > max_index || index < 0) {
        throw std::out_of_range("the specified row/col index is outside the range [0, max_row/max_col).");
    } else if (vec.size() != length && length != 0) {
        throw std::invalid_argument("the size of the specified vector is not equal to the \
                                     number of non-zero columns/rows in the matrix.");
    }
}

double dot(std::vector<const double *> lhs, std::vector<const double *> rhs) {
    double result {0};
    for (int i {0}; i < static_cast<int>(lhs.size()); i++) {
        result += (*lhs.at(i))*(*rhs.at(i));
    }
    return result;
}

void SmallMatrix::convertStackToHeap() {
    mHeapData.resize(mNumRows);
    
    for (int i {0}; i < mNumRows; i++) {
        mHeapData.at(i).resize(mNumCols, 0);
        std::move(mStackData[i].begin(), 
                  mStackData[i].begin() + mNumCols, 
                  mHeapData.at(i).begin());
    }


    mStackData = {};
    mIsLargeMatrix = true;
}

// End Helper Functions

SmallMatrix::SmallMatrix()
    : mNumRows{0}, mNumCols{0}, mIsLargeMatrix{false} {}

SmallMatrix::SmallMatrix(int numRows, int numCols) : SmallMatrix(numRows, numCols, 0) {}

SmallMatrix::SmallMatrix(int numRows, int numCols, double value)
    : mNumRows{numRows}, mNumCols{numCols}
    , mIsLargeMatrix{mNumRows * mNumCols >= mSmallSize} {

    if (mIsLargeMatrix) {
        std::vector<double> row(mNumCols, value);
        mHeapData.resize(mNumRows, row);
    } else {
        std::for_each(mStackData.begin(), mStackData.begin() + mNumRows,
            [this, value](auto &row){std::fill_n(row.begin(), this->mNumCols, value);}
        );
    }
}

SmallMatrix::SmallMatrix(std::initializer_list<std::initializer_list<double>> const& il)
    : mNumRows(il.size()),
      mNumCols(il.begin() == il.end() ? 0 : il.begin()->size()),
      mIsLargeMatrix(mNumRows * mNumCols >= mSmallSize) {
    if (std::adjacent_find(il.begin(), il.end(), [](auto const& lhs, auto const& rhs) {
            return lhs.size() != rhs.size();
        }) != il.end()) {
        throw std::invalid_argument("Rows have different sizes.");
    }

    if (mIsLargeMatrix) {
        mHeapData.resize(mNumRows);
    }

    int row_index{0};
    for (auto const& row : il) {
        if (mIsLargeMatrix) {
            mHeapData.at(row_index).resize(mNumCols);
            std::copy(row.begin(), row.end(), mHeapData.at(row_index).begin());
        } else {
            std::transform(row.begin(), row.end(), mStackData.at(row_index).begin(),
                           [](auto const& e) { return e; });
        }
        row_index++;
    }
}

SmallMatrix::SmallMatrix(SmallMatrix const& sm) {*this = sm;}

SmallMatrix::SmallMatrix(SmallMatrix&& sm) {
    *this = std::move(sm);
}

SmallMatrix& SmallMatrix::operator=(SmallMatrix const& sm) {
    if (this == &sm) {
        return *this;
    }

    mNumRows = sm.mNumRows;
    mNumCols = sm.mNumCols;
    mIsLargeMatrix = sm.mIsLargeMatrix;

    if (mIsLargeMatrix) {
        mHeapData.resize(mNumRows);
    }
    
    for (int i {0}; i < mNumRows; i++) {
        if (mIsLargeMatrix) {
            mHeapData.at(i).resize(mNumCols);
            std::copy(sm.mHeapData.at(i).begin(), sm.mHeapData.at(i).end(), mHeapData.at(i).begin());
        } else {
            mStackData[i] = sm.mStackData[i];
        }
    }

    return *this;
}

SmallMatrix& SmallMatrix::operator=(SmallMatrix&& sm) {
    mNumRows = std::exchange(sm.mNumRows, 0);
    mNumCols = std::exchange(sm.mNumCols, 0);
    mIsLargeMatrix = std::exchange(sm.mIsLargeMatrix, false);

    if (mIsLargeMatrix) {
        mHeapData = std::exchange(sm.mHeapData, {});
    } else {
        mStackData = std::exchange(sm.mStackData, {});
    }
    return *this;
}

double& SmallMatrix::operator()(int numRow, int numCol) {
    checkInRange(this, numRow, numCol);
    if (mIsLargeMatrix) {
        return mHeapData.at(numRow).at(numCol);
    } else {
        return mStackData[numRow][numCol];
    }
}

const double& SmallMatrix::operator()(int numRow, int numCol) const {
    checkInRange(this, numRow, numCol);

    if (mIsLargeMatrix) {
        const double &returnNum {mHeapData.at(numRow).at(numCol)};
        return returnNum;
    } else {
        const double &returnNum {mStackData[numRow][numCol]};
        return returnNum;
    }
}

std::pair<int, int> SmallMatrix::size() const {return std::make_pair(mNumRows, mNumCols);}

bool SmallMatrix::isSmall() const {return !mIsLargeMatrix;}

bool operator==(SmallMatrix const& lhs, SmallMatrix const& rhs) {

    if (lhs.mNumRows != rhs.mNumRows || rhs.mNumCols != lhs.mNumCols) {
        return false;
    } else if (lhs.mNumRows == 0 || lhs.mNumCols == 0) {
        return true;
    }

    auto equalLambda = [](const double *lhsElem, const double *rhsElem){
        return std::abs(*lhsElem - *rhsElem) < EPS;
    };

    for (int i {0}; i < lhs.mNumRows; i++) {
        // std::cout << i << std::endl; 
        auto const lhsRow = lhs.row(i);
        bool equal = std::equal(lhsRow.begin(), lhsRow.end(), rhs.row(i).begin(), equalLambda);
        if (!equal) {
            return false;
        }
    }

    return true;
}

bool operator!=(SmallMatrix const& lhs, SmallMatrix const& rhs) {
    return !operator==(lhs, rhs);
}

std::vector<double*> SmallMatrix::row(int numRow) {
    checkInRange(this, numRow);
    std::vector<double*> row (mNumCols);

    if (mIsLargeMatrix) {
        std::transform(mHeapData.at(numRow).begin(), mHeapData.at(numRow).end(),
            row.begin(), [](double &elem){return &elem;});
    } else {
        std::transform(mStackData[numRow].begin(), mStackData[numRow].begin() + mNumCols,
            row.begin(), [](double &elem){return &elem;});
    } 
    return row; 
}

std::vector<double const*> SmallMatrix::row(int numRow) const {
    checkInRange(this, numRow);
    std::vector<double const*> row(mNumCols);

    if (mIsLargeMatrix) {
        std::transform(mHeapData.at(numRow).begin(), mHeapData.at(numRow).end(),
            row.begin(), [](const double &elem){return &elem;});
    } else {
        std::transform(mStackData[numRow].begin(), mStackData[numRow].begin() + mNumCols,
            row.begin(), [](const double &elem){return &elem;});
    }

    return row;
}

std::vector<double*> SmallMatrix::col(int numCol) {
    checkInRange(this, 0, numCol);
    std::vector<double*> col (mNumRows);

    if (mIsLargeMatrix) {
        std::transform(mHeapData.begin(), mHeapData.end(),
            col.begin(), [numCol](auto &row){return &row.at(numCol);});
    } else {
        std::transform(mStackData.begin(), mStackData.begin() + mNumRows,
            col.begin(), [numCol](auto &row){return &row[numCol];});
    }

    return col; 
}

std::vector<double const*> SmallMatrix::col(int numCol) const {
    checkInRange(this, 0, numCol);

    std::vector<double const*> col (mNumRows);

    if (mIsLargeMatrix) {
        std::transform(mHeapData.begin(), mHeapData.end(),
            col.begin(), [numCol](const auto &row){return &row.at(numCol);});
    } else {
        std::transform(mStackData.begin(), mStackData.begin() + mNumRows,
            col.begin(), [numCol](const auto &row){return &row[numCol];});
    }
    return col; 
}

void SmallMatrix::resize(int numRows, int numCols) {
    if (numRows < 0 || numCols < 0) {
        throw std::out_of_range("The specified row or column index is negative.");
    }

    bool new_IsLargeMatrix = numRows * numCols >= mSmallSize;

    auto trimRowArray = [numCols](auto &row){
        std::for_each(row.begin() + numCols, row.end(),
            [](double &elem){elem = 0;});
    };

    if (!mIsLargeMatrix && !new_IsLargeMatrix) {
        if (numRows < mNumRows) {
            std::for_each(mStackData.begin() + numRows, mStackData.begin() + mNumRows,
                [](auto &row){std::exchange(row, {});});
        }
        mNumRows = numRows;

        if (numCols < mNumCols) {
            std::for_each(mStackData.begin(), mStackData.begin() + mNumRows, trimRowArray);
        }
        mNumCols = numCols;
        mIsLargeMatrix = new_IsLargeMatrix;
    } else {
        const std::vector<double> blankRowVec(numCols, 0);
        mHeapData.resize(numRows, blankRowVec);
        mNumRows = numRows;

        if (!mIsLargeMatrix) {
            this->convertStackToHeap();
        }

        std::for_each(mHeapData.begin(), mHeapData.end(), 
            [numCols](auto &row){row.resize(numCols, 0);});

        mNumCols = numCols;
        mIsLargeMatrix = true;
    }
}

void SmallMatrix::insertRow(int numRow, std::vector<double> const& row) {
    checkInsertInput(numRow, row, mNumRows, mNumCols);

    if (!mIsLargeMatrix && (mNumRows + 1) * mNumCols >= mSmallSize) {
        this->convertStackToHeap();
    }

    if (mIsLargeMatrix) {
        mHeapData.insert(mHeapData.begin() + numRow, row);
    } else {
        std::move_backward(mStackData.begin() + numRow, 
                           mStackData.begin() + mNumRows, 
                           mStackData.begin() + mNumRows + 1);

        std::copy(row.begin(), row.end(), mStackData[numRow].begin());
    }
    mNumRows++;
}

void SmallMatrix::insertCol(int numCol, std::vector<double> const& col) {
    checkInsertInput(numCol, col, mNumCols, mNumRows);
    if (!mIsLargeMatrix && mNumRows * (mNumCols + 1) >= mSmallSize) {
        this->convertStackToHeap();
    }

    if (mIsLargeMatrix) {
        for (int i {0}; i < mNumRows; i++) {
            mHeapData.at(i).insert(mHeapData.at(i).begin() + numCol, col.at(i));
        }
    } else {
        for (int i {0}; i < mNumRows; i++) {
            std::move_backward(mStackData[i].begin() + numCol, 
                               mStackData[i].begin() + mNumCols, 
                               mStackData[i].begin() + mNumCols + 1);
            
            mStackData[i][numCol] = col.at(i);
        }
    }
    mNumCols++;
}

void SmallMatrix::eraseRow(int numRow) {
    if (numRow >= mNumRows || numRow < 0) {
        throw std::out_of_range("The specified row index is outside the range [0, max_row).");
    }
    if (mIsLargeMatrix) {
        mHeapData.erase(mHeapData.begin() + numRow);
    } else {
        std::move(mStackData.begin() + numRow + 1, 
                  mStackData.begin() + mNumRows,
                  mStackData.begin() + numRow);
    }
    mNumRows--;
}

void SmallMatrix::eraseCol(int numCol) {
    if (numCol >= mNumCols || numCol < 0) {
        throw std::out_of_range("The specified col index is outside the range [0, max_col).");
    }

    if (mIsLargeMatrix) {
        std::for_each(mHeapData.begin(), mHeapData.end(),
            [numCol](std::vector<double> &row){row.erase(row.begin() + numCol);});
    } else {
        auto eraseElemFromArray = [numCol, this](auto &row){
            std::move(row.begin() + numCol + 1,
                      row.begin() + this->mNumCols,
                      row.begin() + numCol);
        };

        std::for_each(mStackData.begin(), 
                      mStackData.begin() + mNumRows, 
                      eraseElemFromArray);
    }
    mNumCols--;
}

SmallMatrix operator+(SmallMatrix const& lhs, SmallMatrix const& rhs) {
    checkSizesMatch(lhs, rhs);

    SmallMatrix result = SmallMatrix(lhs.mNumRows, lhs.mNumCols);

    for (int i {0}; i < result.mNumRows; i++) {
        if (result.mIsLargeMatrix) {
            std::vector<double> &row = result.mHeapData.at(i);
            std::transform(lhs.mHeapData.at(i).begin(), 
                           lhs.mHeapData.at(i).end(), 
                           rhs.mHeapData.at(i).begin(),
                           row.begin(), 
                           std::plus<double>());
        } else {
            std::array<double, result.mSmallSize> &row = result.mStackData[i];
            std::transform(lhs.mStackData.at(i).begin(), 
                           lhs.mStackData.at(i).end(), 
                           rhs.mStackData.at(i).begin(),
                           row.begin(), 
                           std::plus<double>());
        }
    }
    return result; 
}

SmallMatrix operator-(SmallMatrix const& lhs, SmallMatrix const& rhs) {
    checkSizesMatch(lhs, rhs);
    SmallMatrix result = SmallMatrix(lhs.mNumRows, lhs.mNumCols);
    for (int i {0}; i < result.mNumRows; i++) {
        if (result.mIsLargeMatrix) {
            std::vector<double> &row = result.mHeapData.at(i);
            std::transform(lhs.mHeapData.at(i).begin(), 
                           lhs.mHeapData.at(i).end(), 
                           rhs.mHeapData.at(i).begin(),
                           row.begin(), 
                           std::minus<double>());
        } else {
            std::array<double, result.mSmallSize> &row = result.mStackData[i];
            std::transform(lhs.mStackData.at(i).begin(), 
                           lhs.mStackData.at(i).end(), 
                           rhs.mStackData.at(i).begin(),
                           row.begin(), 
                           std::minus<double>());
        }
    }
    return result; 
}

SmallMatrix operator*(SmallMatrix const& lhs, SmallMatrix const& rhs) {
    checkRowsMatchCols(lhs.mNumCols, rhs.mNumRows);
    SmallMatrix result = SmallMatrix(lhs.mNumRows, rhs.mNumCols);

    if (lhs.mNumCols == 0 && rhs.mNumRows == 0) {
        return result;
    }
    
    for (int i {0}; i < lhs.mNumRows; i++) {
        for (int j {0}; j < rhs.mNumCols; j++) {
            result(i, j) = dot(lhs.row(i), rhs.col(j));
        }
    }
    return result; 
}

SmallMatrix operator*(double s, SmallMatrix const& sm) {
    SmallMatrix result = SmallMatrix(sm.size().first, sm.size().second);

    for (int i {0}; i < result.mNumRows; i++) {
        if (result.mIsLargeMatrix) {
            std::vector<double> &row = result.mHeapData.at(i);
            std::transform(sm.mHeapData.at(i).begin(), 
                           sm.mHeapData.at(i).end(), 
                           row.begin(), 
                           [s](double elem){return s*elem;});
        } else {
            std::array<double, result.mSmallSize> &row = result.mStackData[i];
            std::transform(sm.mStackData.at(i).begin(), 
                           sm.mStackData.at(i).end(), 
                           row.begin(), 
                           [s](double elem){return s*elem;});
        }
    }

    return result; 
}

SmallMatrix operator*(SmallMatrix const& sm, double s) { return s*sm; }

SmallMatrix& SmallMatrix::operator+=(SmallMatrix const& sm) {
    *this = *this + sm;
    return *this;
}

SmallMatrix& SmallMatrix::operator-=(SmallMatrix const& sm) {
    *this = *this - sm;
    return *this;
}

SmallMatrix& SmallMatrix::operator*=(SmallMatrix const& sm) {
    *this = *this * sm;
    return *this; 
}

SmallMatrix& SmallMatrix::operator*=(double s) {
    *this = s * *this;
    return *this; 
}

SmallMatrix transpose(SmallMatrix const& sm) {
    SmallMatrix result = SmallMatrix(sm.mNumCols, sm.mNumRows);
    if (result.mIsLargeMatrix) {
        for (int i {0}; i < result.mNumRows; i++) {
            std::vector<const double *> col = sm.col(i);
            std::transform(col.begin(), col.end(), result.mHeapData.at(i).begin(),
                [](const double *elem_ptr){return *elem_ptr;});
        }
    } else {
        for (int i {0}; i < result.mNumRows; i++) {
            std::vector<const double *> col = sm.col(i);
            std::transform(col.begin(), col.end(), result.mStackData[i].begin(),
                [](const double *elem_ptr){return *elem_ptr;});
        }
    }
    return result; 
}

std::ostream& operator<<(std::ostream& os, SmallMatrix const& sm) {
    os << "[\n";
    for (int i {0}; i < sm.mNumRows; i++) {
        os << "  [ ";
        for (int j {0}; j < sm.mNumCols; j++) {

            os << sm(i, j) << " ";
        }
        os << "]\n";
    }
    os << "]\n";
    return os;
}

}  // namespace mtrn250