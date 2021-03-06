/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef emailalertservice_H
#define emailalertservice_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "emailalertservice_types.h"



#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class emailalertserviceIf {
 public:
  virtual ~emailalertserviceIf() {}
  virtual void registerEmailAlert(EmailAlertResult& _return, const std::string& userid, const std::map<std::string, std::string> & parameters) = 0;
  virtual void notifyNewAnnounces(EmailAlertResult& _return, const std::string& city) = 0;
  virtual void my_realestate_search(std::vector<std::map<std::string, std::string> > & _return, const std::string& userid) = 0;
  virtual void changeAlertStatus(EmailAlertResult& _return, const std::string& alert_id, const std::string& alert_status) = 0;
};

class emailalertserviceIfFactory {
 public:
  typedef emailalertserviceIf Handler;

  virtual ~emailalertserviceIfFactory() {}

  virtual emailalertserviceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(emailalertserviceIf* /* handler */) = 0;
};

class emailalertserviceIfSingletonFactory : virtual public emailalertserviceIfFactory {
 public:
  emailalertserviceIfSingletonFactory(const boost::shared_ptr<emailalertserviceIf>& iface) : iface_(iface) {}
  virtual ~emailalertserviceIfSingletonFactory() {}

  virtual emailalertserviceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(emailalertserviceIf* /* handler */) {}

 protected:
  boost::shared_ptr<emailalertserviceIf> iface_;
};

class emailalertserviceNull : virtual public emailalertserviceIf {
 public:
  virtual ~emailalertserviceNull() {}
  void registerEmailAlert(EmailAlertResult& /* _return */, const std::string& /* userid */, const std::map<std::string, std::string> & /* parameters */) {
    return;
  }
  void notifyNewAnnounces(EmailAlertResult& /* _return */, const std::string& /* city */) {
    return;
  }
  void my_realestate_search(std::vector<std::map<std::string, std::string> > & /* _return */, const std::string& /* userid */) {
    return;
  }
  void changeAlertStatus(EmailAlertResult& /* _return */, const std::string& /* alert_id */, const std::string& /* alert_status */) {
    return;
  }
};

typedef struct _emailalertservice_registerEmailAlert_args__isset {
  _emailalertservice_registerEmailAlert_args__isset() : userid(false), parameters(false) {}
  bool userid :1;
  bool parameters :1;
} _emailalertservice_registerEmailAlert_args__isset;

class emailalertservice_registerEmailAlert_args {
 public:

  emailalertservice_registerEmailAlert_args(const emailalertservice_registerEmailAlert_args&);
  emailalertservice_registerEmailAlert_args& operator=(const emailalertservice_registerEmailAlert_args&);
  emailalertservice_registerEmailAlert_args() : userid() {
  }

  virtual ~emailalertservice_registerEmailAlert_args() throw();
  std::string userid;
  std::map<std::string, std::string>  parameters;

  _emailalertservice_registerEmailAlert_args__isset __isset;

  void __set_userid(const std::string& val);

  void __set_parameters(const std::map<std::string, std::string> & val);

