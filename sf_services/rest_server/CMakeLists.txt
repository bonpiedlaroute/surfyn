cmake_minimum_required (VERSION 3.8.2)

project(rest_server)

set(CMAKE_CXX_STANDARD 17)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2")


include_directories(../..)
include_directories(inc)

set( CMAKE_PREFIX_PATH "${SF_UTILS_BUILD_DIR}")
find_library(SF_UTILS_LIB sf_utils)


add_executable(rest_server
  src/main.cpp
  src/HttpRequestHandler.cpp
  src/DBaccess.cpp
  src/EstimatorAccess.cpp
  src/SendEmailAccess.cpp
  src/EmailAlertAccess.cpp
  ../../sf_services/dynamodb_access/thrift_generated/dynamodb_access_constants.cpp
  ../../sf_services/dynamodb_access/thrift_generated/dynamodb_access_types.cpp
  ../../sf_services/dynamodb_access/thrift_generated/dynamodb_access.cpp
  ../../sklearn/thrift_generated/house_prediction_constants.cpp
  ../../sklearn/thrift_generated/house_prediction.cpp
  ../../sklearn/thrift_generated/house_prediction_types.cpp
  ../../sf_services/mail/thrift_generated/sendemailservice.cpp
  ../../sf_services/mail/thrift_generated/sendmail_constants.cpp
  ../../sf_services/mail/thrift_generated/sendmail_types.cpp
  ../../sf_services/emailalertservice/thrift_generated/emailalertservice.cpp
  ../../sf_services/emailalertservice/thrift_generated/emailalertservice_constants.cpp
  ../../sf_services/emailalertservice/thrift_generated/emailalertservice_types.cpp
  )

target_link_libraries(rest_server boost_system crypto ssl cpprest ${SF_UTILS_LIB} thrift)







