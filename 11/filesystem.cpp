#include <filesystem>
#include <iostream>
#include <regex>
#include <string_view>

/**
 * Prints content of directory given by path
 * Format
 * [X] file_name file_size
 * where X equals D for directories, F for regular files, L for symlinks and
 * space otherwise.
 * @param path directory path
 */
void printDirectory(std::string_view path) {
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    if (entry.is_directory()) {
      std::cout << "D " << entry.path().filename() << "\n";
    } else if (entry.is_regular_file()) {
      std::cout << "F " << entry.path().filename() << " " << entry.file_size()
                << "\n";
    } else if (entry.is_symlink()) {
      std::cout << "L " << entry.path().filename() << " " << entry.file_size()
                << "\n";
    } else {
      std::cout << " " << entry.path().filename() << " " << entry.file_size()
                << "\n";
    }
  }
}
/**
 * Makes copies of all files matching fileNames regular expression in directory
 * given by path to files in the same directory but with changes extension to
 * newExtension
 * @param path directory path
 * @param fileNames regular expression
 * @param newExtension new extension
 */
void changeExtension(std::filesystem::path path, std::string fileNames,
                     std::string_view newExtension) {
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    std::cout << entry.path().filename() << std::endl;
    std::cout << entry.path().filename().string() << std::endl;
    if (std::regex_search(entry.path().filename().string(),
                          std::regex(fileNames))) {

      std::filesystem::copy_file(
          entry.path(),
          std::filesystem::path(entry.path()).replace_extension(newExtension));
    }
  }
}

int main(void) {
  printDirectory("..");
  changeExtension(std::filesystem::path("test"), "^[0-9]+", "cpp");
}