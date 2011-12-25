#pragma once

#include <boost/shared_ptr.hpp>

#include "ObjectBase.hpp"
#include "DataBase/DataBaseNode.hpp"

namespace Common
{
namespace Game
{
namespace Object
{

class ObjectFactory
{
public:
	boost::shared_ptr<ObjectBase> create(DataBase::DataBaseNode & data);
};

}
}
}
