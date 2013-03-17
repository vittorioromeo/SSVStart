#include "UtilsJson.h"
#include "Log/Log.h"
#include "FileSystem/FileSystem.h"

using namespace std;
using namespace Json;
using namespace ssvs::FileSystem;

namespace ssvs
{
	namespace UtilsJson
	{
		template<> int getValue(const Value& mRoot, const string& mValue) 			{ return mRoot[mValue].asInt(); }
		template<> float getValue(const Value& mRoot, const string& mValue) 		{ return mRoot[mValue].asFloat(); }
		template<> double getValue(const Value& mRoot, const string& mValue) 		{ return mRoot[mValue].asDouble(); }
		template<> bool getValue(const Value& mRoot, const string& mValue) 			{ return mRoot[mValue].asBool(); }
		template<> string getValue(const Value& mRoot, const string& mValue) 		{ return mRoot[mValue].asString(); }
		template<> char const* getValue(const Value& mRoot, const string& mValue)	{ return mRoot[mValue].asCString(); }

		template<> int getArrayValue(const Value& mArray, int mIndex)				{ return mArray[mIndex].asInt(); }
		template<> float getArrayValue(const Value& mArray, int mIndex)				{ return mArray[mIndex].asFloat(); }
		template<> double getArrayValue(const Value& mArray, int mIndex)			{ return mArray[mIndex].asDouble(); }
		template<> bool getArrayValue(const Value& mArray, int mIndex)				{ return mArray[mIndex].asBool(); }
		template<> string getArrayValue(const Value& mArray, int mIndex)			{ return mArray[mIndex].asString(); }
		template<> char const* getArrayValue(const Value& mArray, int mIndex)		{ return mArray[mIndex].asCString(); }

		Value getRootFromString(const string& mString)
		{
			Value result; Reader reader;
			if(!reader.parse(mString, result, false)) log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mString + "]", "JSON Error");
			return result;
		}
		Value getRootFromFile(const string& mPath)
		{
			Value result; Reader reader;
			if(!reader.parse(getFileContents(mPath), result, false)) log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mPath + "]", "JSON Error");
			return result;
		}
	}
}

