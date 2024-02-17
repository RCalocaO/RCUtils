#pragma once

#include "RCUtilsBase.h"

namespace RCUtils
{
	struct FCmdLine
	{
		static inline FCmdLine& Get()
		{
			static FCmdLine Instance;
			return Instance;
		}

		FCmdLine()
		{
			check(__argc > 0);
			Exe = __argv[0];

			for (int32 i = 1; i < __argc; ++i)
			{
				if (__argv[i][0] == '@')
				{
					ParseIni(__argv[i] + 1);
				}
				else
				{
					AddArgument(__argv[i]);
				}
			}
		}

		void AddArgument(const char* Arg)
		{
			FullCmdLine += Arg;
			FullCmdLine += " ";
			Args.push_back(Arg);
		}

		void AddLine(const char* Line)
		{
			while (*Line && !(*Line == '\r' || *Line == '\n'))
			{
				while (*Line == ' ')
				{
					++Line;
				}
				char NewArgStr[256] = "";
				char* NewArg = NewArgStr;
				bool bInQuotes = false;
				while (*Line && !(*Line == '\r' || *Line == '\n'))
				{
					if (!bInQuotes && *Line == ';')
					{
						break;
					}
					*NewArg++ = *Line;
					if (*Line == '"')
					{
						bInQuotes = !bInQuotes;
					}
					++Line;
					if (*Line == ' ' && !bInQuotes)
					{
						break;
					}
				}

				if (NewArg != NewArgStr)
				{
					AddArgument(NewArgStr);
				}

				if (*Line == ';')
				{
					break;
				}
			}
		}

		void ParseIni(const char* Filename)
		{
			FILE* f = fopen(Filename, "r");
			if (f)
			{
				char s[256];
				while (fgets(s, 255, f))
				{
					AddLine(s);
				}
				fclose(f);
			}
		}

		bool Contains(const char* Value) const
		{
			check(Value && *Value);
			for (const auto& Arg : Args)
			{
				if (!_strcmpi(Value, Arg.c_str()))
				{
					return true;
				}
			}

			return false;
		}

		uint32 TryGetIntPrefix(const char* Prefix, uint32 ValueIfMissing, bool* pFound = nullptr)
		{
			check(Prefix);
			uint32 PrefixLength = (uint32)strlen(Prefix);
			for (const auto& Arg : Args)
			{
				if (!_strnicmp(Arg.c_str(), Prefix, PrefixLength))
				{
					const char* IntString = Arg.c_str() + PrefixLength;
					if (pFound)
					{
						*pFound = true;
					}
					return atoi(IntString);
				}
			}

			return ValueIfMissing;
		}

		float TryGetFloatPrefix(const char* Prefix, float ValueIfMissing, bool* pFound = nullptr)
		{
			check(Prefix);
			uint32 PrefixLength = (uint32)strlen(Prefix);
			for (const auto& Arg : Args)
			{
				if (!_strnicmp(Arg.c_str(), Prefix, PrefixLength))
				{
					const char* FloatString = Arg.c_str() + PrefixLength;
					if (pFound)
					{
						*pFound = true;
					}
					return (float)atof(FloatString);
				}
			}

			return ValueIfMissing;
		}

		bool TryGetStringFromPrefix(const char* Prefix, const char*& OutValue, bool* pFound = nullptr)
		{
			check(Prefix);
			uint32 PrefixLength = (uint32)strlen(Prefix);
			for (const auto& Arg : Args)
			{
				if (!_strnicmp(Arg.c_str(), Prefix, PrefixLength))
				{
					OutValue = Arg.c_str() + PrefixLength;
					if (pFound)
					{
						*pFound = true;
					}
					return true;
				}
			}

			return false;
		}

		std::string Exe;
		std::string FullCmdLine;
		std::vector<std::string> Args;
	};
}
