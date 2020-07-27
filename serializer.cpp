#include "serializer.h"

#include <utility>

using namespace std;

FileManager::FileManager(string inp, string out)
	: _inp_nm(move(inp))
	, _out_nm(move(out))
{}

void FileManager::Open_Files()
{
    _f_inp = ifstream(_inp_nm);
    if (!_f_inp)
    {
        cerr << "Input file with path " << _inp_nm << " couldn't be opened\n";
        exit(1);
    }
    _f_out = ofstream(_out_nm);
    if (!_f_out)
    {
        cerr << "Output file with path " << _out_nm << " couldn't be found or created\n";
        exit(1);
    }
}

optional<variant<int, double, string>> FileManager::Read_Node()
{
	char type;
	_f_inp >> type;
	variant<int, double, string> data;
	if (type == 'i')
	{
		int i_num;
		_f_inp >> i_num;
		data = i_num;
	}
	else if (type == 'd')
	{
		double d_num;
		_f_inp >> d_num;
		data = d_num;
	}
	else if (type == 's')
	{
		string str;
		_f_inp >> str;
		data = move(str);
	}
	else if (type == '/' || type == 0)
		return nullopt;
	else
	{
		cerr << "Node type with identification [" << type << "] cann't be in input file\n";
		exit(1);
	}
	return data;
}

bool FileManager::Is_Nxt_Child()
{
	char dummy = _f_inp.get();
	if (dummy == -1)
		return false;
	char nxt = _f_inp.peek();
    return nxt != '/';
}

void FileManager::Deserialize(shared_ptr<TreeWrapper> &root)
{
	auto data_type = Read_Node();
	if (!data_type)
	    return;

    auto &var = *data_type;
    if (holds_alternative<int>(var))
        root = make_shared<TreeNode<int>>(get<int>(var), 'i');
    else if (holds_alternative<double>(var))
        root = make_shared<TreeNode<double>>(get<double>(var), 'd');
    else
        root = make_shared<TreeNode<string>>(get<string>(var), 's');

    auto &childs = root->Get_Child();
    while (Is_Nxt_Child())
	{
    	childs.push_back(nullptr);
    	Deserialize(childs.back());
	}

    char dummy;
    _f_inp >> dummy;
}

void FileManager::Serialize(const TreeWrapper *root) const
{
    if (!root)
        return ;
    char type_node = root->Get_Type();
    _f_out << type_node;
    if (type_node == 'i')
    {
        int data = dynamic_cast<const TreeNode<int> *>(root)->Get_Data();
        _f_out << data << ' ';
    }
    else if (type_node == 'd')
    {
        double data = dynamic_cast<const TreeNode<double> *>(root)->Get_Data();
        _f_out << data << ' ';
    }
    else if (type_node == 's')
    {
        string data = dynamic_cast<const TreeNode<string> *>(root)->Get_Data();
        _f_out << data << ' ';
    }

    for (const auto &curr_child : root->Get_Child())
        Serialize(curr_child.get());

    _f_out << NULL_MARK << endl;
}
