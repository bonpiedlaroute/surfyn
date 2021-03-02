/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "emailalertservice_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>




EmailAlertResult::~EmailAlertResult() throw() {
}


void EmailAlertResult::__set_success(const bool val) {
  this->success = val;
}

void EmailAlertResult::__set_error(const std::string& val) {
  this->error = val;
}

uint32_t EmailAlertResult::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->success);
          this->__isset.success = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->error);
          this->__isset.error = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t EmailAlertResult::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("EmailAlertResult");

  xfer += oprot->writeFieldBegin("success", ::apache::thrift::protocol::T_BOOL, 1);
  xfer += oprot->writeBool(this->success);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("error", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->error);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(EmailAlertResult &a, EmailAlertResult &b) {
  using ::std::swap;
  swap(a.success, b.success);
  swap(a.error, b.error);
  swap(a.__isset, b.__isset);
}

EmailAlertResult::EmailAlertResult(const EmailAlertResult& other0) {
  success = other0.success;
  error = other0.error;
  __isset = other0.__isset;
}
EmailAlertResult& EmailAlertResult::operator=(const EmailAlertResult& other1) {
  success = other1.success;
  error = other1.error;
  __isset = other1.__isset;
  return *this;
}
void EmailAlertResult::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "EmailAlertResult(";
  out << "success=" << to_string(success);
  out << ", " << "error=" << to_string(error);
  out << ")";
}

