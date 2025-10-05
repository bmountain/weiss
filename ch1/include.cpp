#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <regex>

using namespace std;
namespace fs = filesystem;

enum class IncludeType
{
  UserCode,
  StandardLibrary,
  Other
};

struct IncludeInfo
{
  IncludeType type;
  string fileName;
};

string read_file(fs::path filePath);
IncludeInfo getIncludeInfo(const string& line);
fs::path findStandardLibraryPath(string fileName);
fs::path findPath(fs::path source, const IncludeType& type, const string& fileName);

int main(int argc, char** argv)
{
  if (argc > 2) {
    throw invalid_argument("Too many argument");
  }
  fs::path filePath{argv[1]};
  println("{}", read_file(filePath));
}

string read_file(fs::path filePath)
{
  using enum IncludeType;

  ifstream fs{filePath};
  if (!fs) {
    throw runtime_error{format("Failed to open file: {}", string(filePath))};
  }
  string contents;
  string line;
  while (getline(fs, line)) {
    const auto& [type, file] = getIncludeInfo(line);

    switch (type) {
    case StandardLibrary:
      contents += read_file(findPath(filePath, type, file));
      break;
    case UserCode: {
      fs::path includeFilePath = filePath.replace_filename(file);
      contents += read_file(findPath(filePath, type, file));
    } break;
    case Other:
      contents += line + "\n";
      break;
    default:
      throw runtime_error("Unknown include type");
    }
  }
  return contents;
}

fs::path findPath(fs::path source, const IncludeType& type, const string& fileName)
{
  if (type == IncludeType::StandardLibrary) {
    return findStandardLibraryPath(fileName);
  }
  return source.replace_filename(fileName);
}

fs::path findStandardLibraryPath(string fileName)
{
  static const fs::path stlDir{"/opt/gcc-15/include/c++/15.1.0"};

  std::size_t pos = fileName.find_last_of('/');
  if (pos != string::npos) {
    fileName = fileName.substr(pos + 1);
  }

  for (const fs::directory_entry& entry : fs::recursive_directory_iterator(stlDir)) {
    if (entry.is_regular_file() && entry.path().filename() == fileName) {
      return entry.path();
    }
  }
  throw runtime_error(format("Standard library not found: {}", fileName));
}

IncludeInfo getIncludeInfo(const string& line)
{
  static const regex reUser{R"(\s*#include\s+\"(.+)\"\s*$)"};
  static const regex reStandard{R"(\s*#include\s+<(.+)>\s*$)"};
  using enum IncludeType;

  smatch m;
  if (regex_match(line, m, reUser); m.size()) {
    return IncludeInfo{UserCode, m[1].str()};
  }
  if (regex_match(line, m, reStandard); m.size()) {
    return IncludeInfo{StandardLibrary, m[1].str()};
  }
  return IncludeInfo{Other, string{}};
}