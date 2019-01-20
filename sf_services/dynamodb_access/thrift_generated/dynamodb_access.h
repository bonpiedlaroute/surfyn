/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef dynamodb_access_H
#define dynamodb_access_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "dynamodb_access_types.h"



#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class dynamodb_accessIf {
 public:
  virtual ~dynamodb_accessIf() {}
  virtual void put(OperationResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & values) = 0;
  virtual void get(GetResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & attributestoget) = 0;
  virtual void scan(ScanReqResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & attributestoget, const std::string& filterexpression) = 0;
  virtual void remove(OperationResult& _return, const std::string& tablename, const KeyValue& key) = 0;
  virtual void update(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & values) = 0;
  virtual void createTable(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, std::string> & properties) = 0;
  virtual void deleteTable(OperationResult& _return, const std::string& tablename) = 0;
};

class dynamodb_accessIfFactory {
 public:
  typedef dynamodb_accessIf Handler;

  virtual ~dynamodb_accessIfFactory() {}

  virtual dynamodb_accessIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(dynamodb_accessIf* /* handler */) = 0;
};

class dynamodb_accessIfSingletonFactory : virtual public dynamodb_accessIfFactory {
 public:
  dynamodb_accessIfSingletonFactory(const std::shared_ptr<dynamodb_accessIf>& iface) : iface_(iface) {}
  virtual ~dynamodb_accessIfSingletonFactory() {}

  virtual dynamodb_accessIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(dynamodb_accessIf* /* handler */) {}

 protected:
  std::shared_ptr<dynamodb_accessIf> iface_;
};

class dynamodb_accessNull : virtual public dynamodb_accessIf {
 public:
  virtual ~dynamodb_accessNull() {}
  void put(OperationResult& /* _return */, const std::string& /* tablename */, const std::map<std::string, ValueType> & /* values */) {
    return;
  }
  void get(GetResult& /* _return */, const std::string& /* tablename */, const KeyValue& /* key */, const std::map<std::string, ValueType> & /* attributestoget */) {
    return;
  }
  void scan(ScanReqResult& /* _return */, const std::string& /* tablename */, const std::map<std::string, ValueType> & /* attributestoget */, const std::string& /* filterexpression */) {
    return;
  }
  void remove(OperationResult& /* _return */, const std::string& /* tablename */, const KeyValue& /* key */) {
    return;
  }
  void update(OperationResult& /* _return */, const std::string& /* tablename */, const KeyValue& /* key */, const std::map<std::string, ValueType> & /* values */) {
    return;
  }
  void createTable(OperationResult& /* _return */, const std::string& /* tablename */, const KeyValue& /* key */, const std::map<std::string, std::string> & /* properties */) {
    return;
  }
  void deleteTable(OperationResult& /* _return */, const std::string& /* tablename */) {
    return;
  }
};

typedef struct _dynamodb_access_put_args__isset {
  _dynamodb_access_put_args__isset() : tablename(false), values(false) {}
  bool tablename :1;
  bool values :1;
} _dynamodb_access_put_args__isset;

class dynamodb_access_put_args {
 public:

  dynamodb_access_put_args(const dynamodb_access_put_args&);
  dynamodb_access_put_args& operator=(const dynamodb_access_put_args&);
  dynamodb_access_put_args() : tablename() {
  }

  virtual ~dynamodb_access_put_args() throw();
  std::string tablename;
  std::map<std::string, ValueType>  values;

  _dynamodb_access_put_args__isset __isset;

  void __set_tablename(const std::string& val);

  void __set_values(const std::map<std::string, ValueType> & val);