  bool operator == (const emailalertservice_registerEmailAlert_args & rhs) const
  {
    if (!(userid == rhs.userid))
      return false;
    if (!(parameters == rhs.parameters))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_registerEmailAlert_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_registerEmailAlert_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class emailalertservice_registerEmailAlert_pargs {
 public:


  virtual ~emailalertservice_registerEmailAlert_pargs() throw();
  const std::string* userid;
  const std::map<std::string, std::string> * parameters;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_registerEmailAlert_result__isset {
  _emailalertservice_registerEmailAlert_result__isset() : success(false) {}
  bool success :1;
} _emailalertservice_registerEmailAlert_result__isset;

class emailalertservice_registerEmailAlert_result {
 public:

  emailalertservice_registerEmailAlert_result(const emailalertservice_registerEmailAlert_result&);
  emailalertservice_registerEmailAlert_result& operator=(const emailalertservice_registerEmailAlert_result&);
  emailalertservice_registerEmailAlert_result() {
  }

  virtual ~emailalertservice_registerEmailAlert_result() throw();
  EmailAlertResult success;

  _emailalertservice_registerEmailAlert_result__isset __isset;

  void __set_success(const EmailAlertResult& val);

  bool operator == (const emailalertservice_registerEmailAlert_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_registerEmailAlert_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_registerEmailAlert_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_registerEmailAlert_presult__isset {
  _emailalertservice_registerEmailAlert_presult__isset() : success(false) {}
  bool success :1;
} _emailalertservice_registerEmailAlert_presult__isset;

class emailalertservice_registerEmailAlert_presult {
 public:


  virtual ~emailalertservice_registerEmailAlert_presult() throw();
  EmailAlertResult* success;

  _emailalertservice_registerEmailAlert_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _emailalertservice_notifyNewAnnounces_args__isset {
  _emailalertservice_notifyNewAnnounces_args__isset() : city(false) {}
  bool city :1;
} _emailalertservice_notifyNewAnnounces_args__isset;

class emailalertservice_notifyNewAnnounces_args {
 public:

  emailalertservice_notifyNewAnnounces_args(const emailalertservice_notifyNewAnnounces_args&);
  emailalertservice_notifyNewAnnounces_args& operator=(const emailalertservice_notifyNewAnnounces_args&);
  emailalertservice_notifyNewAnnounces_args() : city() {
  }

  virtual ~emailalertservice_notifyNewAnnounces_args() throw();
  std::string city;

  _emailalertservice_notifyNewAnnounces_args__isset __isset;

  void __set_city(const std::string& val);

  bool operator == (const emailalertservice_notifyNewAnnounces_args & rhs) const
  {
    if (!(city == rhs.city))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_notifyNewAnnounces_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_notifyNewAnnounces_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class emailalertservice_notifyNewAnnounces_pargs {
 public:


  virtual ~emailalertservice_notifyNewAnnounces_pargs() throw();
  const std::string* city;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_notifyNewAnnounces_result__isset {
  _emailalertservice_notifyNewAnnounces_result__isset() : success(false) {}
  bool success :1;
} _emailalertservice_notifyNewAnnounces_result__isset;

class emailalertservice_notifyNewAnnounces_result {
 public:

  emailalertservice_notifyNewAnnounces_result(const emailalertservice_notifyNewAnnounces_result&);
  emailalertservice_notifyNewAnnounces_result& operator=(const emailalertservice_notifyNewAnnounces_result&);
  emailalertservice_notifyNewAnnounces_result() {
  }

  virtual ~emailalertservice_notifyNewAnnounces_result() throw();
  EmailAlertResult success;

  _emailalertservice_notifyNewAnnounces_result__isset __isset;

  void __set_success(const EmailAlertResult& val);

  bool operator == (const emailalertservice_notifyNewAnnounces_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_notifyNewAnnounces_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_notifyNewAnnounces_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_notifyNewAnnounces_presult__isset {
  _emailalertservice_notifyNewAnnounces_presult__isset() : success(false) {}
  bool success :1;
} _emailalertservice_notifyNewAnnounces_presult__isset;

class emailalertservice_notifyNewAnnounces_presult {
 public:


  virtual ~emailalertservice_notifyNewAnnounces_presult() throw();
  EmailAlertResult* success;

  _emailalertservice_notifyNewAnnounces_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _emailalertservice_my_realestate_search_args__isset {
  _emailalertservice_my_realestate_search_args__isset() : userid(false) {}
  bool userid :1;
} _emailalertservice_my_realestate_search_args__isset;

class emailalertservice_my_realestate_search_args {
 public:

  emailalertservice_my_realestate_search_args(const emailalertservice_my_realestate_search_args&);
  emailalertservice_my_realestate_search_args& operator=(const emailalertservice_my_realestate_search_args&);
  emailalertservice_my_realestate_search_args() : userid() {
  }

  virtual ~emailalertservice_my_realestate_search_args() throw();
  std::string userid;

  _emailalertservice_my_realestate_search_args__isset __isset;

  void __set_userid(const std::string& val);

  bool operator == (const emailalertservice_my_realestate_search_args & rhs) const
  {
    if (!(userid == rhs.userid))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_my_realestate_search_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_my_realestate_search_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class emailalertservice_my_realestate_search_pargs {
 public:


  virtual ~emailalertservice_my_realestate_search_pargs() throw();
  const std::string* userid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_my_realestate_search_result__isset {
  _emailalertservice_my_realestate_search_result__isset() : success(false) {}
  bool success :1;
} _emailalertservice_my_realestate_search_result__isset;

class emailalertservice_my_realestate_search_result {
 public:

  emailalertservice_my_realestate_search_result(const emailalertservice_my_realestate_search_result&);
  emailalertservice_my_realestate_search_result& operator=(const emailalertservice_my_realestate_search_result&);
  emailalertservice_my_realestate_search_result() {
  }

  virtual ~emailalertservice_my_realestate_search_result() throw();
  std::vector<std::map<std::string, std::string> >  success;

  _emailalertservice_my_realestate_search_result__isset __isset;

  void __set_success(const std::vector<std::map<std::string, std::string> > & val);

  bool operator == (const emailalertservice_my_realestate_search_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_my_realestate_search_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_my_realestate_search_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_my_realestate_search_presult__isset {
  _emailalertservice_my_realestate_search_presult__isset() : success(false) {}
  bool success :1;
} _emailalertservice_my_realestate_search_presult__isset;

class emailalertservice_my_realestate_search_presult {
 public:


  virtual ~emailalertservice_my_realestate_search_presult() throw();
  std::vector<std::map<std::string, std::string> > * success;

  _emailalertservice_my_realestate_search_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _emailalertservice_changeAlertStatus_args__isset {
  _emailalertservice_changeAlertStatus_args__isset() : alert_id(false), alert_status(false) {}
  bool alert_id :1;
  bool alert_status :1;
} _emailalertservice_changeAlertStatus_args__isset;

class emailalertservice_changeAlertStatus_args {
 public:

  emailalertservice_changeAlertStatus_args(const emailalertservice_changeAlertStatus_args&);
  emailalertservice_changeAlertStatus_args& operator=(const emailalertservice_changeAlertStatus_args&);
  emailalertservice_changeAlertStatus_args() : alert_id(), alert_status() {
  }

  virtual ~emailalertservice_changeAlertStatus_args() throw();
  std::string alert_id;
  std::string alert_status;

  _emailalertservice_changeAlertStatus_args__isset __isset;

  void __set_alert_id(const std::string& val);

  void __set_alert_status(const std::string& val);

  bool operator == (const emailalertservice_changeAlertStatus_args & rhs) const
  {
    if (!(alert_id == rhs.alert_id))
      return false;
    if (!(alert_status == rhs.alert_status))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_changeAlertStatus_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_changeAlertStatus_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class emailalertservice_changeAlertStatus_pargs {
 public:


  virtual ~emailalertservice_changeAlertStatus_pargs() throw();
  const std::string* alert_id;
  const std::string* alert_status;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_changeAlertStatus_result__isset {
  _emailalertservice_changeAlertStatus_result__isset() : success(false) {}
  bool success :1;
} _emailalertservice_changeAlertStatus_result__isset;

class emailalertservice_changeAlertStatus_result {
 public:

  emailalertservice_changeAlertStatus_result(const emailalertservice_changeAlertStatus_result&);
  emailalertservice_changeAlertStatus_result& operator=(const emailalertservice_changeAlertStatus_result&);
  emailalertservice_changeAlertStatus_result() {
  }

  virtual ~emailalertservice_changeAlertStatus_result() throw();
  EmailAlertResult success;

  _emailalertservice_changeAlertStatus_result__isset __isset;

  void __set_success(const EmailAlertResult& val);

  bool operator == (const emailalertservice_changeAlertStatus_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const emailalertservice_changeAlertStatus_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const emailalertservice_changeAlertStatus_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _emailalertservice_changeAlertStatus_presult__isset {
  _emailalertservice_changeAlertStatus_presult__isset() : success(false) {}
  bool success :1;
} _emailalertservice_changeAlertStatus_presult__isset;

class emailalertservice_changeAlertStatus_presult {
 public:


  virtual ~emailalertservice_changeAlertStatus_presult() throw();
  EmailAlertResult* success;

  _emailalertservice_changeAlertStatus_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class emailalertserviceClient : virtual public emailalertserviceIf {
 public:
  emailalertserviceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  emailalertserviceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void registerEmailAlert(EmailAlertResult& _return, const std::string& userid, const std::map<std::string, std::string> & parameters);
  void send_registerEmailAlert(const std::string& userid, const std::map<std::string, std::string> & parameters);
  void recv_registerEmailAlert(EmailAlertResult& _return);
  void notifyNewAnnounces(EmailAlertResult& _return, const std::string& city);
  void send_notifyNewAnnounces(const std::string& city);
  void recv_notifyNewAnnounces(EmailAlertResult& _return);
  void my_realestate_search(std::vector<std::map<std::string, std::string> > & _return, const std::string& userid);
  void send_my_realestate_search(const std::string& userid);
  void recv_my_realestate_search(std::vector<std::map<std::string, std::string> > & _return);
  void changeAlertStatus(EmailAlertResult& _return, const std::string& alert_id, const std::string& alert_status);
  void send_changeAlertStatus(const std::string& alert_id, const std::string& alert_status);
  void recv_changeAlertStatus(EmailAlertResult& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class emailalertserviceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<emailalertserviceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (emailalertserviceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_registerEmailAlert(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_notifyNewAnnounces(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_my_realestate_search(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_changeAlertStatus(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  emailalertserviceProcessor(boost::shared_ptr<emailalertserviceIf> iface) :
    iface_(iface) {
    processMap_["registerEmailAlert"] = &emailalertserviceProcessor::process_registerEmailAlert;
    processMap_["notifyNewAnnounces"] = &emailalertserviceProcessor::process_notifyNewAnnounces;
    processMap_["my_realestate_search"] = &emailalertserviceProcessor::process_my_realestate_search;
    processMap_["changeAlertStatus"] = &emailalertserviceProcessor::process_changeAlertStatus;
  }

  virtual ~emailalertserviceProcessor() {}
};

class emailalertserviceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  emailalertserviceProcessorFactory(const ::boost::shared_ptr< emailalertserviceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< emailalertserviceIfFactory > handlerFactory_;
};

class emailalertserviceMultiface : virtual public emailalertserviceIf {
 public:
  emailalertserviceMultiface(std::vector<boost::shared_ptr<emailalertserviceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~emailalertserviceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<emailalertserviceIf> > ifaces_;
  emailalertserviceMultiface() {}
  void add(boost::shared_ptr<emailalertserviceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void registerEmailAlert(EmailAlertResult& _return, const std::string& userid, const std::map<std::string, std::string> & parameters) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->registerEmailAlert(_return, userid, parameters);
    }
    ifaces_[i]->registerEmailAlert(_return, userid, parameters);
    return;
  }

  void notifyNewAnnounces(EmailAlertResult& _return, const std::string& city) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->notifyNewAnnounces(_return, city);
    }
    ifaces_[i]->notifyNewAnnounces(_return, city);
    return;
  }

  void my_realestate_search(std::vector<std::map<std::string, std::string> > & _return, const std::string& userid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->my_realestate_search(_return, userid);
    }
    ifaces_[i]->my_realestate_search(_return, userid);
    return;
  }

  void changeAlertStatus(EmailAlertResult& _return, const std::string& alert_id, const std::string& alert_status) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->changeAlertStatus(_return, alert_id, alert_status);
    }
    ifaces_[i]->changeAlertStatus(_return, alert_id, alert_status);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class emailalertserviceConcurrentClient : virtual public emailalertserviceIf {
 public:
  emailalertserviceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  emailalertserviceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void registerEmailAlert(EmailAlertResult& _return, const std::string& userid, const std::map<std::string, std::string> & parameters);
  int32_t send_registerEmailAlert(const std::string& userid, const std::map<std::string, std::string> & parameters);
  void recv_registerEmailAlert(EmailAlertResult& _return, const int32_t seqid);
  void notifyNewAnnounces(EmailAlertResult& _return, const std::string& city);
  int32_t send_notifyNewAnnounces(const std::string& city);
  void recv_notifyNewAnnounces(EmailAlertResult& _return, const int32_t seqid);
  void my_realestate_search(std::vector<std::map<std::string, std::string> > & _return, const std::string& userid);
  int32_t send_my_realestate_search(const std::string& userid);
  void recv_my_realestate_search(std::vector<std::map<std::string, std::string> > & _return, const int32_t seqid);
  void changeAlertStatus(EmailAlertResult& _return, const std::string& alert_id, const std::string& alert_status);
  int32_t send_changeAlertStatus(const std::string& alert_id, const std::string& alert_status);
  void recv_changeAlertStatus(EmailAlertResult& _return, const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif



#endif
