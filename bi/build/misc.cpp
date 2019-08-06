/**
 * @file
 */
#include "bi/build/misc.hpp"

#include "boost/algorithm/string.hpp"

void bi::warn(const std::string& msg) {
  std::cerr << "warning: " << msg << std::endl;
}

std::filesystem::path bi::find(const std::list<std::filesystem::path>& paths, const std::filesystem::path path) {
  auto iter = paths.begin();
  while (iter != paths.end() && !exists(*iter / path)) {
    ++iter;
  }
  if (iter == paths.end()) {
    throw FileNotFoundException(path.string().c_str());
  } else {
    return *iter / path;
  }
}

bool bi::copy_if_newer(std::filesystem::path src, std::filesystem::path dst) {
  using namespace std::filesystem;

  /* copy_file(src, dst, copy_option::overwrite_if_exists) seems problematic,
   * workaround... */
  bool result = false;
  if (!exists(dst)) {
    copy_file(src, dst);
    result = true;
  } else if (last_write_time(src) > last_write_time(dst)) {
    remove(dst);
    copy_file(src, dst);
    result = true;
  }
  return result;
}

bool bi::copy_with_prompt(std::filesystem::path src, std::filesystem::path dst) {
  using namespace std::filesystem;

  bool result = false;
  std::string ans;

  if (exists(dst)) {
    std::cout << dst.string() << " already exists, overwrite? [y/N] ";
    std::getline(std::cin, ans);
    if (ans.length() > 0 && (ans[0] == 'y' || ans[0] == 'Y')) {
      remove(dst);
      copy_file(src, dst);
      result = true;
    }
  } else {
    copy_file(src, dst);
    result = true;
  }
  return result;
}

void bi::copy_with_force(std::filesystem::path src, std::filesystem::path dst) {
  using namespace std::filesystem;

  if (exists(dst)) {
    remove(dst);
    copy_file(src, dst);
  } else {
    copy_file(src, dst);
  }
}

std::filesystem::path bi::remove_first(const std::filesystem::path& path) {
  auto parent = path.parent_path();
  if (parent == path || parent.string().compare(".") == 0) {
    return std::filesystem::path() / path.filename();
  } else {
    return remove_first(path.parent_path()) / path.filename();
  }
}

std::filesystem::path bi::remove_common_prefix(const std::filesystem::path& base, const std::filesystem::path& path) {
  auto iter1 = base.begin();
  auto end1 = base.end();
  auto iter2 = path.begin();
  auto end2 = path.end();
  while (iter1 != end1 && iter2 != end2 && *iter1 == *iter2) {
    ++iter1;
    ++iter2;
  }
  if (iter2 != end2) {
    auto result = *iter2;
    ++iter2;
    while (iter2 != end2) {
      result /= *iter2;
      ++iter2;
    }
    return result;
  } else {
    return std::filesystem::path();
  }
}

std::string bi::read_all(const std::filesystem::path& path) {
  std::ifstream in(path);
  std::stringstream buf;
  buf << in.rdbuf();
  return buf.str();
}

void bi::write_all(const std::filesystem::path& path, const std::string& contents) {
  if (!path.parent_path().empty()) {
    std::filesystem::create_directories(path.parent_path());
  }
  std::ofstream out(path);
  std::stringstream buf(contents);
  out << buf.rdbuf();
}

bool bi::write_all_if_different(const std::filesystem::path& path,
    const std::string& contents) {
  if (std::filesystem::exists(path)) {
    std::string old = read_all(path);
    if (contents != old) {
      write_all(path, contents);
      return true;
    }
  } else {
    write_all(path, contents);
    return true;
  }
  return false;
}

std::string bi::tarname(const std::string& name) {
  std::string result = name;
  boost::to_lower(result);
  boost::replace_all(result, ".", "_");
  boost::replace_all(result, "-", "_");
  return result;
}

bool bi::isPower2(const int x) {
  return x > 0 && !(x & (x - 1));
}