  bool operator == (const dynamodb_access_put_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    if (!(values == rhs.values))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_put_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_put_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_put_pargs {
 public:


  virtual ~dynamodb_access_put_pargs() throw();
  const std::string* tablename;
  const std::map<std::string, ValueType> * values;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_put_result__isset {
  _dynamodb_access_put_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_put_result__isset;

class dynamodb_access_put_result {
 public:

  dynamodb_access_put_result(const dynamodb_access_put_result&);
  dynamodb_access_put_result& operator=(const dynamodb_access_put_result&);
  dynamodb_access_put_result() {
  }

  virtual ~dynamodb_access_put_result() throw();
  OperationResult success;

  _dynamodb_access_put_result__isset __isset;

  void __set_success(const OperationResult& val);

  bool operator == (const dynamodb_access_put_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_put_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_put_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_put_presult__isset {
  _dynamodb_access_put_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_put_presult__isset;

class dynamodb_access_put_presult {
 public:


  virtual ~dynamodb_access_put_presult() throw();
  OperationResult* success;

  _dynamodb_access_put_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _dynamodb_access_get_args__isset {
  _dynamodb_access_get_args__isset() : tablename(false), key(false), attributestoget(false) {}
  bool tablename :1;
  bool key :1;
  bool attributestoget :1;
} _dynamodb_access_get_args__isset;

class dynamodb_access_get_args {
 public:

  dynamodb_access_get_args(const dynamodb_access_get_args&);
  dynamodb_access_get_args& operator=(const dynamodb_access_get_args&);
  dynamodb_access_get_args() : tablename() {
  }

  virtual ~dynamodb_access_get_args() throw();
  std::string tablename;
  KeyValue key;
  std::map<std::string, ValueType>  attributestoget;

  _dynamodb_access_get_args__isset __isset;

  void __set_tablename(const std::string& val);

  void __set_key(const KeyValue& val);

  void __set_attributestoget(const std::map<std::string, ValueType> & val);

  bool operator == (const dynamodb_access_get_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    if (!(key == rhs.key))
      return false;
    if (!(attributestoget == rhs.attributestoget))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_get_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_get_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_get_pargs {
 public:


  virtual ~dynamodb_access_get_pargs() throw();
  const std::string* tablename;
  const KeyValue* key;
  const std::map<std::string, ValueType> * attributestoget;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_get_result__isset {
  _dynamodb_access_get_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_get_result__isset;

class dynamodb_access_get_result {
 public:

  dynamodb_access_get_result(const dynamodb_access_get_result&);
  dynamodb_access_get_result& operator=(const dynamodb_access_get_result&);
  dynamodb_access_get_result() {
  }

  virtual ~dynamodb_access_get_result() throw();
  GetResult success;

  _dynamodb_access_get_result__isset __isset;

  void __set_success(const GetResult& val);

  bool operator == (const dynamodb_access_get_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_get_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_get_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_get_presult__isset {
  _dynamodb_access_get_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_get_presult__isset;

class dynamodb_access_get_presult {
 public:


  virtual ~dynamodb_access_get_presult() throw();
  GetResult* success;

  _dynamodb_access_get_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _dynamodb_access_scan_args__isset {
  _dynamodb_access_scan_args__isset() : tablename(false), attributestoget(false), filterexpression(false) {}
  bool tablename :1;
  bool attributestoget :1;
  bool filterexpression :1;
} _dynamodb_access_scan_args__isset;

class dynamodb_access_scan_args {
 public:

  dynamodb_access_scan_args(const dynamodb_access_scan_args&);
  dynamodb_access_scan_args& operator=(const dynamodb_access_scan_args&);
  dynamodb_access_scan_args() : tablename(), filterexpression() {
  }

  virtual ~dynamodb_access_scan_args() throw();
  std::string tablename;
  std::map<std::string, ValueType>  attributestoget;
  std::string filterexpression;

  _dynamodb_access_scan_args__isset __isset;

  void __set_tablename(const std::string& val);

  void __set_attributestoget(const std::map<std::string, ValueType> & val);

  void __set_filterexpression(const std::string& val);

  bool operator == (const dynamodb_access_scan_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    if (!(attributestoget == rhs.attributestoget))
      return false;
    if (!(filterexpression == rhs.filterexpression))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_scan_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_scan_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_scan_pargs {
 public:


  virtual ~dynamodb_access_scan_pargs() throw();
  const std::string* tablename;
  const std::map<std::string, ValueType> * attributestoget;
  const std::string* filterexpression;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_scan_result__isset {
  _dynamodb_access_scan_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_scan_result__isset;

class dynamodb_access_scan_result {
 public:

  dynamodb_access_scan_result(const dynamodb_access_scan_result&);
  dynamodb_access_scan_result& operator=(const dynamodb_access_scan_result&);
  dynamodb_access_scan_result() {
  }

  virtual ~dynamodb_access_scan_result() throw();
  ScanReqResult success;

  _dynamodb_access_scan_result__isset __isset;

  void __set_success(const ScanReqResult& val);

  bool operator == (const dynamodb_access_scan_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_scan_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_scan_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_scan_presult__isset {
  _dynamodb_access_scan_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_scan_presult__isset;

class dynamodb_access_scan_presult {
 public:


  virtual ~dynamodb_access_scan_presult() throw();
  ScanReqResult* success;

  _dynamodb_access_scan_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _dynamodb_access_remove_args__isset {
  _dynamodb_access_remove_args__isset() : tablename(false), key(false) {}
  bool tablename :1;
  bool key :1;
} _dynamodb_access_remove_args__isset;

class dynamodb_access_remove_args {
 public:

  dynamodb_access_remove_args(const dynamodb_access_remove_args&);
  dynamodb_access_remove_args& operator=(const dynamodb_access_remove_args&);
  dynamodb_access_remove_args() : tablename() {
  }

  virtual ~dynamodb_access_remove_args() throw();
  std::string tablename;
  KeyValue key;

  _dynamodb_access_remove_args__isset __isset;

  void __set_tablename(const std::string& val);

  void __set_key(const KeyValue& val);

  bool operator == (const dynamodb_access_remove_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_remove_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_remove_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_remove_pargs {
 public:


  virtual ~dynamodb_access_remove_pargs() throw();
  const std::string* tablename;
  const KeyValue* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_remove_result__isset {
  _dynamodb_access_remove_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_remove_result__isset;

class dynamodb_access_remove_result {
 public:

  dynamodb_access_remove_result(const dynamodb_access_remove_result&);
  dynamodb_access_remove_result& operator=(const dynamodb_access_remove_result&);
  dynamodb_access_remove_result() {
  }

  virtual ~dynamodb_access_remove_result() throw();
  OperationResult success;

  _dynamodb_access_remove_result__isset __isset;

  void __set_success(const OperationResult& val);

  bool operator == (const dynamodb_access_remove_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_remove_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_remove_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_remove_presult__isset {
  _dynamodb_access_remove_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_remove_presult__isset;

class dynamodb_access_remove_presult {
 public:


  virtual ~dynamodb_access_remove_presult() throw();
  OperationResult* success;

  _dynamodb_access_remove_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _dynamodb_access_update_args__isset {
  _dynamodb_access_update_args__isset() : tablename(false), key(false), values(false) {}
  bool tablename :1;
  bool key :1;
  bool values :1;
} _dynamodb_access_update_args__isset;

class dynamodb_access_update_args {
 public:

  dynamodb_access_update_args(const dynamodb_access_update_args&);
  dynamodb_access_update_args& operator=(const dynamodb_access_update_args&);
  dynamodb_access_update_args() : tablename() {
  }

  virtual ~dynamodb_access_update_args() throw();
  std::string tablename;
  KeyValue key;
  std::map<std::string, ValueType>  values;

  _dynamodb_access_update_args__isset __isset;

  void __set_tablename(const std::string& val);

  void __set_key(const KeyValue& val);

  void __set_values(const std::map<std::string, ValueType> & val);

  bool operator == (const dynamodb_access_update_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    if (!(key == rhs.key))
      return false;
    if (!(values == rhs.values))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_update_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_update_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_update_pargs {
 public:


  virtual ~dynamodb_access_update_pargs() throw();
  const std::string* tablename;
  const KeyValue* key;
  const std::map<std::string, ValueType> * values;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_update_result__isset {
  _dynamodb_access_update_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_update_result__isset;

class dynamodb_access_update_result {
 public:

  dynamodb_access_update_result(const dynamodb_access_update_result&);
  dynamodb_access_update_result& operator=(const dynamodb_access_update_result&);
  dynamodb_access_update_result() {
  }

  virtual ~dynamodb_access_update_result() throw();
  OperationResult success;

  _dynamodb_access_update_result__isset __isset;

  void __set_success(const OperationResult& val);

  bool operator == (const dynamodb_access_update_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_update_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_update_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_update_presult__isset {
  _dynamodb_access_update_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_update_presult__isset;

class dynamodb_access_update_presult {
 public:


  virtual ~dynamodb_access_update_presult() throw();
  OperationResult* success;

  _dynamodb_access_update_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _dynamodb_access_createTable_args__isset {
  _dynamodb_access_createTable_args__isset() : tablename(false), key(false), properties(false) {}
  bool tablename :1;
  bool key :1;
  bool properties :1;
} _dynamodb_access_createTable_args__isset;

class dynamodb_access_createTable_args {
 public:

  dynamodb_access_createTable_args(const dynamodb_access_createTable_args&);
  dynamodb_access_createTable_args& operator=(const dynamodb_access_createTable_args&);
  dynamodb_access_createTable_args() : tablename() {
  }

  virtual ~dynamodb_access_createTable_args() throw();
  std::string tablename;
  KeyValue key;
  std::map<std::string, std::string>  properties;

  _dynamodb_access_createTable_args__isset __isset;

  void __set_tablename(const std::string& val);

  void __set_key(const KeyValue& val);

  void __set_properties(const std::map<std::string, std::string> & val);

  bool operator == (const dynamodb_access_createTable_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    if (!(key == rhs.key))
      return false;
    if (!(properties == rhs.properties))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_createTable_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_createTable_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_createTable_pargs {
 public:


  virtual ~dynamodb_access_createTable_pargs() throw();
  const std::string* tablename;
  const KeyValue* key;
  const std::map<std::string, std::string> * properties;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_createTable_result__isset {
  _dynamodb_access_createTable_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_createTable_result__isset;

class dynamodb_access_createTable_result {
 public:

  dynamodb_access_createTable_result(const dynamodb_access_createTable_result&);
  dynamodb_access_createTable_result& operator=(const dynamodb_access_createTable_result&);
  dynamodb_access_createTable_result() {
  }

  virtual ~dynamodb_access_createTable_result() throw();
  OperationResult success;

  _dynamodb_access_createTable_result__isset __isset;

  void __set_success(const OperationResult& val);

  bool operator == (const dynamodb_access_createTable_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_createTable_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_createTable_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_createTable_presult__isset {
  _dynamodb_access_createTable_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_createTable_presult__isset;

class dynamodb_access_createTable_presult {
 public:


  virtual ~dynamodb_access_createTable_presult() throw();
  OperationResult* success;

  _dynamodb_access_createTable_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _dynamodb_access_deleteTable_args__isset {
  _dynamodb_access_deleteTable_args__isset() : tablename(false) {}
  bool tablename :1;
} _dynamodb_access_deleteTable_args__isset;

class dynamodb_access_deleteTable_args {
 public:

  dynamodb_access_deleteTable_args(const dynamodb_access_deleteTable_args&);
  dynamodb_access_deleteTable_args& operator=(const dynamodb_access_deleteTable_args&);
  dynamodb_access_deleteTable_args() : tablename() {
  }

  virtual ~dynamodb_access_deleteTable_args() throw();
  std::string tablename;

  _dynamodb_access_deleteTable_args__isset __isset;

  void __set_tablename(const std::string& val);

  bool operator == (const dynamodb_access_deleteTable_args & rhs) const
  {
    if (!(tablename == rhs.tablename))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_deleteTable_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_deleteTable_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class dynamodb_access_deleteTable_pargs {
 public:


  virtual ~dynamodb_access_deleteTable_pargs() throw();
  const std::string* tablename;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_deleteTable_result__isset {
  _dynamodb_access_deleteTable_result__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_deleteTable_result__isset;

class dynamodb_access_deleteTable_result {
 public:

  dynamodb_access_deleteTable_result(const dynamodb_access_deleteTable_result&);
  dynamodb_access_deleteTable_result& operator=(const dynamodb_access_deleteTable_result&);
  dynamodb_access_deleteTable_result() {
  }

  virtual ~dynamodb_access_deleteTable_result() throw();
  OperationResult success;

  _dynamodb_access_deleteTable_result__isset __isset;

  void __set_success(const OperationResult& val);

  bool operator == (const dynamodb_access_deleteTable_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const dynamodb_access_deleteTable_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dynamodb_access_deleteTable_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _dynamodb_access_deleteTable_presult__isset {
  _dynamodb_access_deleteTable_presult__isset() : success(false) {}
  bool success :1;
} _dynamodb_access_deleteTable_presult__isset;

class dynamodb_access_deleteTable_presult {
 public:


  virtual ~dynamodb_access_deleteTable_presult() throw();
  OperationResult* success;

  _dynamodb_access_deleteTable_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class dynamodb_accessClient : virtual public dynamodb_accessIf {
 public:
#ifdef _WIN32
  dynamodb_accessClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  dynamodb_accessClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
#else
  dynamodb_accessClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  dynamodb_accessClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
#endif
  void put(OperationResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & values);
  void send_put(const std::string& tablename, const std::map<std::string, ValueType> & values);
  void recv_put(OperationResult& _return);
  void get(GetResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & attributestoget);
  void send_get(const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & attributestoget);
  void recv_get(GetResult& _return);
  void scan(ScanReqResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & attributestoget, const std::string& filterexpression);
  void send_scan(const std::string& tablename, const std::map<std::string, ValueType> & attributestoget, const std::string& filterexpression);
  void recv_scan(ScanReqResult& _return);
  void remove(OperationResult& _return, const std::string& tablename, const KeyValue& key);
  void send_remove(const std::string& tablename, const KeyValue& key);
  void recv_remove(OperationResult& _return);
  void update(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & values);
  void send_update(const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & values);
  void recv_update(OperationResult& _return);
  void createTable(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, std::string> & properties);
  void send_createTable(const std::string& tablename, const KeyValue& key, const std::map<std::string, std::string> & properties);
  void recv_createTable(OperationResult& _return);
  void deleteTable(OperationResult& _return, const std::string& tablename);
  void send_deleteTable(const std::string& tablename);
  void recv_deleteTable(OperationResult& _return);
 protected:
#ifdef _WIN32
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
#else
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
#endif
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class dynamodb_accessProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
#ifdef _WIN32
  std::shared_ptr<dynamodb_accessIf> iface_;
#else
  boost::shared_ptr<dynamodb_accessIf> iface_;
#endif
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (dynamodb_accessProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_put(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_get(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_scan(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_remove(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_update(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_createTable(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_deleteTable(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
#ifdef _WIN32
  dynamodb_accessProcessor(std::shared_ptr<dynamodb_accessIf> iface) :
#else
     dynamodb_accessProcessor(boost::shared_ptr<dynamodb_accessIf> iface) :
#endif
    iface_(iface) {
    processMap_["put"] = &dynamodb_accessProcessor::process_put;
    processMap_["get"] = &dynamodb_accessProcessor::process_get;
    processMap_["scan"] = &dynamodb_accessProcessor::process_scan;
    processMap_["remove"] = &dynamodb_accessProcessor::process_remove;
    processMap_["update"] = &dynamodb_accessProcessor::process_update;
    processMap_["createTable"] = &dynamodb_accessProcessor::process_createTable;
    processMap_["deleteTable"] = &dynamodb_accessProcessor::process_deleteTable;
  }

  virtual ~dynamodb_accessProcessor() {}
};

class dynamodb_accessProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
#if _WIN32
  dynamodb_accessProcessorFactory(const ::std::shared_ptr< dynamodb_accessIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);
#else
  dynamodb_accessProcessorFactory(const ::boost::shared_ptr< dynamodb_accessIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}
  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);
#endif

 protected:
#ifdef _WIN32
  ::std::shared_ptr< dynamodb_accessIfFactory > handlerFactory_;
#else
  ::boost::shared_ptr< dynamodb_accessIfFactory > handlerFactory_;
#endif
};

class dynamodb_accessMultiface : virtual public dynamodb_accessIf {
 public:
  dynamodb_accessMultiface(std::vector<std::shared_ptr<dynamodb_accessIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~dynamodb_accessMultiface() {}
 protected:
  std::vector<std::shared_ptr<dynamodb_accessIf> > ifaces_;
  dynamodb_accessMultiface() {}
  void add(std::shared_ptr<dynamodb_accessIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void put(OperationResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & values) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->put(_return, tablename, values);
    }
    ifaces_[i]->put(_return, tablename, values);
    return;
  }

  void get(GetResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & attributestoget) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->get(_return, tablename, key, attributestoget);
    }
    ifaces_[i]->get(_return, tablename, key, attributestoget);
    return;
  }

  void scan(ScanReqResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & attributestoget, const std::string& filterexpression) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->scan(_return, tablename, attributestoget, filterexpression);
    }
    ifaces_[i]->scan(_return, tablename, attributestoget, filterexpression);
    return;
  }

  void remove(OperationResult& _return, const std::string& tablename, const KeyValue& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->remove(_return, tablename, key);
    }
    ifaces_[i]->remove(_return, tablename, key);
    return;
  }

  void update(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & values) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->update(_return, tablename, key, values);
    }
    ifaces_[i]->update(_return, tablename, key, values);
    return;
  }

  void createTable(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, std::string> & properties) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->createTable(_return, tablename, key, properties);
    }
    ifaces_[i]->createTable(_return, tablename, key, properties);
    return;
  }

  void deleteTable(OperationResult& _return, const std::string& tablename) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->deleteTable(_return, tablename);
    }
    ifaces_[i]->deleteTable(_return, tablename);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class dynamodb_accessConcurrentClient : virtual public dynamodb_accessIf {
 public:
  dynamodb_accessConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  dynamodb_accessConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void put(OperationResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & values);
  int32_t send_put(const std::string& tablename, const std::map<std::string, ValueType> & values);
  void recv_put(OperationResult& _return, const int32_t seqid);
  void get(GetResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & attributestoget);
  int32_t send_get(const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & attributestoget);
  void recv_get(GetResult& _return, const int32_t seqid);
  void scan(ScanReqResult& _return, const std::string& tablename, const std::map<std::string, ValueType> & attributestoget, const std::string& filterexpression);
  int32_t send_scan(const std::string& tablename, const std::map<std::string, ValueType> & attributestoget, const std::string& filterexpression);
  void recv_scan(ScanReqResult& _return, const int32_t seqid);
  void remove(OperationResult& _return, const std::string& tablename, const KeyValue& key);
  int32_t send_remove(const std::string& tablename, const KeyValue& key);
  void recv_remove(OperationResult& _return, const int32_t seqid);
  void update(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & values);
  int32_t send_update(const std::string& tablename, const KeyValue& key, const std::map<std::string, ValueType> & values);
  void recv_update(OperationResult& _return, const int32_t seqid);
  void createTable(OperationResult& _return, const std::string& tablename, const KeyValue& key, const std::map<std::string, std::string> & properties);
  int32_t send_createTable(const std::string& tablename, const KeyValue& key, const std::map<std::string, std::string> & properties);
  void recv_createTable(OperationResult& _return, const int32_t seqid);
  void deleteTable(OperationResult& _return, const std::string& tablename);
  int32_t send_deleteTable(const std::string& tablename);
  void recv_deleteTable(OperationResult& _return, const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif



#endif
