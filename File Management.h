#pragma once

#include <string>
#include <vector>
#include <fstream>

class FileManagement
{

public:
	static std::vector<std::string> GetList()
	{
		std::vector<std::string> output;
		std::string line = "";
		std::ifstream inFile;
		inFile.open("saved_files.txt");
		if (inFile.is_open())
		{
			while (getline(inFile, line))
			{
				output.push_back(line);
			}
		}
		if (output.size() == 0)
		{
			std::ofstream myfile;
			std::string fullName = "saved_files.txt";
			myfile.open(fullName.c_str());
			myfile << "";
			myfile.close();
		}
		return output;
	}

	static bool CheckExists(std::string fileName)
	{
		std::vector<std::string> files = GetList();
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i] == fileName)
			{
				return true;
			}
		}
		return false;
	}

	static std::string ReadFile(std::string fileName)
	{
		if (!CheckExists(fileName))
		{
			return "";
		}
		std::string contents = "";
		std::string line = "";
		std::ifstream inFile;
		inFile.open((fileName + ".dti").c_str());
		if (inFile.is_open())
		{
			while (getline(inFile, line))
			{
				if (contents != "")
				{
					contents += "\n";
				}
				contents += line;
			}
		}
		return contents;
	}

	static void WriteFile(std::string fileName, std::string content)
	{
		if (!CheckExists(fileName))
		{
			std::vector<std::string> files = GetList();
			files.push_back(fileName);
			std::string fileString = "";
			for (int i = 0; i < files.size(); i++)
			{
				if (fileString != "")
				{
					fileString += "\n";
				}
				fileString += files[i];
			}
			std::ofstream fileListOutput;
			std::string name = "saved_files.txt";
			fileListOutput.open(name.c_str());
			fileListOutput << fileString;
			fileListOutput.close();
		}
		std::ofstream myfile;
		std::string fullName = fileName + ".dti";
		myfile.open(fullName.c_str());
		myfile << content;
		myfile.close();
	}

	static void DeleteFile(std::string fileName)
	{
		if (CheckExists(fileName))
		{
			WriteFile(fileName, "");
			std::vector<std::string> list = GetList();
			std::string listText = "";
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] != fileName)
				{
					if (listText != "")
					{
						listText += "\n";
					}
					listText += list[i];
				}
			}
			std::ofstream fileListOutput;
			std::string name = "saved_files.txt";
			fileListOutput.open(name.c_str());
			fileListOutput << listText;
			fileListOutput.close();
		}
	}
};