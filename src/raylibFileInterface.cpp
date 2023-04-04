#include <filesystem>
#include "raylibFileInterface.h"
#include <fstream>

const std::filesystem::path dir("../../assets/");

inline bool StartsWith(const std::string &text, const std::string &ending) {
	if (ending.size() > text.size()) {
		return false;
	}

	return std::equal(text.begin(), text.begin() + ending.size(), ending.begin(), ending.end());
}

inline void RemoveText(std::string &text, const std::string &toRemove) {
	auto pos = std::string::npos;

	while ((pos = text.find(toRemove)) != std::string::npos) {
		text.erase(pos, toRemove.length());
	}
}

Rml::FileHandle RaylibFileInterface::Open(const Rml::String &path) {
	auto stream = new std::fstream(ParsePath(path), std::ios::in);

	return (Rml::FileHandle)stream;
}

void RaylibFileInterface::Close(Rml::FileHandle file) {
	(*(std::fstream*)file).close();

	delete (std::fstream*)file;
}

size_t RaylibFileInterface::Read(void* buffer, std::size_t size, Rml::FileHandle file) {
	return (*(std::fstream*)file).readsome(reinterpret_cast<char*>(buffer), size);
}

bool RaylibFileInterface::Seek(Rml::FileHandle file, long offset, int origin) {
	auto direction = std::ios::beg;
	switch (origin) {
		default:
			break;
		case SEEK_CUR:
			direction = std::ios::cur;
			break;
		case SEEK_END:
			direction = std::ios::end;
	}
	(*(std::fstream*)file).seekg(offset, direction);

	return (*(std::fstream*)file).fail();
}

size_t RaylibFileInterface::Tell(Rml::FileHandle file) {
	return (*(std::fstream*)file).tellg();
}

std::string RaylibFileInterface::ParsePath(const std::string &path) {
	auto filePath = std::string(path);
	RemoveText(filePath, "..");
	while (StartsWith(filePath, "/")) {
		filePath = filePath.substr(1);
	}
	while (StartsWith(filePath, "assets/")) {
		filePath = filePath.substr(7);
	}
	const std::filesystem::path f(filePath);
	auto full = dir / f;
	auto str = full.string();

	return str;
}
