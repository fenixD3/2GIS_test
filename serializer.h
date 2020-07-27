#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <variant>
#include <string>
#include <optional>

#include "tree.h"

class FileManager
{
private:
	std::string _inp_nm, _out_nm;
	std::ifstream _f_inp;
    mutable std::ofstream _f_out;

    bool Is_Nxt_Child();
public:
	const static char NULL_MARK = '/';

	FileManager(std::string inp, std::string out);

	std::optional<std::variant<int, double, std::string>> Read_Node();
	void Open_Files();
	void Deserialize(std::shared_ptr<TreeWrapper> &root);
    void Serialize(const TreeWrapper *root) const;
};
