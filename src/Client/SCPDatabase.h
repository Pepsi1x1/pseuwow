#ifndef _SCPDATABASE_H
#define _SCPDATABASE_H

#include "DefScript/TypeStorage.h"
#include <set>

enum SCPFieldTypes
{
    SCP_TYPE_INT = 0,
    SCP_TYPE_FLOAT = 1,
    SCP_TYPE_STRING = 2
};

struct SCPFieldDef
{
    uint32 id;
    uint8 type;
};

#define SCP_INVALID_INT 0xFFFFFFFF

typedef std::map<std::string,std::string> SCPEntryMap;
typedef std::map<uint32,SCPEntryMap> SCPFieldMap;
typedef std::set<std::string> SCPSourceList;

class SCPDatabase
{
    friend class SCPDatabaseMgr;
public:
    SCPDatabase();
    ~SCPDatabase();

    // if the database is compacted, do not allow any modification from outside
    SCPSourceList *GetSources(void) { return _compact ? NULL : &sources; }
    SCPFieldMap *GetFields(void) { return _compact ? NULL : &fields; }
    inline bool IsCompact(void) { return _compact; }
    inline std::string GetName(void) { return _name; }
    void DropAll(void);
    void DropTextData(void);

    // access funcs
    void *GetPtr(uint32 index, char *entry);
    void *GetPtrByField(uint32 index, uint32 entry);
    inline char *GetStringByOffset(uint32 offs) { return (char*)(offs < _stringsize ? _stringbuf + offs : ""); }
    inline char *GetString(uint32 index, char *entry) { return GetStringByOffset(GetUint32(index,entry)); }
    inline char *GetString(uint32 index, uint32 entry) { return GetStringByOffset(GetUint32(index,entry)); }
    inline uint32 GetUint32(uint32 index, char *entry) { uint32 *t = (uint32*)GetPtr(index,entry); return t ? *t : 0; }
    inline uint32 GetUint32(uint32 index, uint32 entry) { uint32 *t = (uint32*)GetPtrByField(index,entry); return t ? *t : 0; }
    inline int32 GetInt(uint32 index, char *entry) { int32 *t = (int32*)GetPtr(index,entry); return t ? *t : 0; }
    inline int32 GetInt(uint32 index, uint32 entry) { int32 *t = (int32*)GetPtrByField(index,entry); return t ? *t : 0; }
    inline float GetFloat(uint32 index, char *entry) { float *t = (float*)GetPtr(index,entry); return t ? *t : 0; }
    inline float GetFloat(uint32 index, uint32 entry) { float *t = (float*)GetPtrByField(index,entry); return t ? *t : 0; }
    uint32 GetFieldType(char *entry);
    uint32 GetFieldId(char *entry);
    inline void *GetRowByIndex(uint32 index) { return GetPtrByField(index,0); }
    uint32 GetFieldByUint32Value(char *entry, uint32 val);
    uint32 GetFieldByUint32Value(uint32 entry, uint32 val);
    uint32 GetFieldByIntValue(char *entry, int32 val);
    uint32 GetFieldByIntValue(uint32 entry, int32 val);
    uint32 GetFieldByStringValue(char *entry, char *val);
    uint32 GetFieldByStringValue(uint32 entry, char *val);
    // float value lookup not necessary
    inline uint32 GetFieldsCount(void) { return _fields_per_row; }
    inline uint32 GetRowsCount(void) { return _rowcount; }


    void DumpStructureToFile(char *fn);
private:
    // text data related
    SCPSourceList sources;
    SCPFieldMap fields;

    // binary data related
    bool _compact;
    std::string _name;
    uint32 _rowcount;
    uint32 _fields_per_row;
    char *_stringbuf;
    uint32 _stringsize;
    uint32 *_intbuf;
    std::map<uint32,uint32> _indexes, _indexes_reverse; // stores index-to-rowID, rowID-to-index
    std::map<std::string,SCPFieldDef> _fielddefs;
};

typedef TypeStorage<SCPDatabase> SCPDatabaseMap;


class SCPDatabaseMgr
{
    friend class SCPDatabase;
public:
    SCPDatabase *GetDB(std::string n, bool create = false);
    uint32 AutoLoadFile(char *fn);
    inline void DropDB(std::string s) { _map.Delete(stringToLower(s)); }
    bool Compact(char *dbname, char *outfile);
    static uint32 GetDataTypeFromString(char *s);
    uint32 SearchAndLoad(char*,bool);
    void AddSearchPath(char*);
    bool LoadCompactSCP(char*, char*);

private:
    SCPDatabaseMap _map;
    std::deque<std::string> _paths;
};




#endif
