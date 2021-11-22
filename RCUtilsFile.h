#pragma once

#include "RCUtilsBase.h"

namespace RCUtils
{
	inline std::vector<char> LoadFileToArray(const char* Filename, bool* OutSuccess = nullptr)
	{
		std::vector<char> OutData;
		bool bSuccess = false;
		FILE* File = nullptr;
		fopen_s(&File, Filename, "rb");
		if (File)
		{
			fseek(File, 0, SEEK_END);
			long Size = ftell(File);
			fseek(File, 0, SEEK_SET);
			check(Size > 0);
			OutData.resize(Size);
			fread(&OutData[0], 1, Size, File);
			fclose(File);
			bSuccess = true;
		}

		if (OutSuccess)
		{
			*OutSuccess = bSuccess;
		}

		return OutData;
	}

	inline std::string LoadFileToString(const char* Filename, bool* OutSuccess = nullptr)
	{
		bool bSuccess = false;
		std::string OutString;
		FILE* File;
		fopen_s(&File, Filename, "rb");
		if (File)
		{
			fseek(File, 0, SEEK_END);
			long Size = ftell(File);
			check(Size > 0);
			std::vector<char> Data(Size);
			fseek(File, 0, SEEK_SET);
			fread(&Data[0], 1, Size, File);
			fclose(File);
			OutString.resize(Size);
			OutString = &Data[0];
			bSuccess = true;
		}

		if (OutSuccess)
		{
			*OutSuccess = bSuccess;
		}

		return OutString;
	}

	// Returns Extension
	inline std::string SplitPath(const std::string& FullPathToFilename, std::string& OutPath, std::string& OutFilename, bool bIncludeExtension)
	{
		char Buffer[1024];
		char* PtrFilename = nullptr;
		::GetFullPathNameA(FullPathToFilename.c_str(), sizeof(Buffer), Buffer, &PtrFilename);
		OutPath = Buffer;
		if (PtrFilename)
		{
			OutPath.resize(PtrFilename - Buffer);
			OutFilename = PtrFilename;
		}

		std::string Extension;

		auto ExtensionFound = OutFilename.rfind('.');
		if (ExtensionFound != std::string::npos)
		{
			Extension = OutFilename.substr(ExtensionFound + 1);
			if (!bIncludeExtension)
			{
				OutFilename.resize(ExtensionFound);
			}
		}

		return Extension;
	}

	inline std::string GetBaseName(const std::string& FullPathToFilename, bool bExtension)
	{
		std::string Path;
		std::string Filename;
		SplitPath(FullPathToFilename, Path, Filename, bExtension);
		return Filename;
	}

	inline std::string GetPath(const std::string& FullPathToFilename, bool bExtension)
	{
		std::string Path;
		std::string Filename;
		SplitPath(FullPathToFilename, Path, Filename, bExtension);
		return Path;
	}

	inline void RemoveQuotes(std::string& Path)
	{
		if (Path.size() > 2 && Path.front() == '"')
		{
			check(Path.back() == '"');
			Path.pop_back();
			Path = Path.substr(1);
		}
	}

	inline std::string MakePath(const std::string& Root, const std::string& DirOrFile)
	{
		std::string Out;
		if (!Root.empty())
		{
			Out = Root;
			RemoveQuotes(Out);
			if (Root.back() != '\\')
			{
				Out += '\\';
			}
		}

		Out += DirOrFile;
		return Out;
	}

	inline std::string AddQuotes(const std::string& InPath)
	{
		std::string Path = InPath;
		if (Path.size() > 2 && Path.front() == '"')
		{
			check(Path.back() == '"');
		}
		else
		{
			Path = "\"" + Path;
			Path +="\"";
		}

		return Path;
	}


	inline std::vector<std::string> GetFilenamesInDir(const char* Path, bool bFullFilename)
	{
		std::vector<std::string> FileList;
		if (Path && *Path)
		{
			std::string Filename = Path;
			Filename += "\\*.*";
			::WIN32_FIND_DATAA FindData;
			::HANDLE Found = INVALID_HANDLE_VALUE;
			Found = ::FindFirstFileA(Filename.c_str(), &FindData);
			if (Found != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					{
						std::string ItemName;
						if (bFullFilename)
						{
							ItemName = Path;
							ItemName += "\\";
						}
						ItemName += FindData.cFileName;
						FileList.push_back(ItemName);
					}
				}
				while (::FindNextFileA(Found, &FindData));
				::FindClose(Found);
			}
		}

		return FileList;
	}

	// Returns true is Src is newer than Dst or if Dst doesn't exist
	inline bool IsNewerThan(const std::string& Src, const std::string& Dst)
	{
		HANDLE SrcHandle = ::CreateFileA(Src.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		if (SrcHandle == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		HANDLE DstHandle = ::CreateFileA(Dst.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		if (DstHandle == INVALID_HANDLE_VALUE)
		{
			::CloseHandle(SrcHandle);
			return true;
		}

		FILETIME SrcTime, DstTime;
		if (!::GetFileTime(SrcHandle, nullptr, nullptr, &SrcTime))
		{
			auto Error = ::GetLastError();
			check(0);
			return false;
		}

		if (!::GetFileTime(DstHandle, nullptr, nullptr, &DstTime))
		{
			auto Error = ::GetLastError();
			check(0);
			return false;
		}

		bool bResult = false;
		if (SrcTime.dwHighDateTime < DstTime.dwHighDateTime)
		{
			bResult = false;
		}
		else if (SrcTime.dwHighDateTime == DstTime.dwHighDateTime)
		{
			bResult = SrcTime.dwLowDateTime > DstTime.dwLowDateTime;
		}
		else
		{
			bResult = true;
		}

		::CloseHandle(DstHandle);
		::CloseHandle(SrcHandle);
		return bResult;
	}
}
