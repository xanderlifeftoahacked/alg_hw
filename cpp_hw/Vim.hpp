#include <iostream>

namespace utils {
inline size_t Max(size_t a, size_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

inline size_t Min(size_t a, size_t b) {
  if (a < b) {
    return a;
  }
  return b;
}

}  // namespace utils

class Vim {
  static constexpr size_t kMaxSize = 10000;
  enum class States { NormalMode, InputMode };

  States state_;
  size_t pos_;
  size_t last_symb_;
  char* infile_;
  char* outfile_;

  void InsertAt(size_t pos, char value) {
    if (pos > last_symb_ || last_symb_ > kMaxSize) {
      return;
    }

    for (size_t i = last_symb_; i > pos; --i) {
      outfile_[i] = outfile_[i - 1];
    }
    outfile_[pos] = value;

    ++last_symb_;
  }
  void Evaluate() {
    char cur_char = ' ';
    int parent_c = 0;

    for (size_t i = 0; i < kMaxSize; ++i) {
      if (infile_[i] == '\0') {
        break;
      }
      cur_char = infile_[i];
      if (cur_char == '>') {
        state_ = States::NormalMode;
        --parent_c;
        continue;
      }

      if (cur_char == '<') {
        ++parent_c;
        continue;
      }

      if (parent_c != 0) {
        continue;
      }

      if (state_ == States::InputMode) {
        InsertAt(pos_, cur_char);
        pos_ = utils::Min(pos_ + 1, last_symb_);
        continue;
      }

      switch (cur_char) {
        case 'i':
          state_ = States::InputMode;
          break;
        case 'h':
          if (pos_ == 0) {
            break;
          }
          --pos_;
          break;
        case 'l':
          pos_ = utils::Min(last_symb_, pos_ + 1);
          break;
        default:
          break;
      }
    }

    outfile_[last_symb_] = '\0';
  }

 public:
  Vim()
      : state_{States::NormalMode}, pos_{0}, last_symb_{0}, infile_{new char[kMaxSize]}, outfile_{new char[kMaxSize]} {
    infile_[0] = '\0';
  }

  ~Vim() {
    delete[] outfile_;
    delete[] infile_;
  }

  friend std::ostream& operator<<(std::ostream& out, Vim& editor) {
    editor.Evaluate();
    out << editor.outfile_;
    return out;
  }

  friend std::istream& operator>>(std::istream& in, Vim& editor) {
    in.getline(editor.infile_, kMaxSize);
    return in;
  }
};
