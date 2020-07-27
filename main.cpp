#include <string_view>
#include <cstring>

#include "tree.h"
#include "serializer.h"

using namespace std;

void Write_To_Out(const TreeWrapper *root, ostream& out = cout)
{
	static size_t level = 0;
	if (!root)
		return ;

	if (level)
		for (size_t i = 0; i < level; ++i)
			out << "\t|";

	char type_node = root->Get_Type();
	if (type_node == 'i')
	{
		int data = dynamic_cast<const TreeNode<int> *>(root)->Get_Data();
		out << data << endl << "|";
	}
	else if (type_node == 'd')
	{
		double data = dynamic_cast<const TreeNode<double> *>(root)->Get_Data();
		out << data << endl << "|";
	}
	else if (type_node == 's')
	{
		string data = dynamic_cast<const TreeNode<string> *>(root)->Get_Data();
		out << '\"' << data << '\"' << endl << "|";
	}

	for (const auto &curr_child : root->Get_Child())
	{
		++level;
		Write_To_Out(curr_child.get());
	}

	--level;
}

FileManager Parse_Args(int ac, char **av)
{
	if (ac <= 1)
	{
		cerr << "Usage: ./tree -i <input file name> -o <output file name>\n";
		exit(1);
	}
	string input_nm, output_nm;
	for (int i = 1; i < ac; ++i)
	{
		if (!strcmp(av[i], "-i"))
			input_nm = av[++i];
		else if (!strcmp(av[i], "-o"))
			output_nm = av[++i];
		else
		{
            cerr << "Flags should be -i and -o!\n";
            exit(1);
        }
	}
	return FileManager(move(input_nm), move(output_nm));
}

int main(int ac, char **av)
{
	FileManager fm = Parse_Args(ac, av);
	fm.Open_Files();
	shared_ptr<TreeWrapper> root = nullptr;
	fm.Deserialize(root);
	Write_To_Out(root.get());
	fm.Serialize(root.get());
	return 0;
}
