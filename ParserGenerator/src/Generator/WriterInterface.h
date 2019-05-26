#pragma once

#include <string>
#include <fstream>

namespace ParserGenerator {

	class IWriterInterface
	{
	public:
		virtual bool GetCodeFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream* OutHeaderStream, std::ofstream* OutSourceStream = nullptr) = 0;
	};
}