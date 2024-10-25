#include <iostream>
#include <vector>

class Minesweeper {
 private:
  size_t M, N;                          // NOLINT
  std::vector<std::vector<int>> Table;  // NOLINT

 public:
  Minesweeper(size_t m, size_t n) : M(m), N(n) {
    Table.resize(M, std::vector<int>(N, 0));
  }

  size_t Rows() const {
    return M;
  }

  size_t Columns() const {
    return N;
  }

  void SetMine(size_t i, size_t j) {
    Table[i][j] = -1;
  }

  int operator()(size_t i, size_t j) const {
    return Table[i][j];
  }

  void CheckForMinesAround() {
    for (size_t i = 0; i != M; ++i) {
      for (size_t j = 0; j != N; ++j) {
        if (Table[i][j] != -1) {
          CheckForMinesAround(i, j);
        }
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Minesweeper& ms) {
    for (size_t i = 0; i != ms.Rows(); ++i) {
      for (size_t j = 0; j != ms.Columns(); ++j) {
        if (ms(i, j) == -1) {
          out << '*';
        } else {
          out << ms(i, j);
        }
      }
      out << "\n";
    }
    return out;
  }

 private:
  void CheckForMinesAround(size_t i, size_t j) {
    int counter = 0;
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (i + dx >= 0 && i + dx < M && j + dy >= 0 && j + dy < N && Table[i + dx][j + dy] == -1) {
          ++counter;
        }
      }
    }
    Table[i][j] = counter;
  }
};
