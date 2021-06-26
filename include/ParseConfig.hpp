#ifndef ParseConfigIG_HPP
#define ParseConfigIG_HPP

/* Сброс */

//# define RESET			"\e[0m"

#include <fcntl.h>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include "get_next_line.hpp"

class ParseConfig
{
	public:
		ParseConfig();
		~ParseConfig();

		// SET
		void setFlagLoc(bool FlagLoc);
		void setLocPath(std::string LocPath);

		// GET
		int getPosServ(void);
		bool getFlagLoc(void);
		std::vector <ParseConfig *> getServInfo(void);
		std::vector <std::string> getValueLocPath(void);
		std::vector < std::vector <std::string> > getLocPath(void);
		std::map < int, std::map<int, std::string> > &getMethods(void);
		std::map < std::string, std::map<std::string, std::string> > &getMapLoc(void);
		std::map <std::string, std::string> &getErrorPages(void);
		std::map <std::string, std::string> &getMapHeadFields(void);

		// METHODS
		void ParseConf(void);
		void ReadConf(void);
		void TestPrint(void);
		void ParseStart(char *line);
		void CheckDelimiter();
		void DelSpaceChars(std::string *str);
		void Parse1stLevel(std::string str);
		void Parse2ndLevel(std::string str);
		void FieldValidCheck(std::string *str);
		void CheckTabs(std::string *str);


	private:
		bool _flag_loc;
		int _count_serv;
		int _pos_loc;
		int _pos_serv;
		int _count_tab;

		std::vector <ParseConfig *> _servinfo;
		std::vector < std::vector <std::string> > _loc_path;
		std::map < int, std::map<int, std::string> > _methods;
		std::map <std::string, std::string> _error_pages;
		std::map < std::string, std::map<std::string, std::string> > _location;
		std::map <std::string, std::string> _head_fields;
};


#endif
