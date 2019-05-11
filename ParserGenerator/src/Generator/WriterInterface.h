#pragma once

#include <string>
#include <fstream>

class IWriterInterface
{
public:
	virtual void GetFileStreams(const std::string& RelativeDirectory, const std::string& FileName, std::ofstream& OutHeaderStream, std::ofstream& OutSourceStream) = 0;
};