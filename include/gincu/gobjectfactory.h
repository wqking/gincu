#ifndef GOBJECTFACTORY_H
#define GOBJECTFACTORY_H

#include "cpgf/gcallback.h"

#include <string>
#include <vector>
#include <map>

namespace gincu {

class GObjectFactoryBase
{
public:
	const std::vector<std::string> & getNameList() const { return this->nameList; }

protected:
	std::vector<std::string> & getMutableNameList() { return this->nameList; }
	void raiseCantFindError(const std::string & name) const;

private:
	std::vector<std::string> nameList;
};

template <typename T>
struct GAfterObjectCreated
{
	static void afterCreated(T * /*object*/, const std::string & /*name*/)
	{
	}
};

template <typename T>
struct GAfterObjectCreatedSetName
{
	static void afterCreated(T * object, const std::string & name)
	{
		object->setName(name);
	}
};

template <typename T, typename AfterCreated = GAfterObjectCreated<T>, typename ParamType = char>
class GObjectFactory : public GObjectFactoryBase
{
private:
	typedef GObjectFactoryBase super;

public:
	typedef T ObjectType;

	typedef cpgf::GCallback<T * ()> ObjectCreator;

	struct RegisterEntry
	{
		std::string name;
		ObjectCreator creator;
		ParamType param;
	};

private:
	typedef std::map<std::string, RegisterEntry> RegisterEntryMap;

public:
	void registerObject(
		const std::string & name,
		ObjectCreator creator,
		const ParamType & param
	)
	{
		this->getMutableNameList().push_back(name);

		RegisterEntry entry {
			name,
			creator,
			param
		};

		this->entryMap.insert(std::make_pair(entry.name, entry));
	}

	void registerObject(
		const std::string & name,
		ObjectCreator creator
	)
	{
		this->registerObject(name, creator, ParamType());
	}

	T * createObject(const std::string & name) const
	{
		const RegisterEntry * entry = this->getEntry(name);
		T * object = entry->creator();
		AfterCreated::afterCreated(object, name);

		return object;
	}

	const ParamType & getParam(const std::string & name) const
	{
		return this->getEntry(name)->param;
	}

	bool has(const std::string & name) const
	{
		return this->getEntry(name) != nullptr;
	}

private:
	const RegisterEntry * getEntry(const std::string & name) const
	{
		typename RegisterEntryMap::const_iterator it = this->entryMap.find(name);
		if(it == this->entryMap.end()) {
			this->raiseCantFindError(name);
			return nullptr;
		}
		else {
			return &it->second;
		}
	}

private:
	RegisterEntryMap entryMap;
};

template <typename T>
T * objectFactoryCreator()
{
	return new T();
}


} //namespace gincu


#endif

