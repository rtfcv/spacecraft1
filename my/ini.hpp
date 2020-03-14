#ifndef _MYINI_H
#define _MYINI_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

//using namespace boost::property_tree;
namespace my{

	class ini{
		boost::property_tree::ptree pt;
		public:
		double dread(std::string key){
			boost::optional<double> indat=pt.get_optional<double>(key);
			return indat.get();
		}

		std::string read(std::string key){
			boost::optional<std::string> indat=pt.get_optional<std::string>(key);
			return indat.get();
		}

		template<typename T>
		T read(std::string key){
			boost::optional<T> indat=pt.get_optional<T>(key);
			return indat.get();
		}

		ini(std::string fname){
			boost::property_tree::read_ini(fname, pt);
		}
	};
}
#endif
