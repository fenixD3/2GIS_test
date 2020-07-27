#pragma once

#include <list>
#include <memory>
#include <utility>

class TreeWrapper
{
protected:
	char _type_id;
	std::list<std::shared_ptr<TreeWrapper>> _childs;

public:
	virtual ~TreeWrapper() = default;

	TreeWrapper(char type)
		: _type_id(type)
	{}

	char Get_Type() const
	{
		return _type_id;
	}

	std::list<std::shared_ptr<TreeWrapper>>& Get_Child()
	{
		return _childs;
	}

    const std::list<std::shared_ptr<TreeWrapper>>& Get_Child() const
    {
        return _childs;
    }
};

template<typename D>
class TreeNode : public TreeWrapper
{
private:
	D _data;
public:
	TreeNode(D data, char type)
		: TreeWrapper(type)
		, _data(std::move(data))
	{}

	D Get_Data() const
    {
        return _data;
    }
};
