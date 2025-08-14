#include "File.h"


namespace fs = std::filesystem;

std::string fox::file::GetCurrentDirectory()
{
	std::error_code ec;
    fs::path path = fs::current_path(ec);
    return ec ? std::string{} : path.string();
}

bool fox::file::SetCurrentDirectory(const std::string& path)
{
	std::error_code ec;
	fs::current_path(path, ec);
	return !ec;
}

std::string fox::file::GetExtension(const std::string& path)
{
	fs::path p(path);
	return p.extension().string();
}

std::string fox::file::GetFilename(const std::string& path)
{
	fs::path p(path);
	return p.filename().string();
}

bool fox::file::Exists(const std::string& path)
{
	std::error_code ec;
	bool result = fs::exists(path, ec);
	return !ec && result;
}

std::vector<std::string> fox::file::GetFilesInDirectory(const std::string& path)
{
	std::vector<std::string> files;
	std::error_code ec;

	fs::directory_iterator iter(path, ec);
	if (ec) return files;

	for (const auto& entry : iter) {
		if (entry.is_regular_file(ec) && !ec) {
			files.push_back(entry.path().string());
		}
	}

	return files;
}

std::vector<std::string> fox::file::GetDirectoriesIn(const std::string& path)
{
	std::vector<std::string> directories;
	std::error_code ec;

	fs::directory_iterator iter(path, ec);
	if (ec) return directories;

	for (const auto& entry : iter) {
		if (entry.is_directory(ec) && !ec) {
			directories.push_back(entry.path().string());
		}
	}

	return directories;
}

bool fox::file::ReadTextFile(const std::string& path, std::string& content)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		return false;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();  
	content = buffer.str();  
	return true;
}

bool fox::file::WriteTextFile(const std::string& path, const std::string& content, bool append)
{
	std::ios::openmode mode = std::ios::out | (append ? std::ios::app : std::ios::trunc);
	std::ofstream file(path, mode);
	if (!file.is_open()) {
		return false;
	}

	file << content;
	return true;
}
