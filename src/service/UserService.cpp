#include "UserService.h"
#include "dto/StatusDto.hpp"
#include "dto/UserDto.hpp"
#include <oatpp/web/protocol/http/Http.hpp>

UserService::UserService()
{

}

UserService::~UserService()
{

}

oatpp::Object<StatusDto> UserService::deleteUserById(const oatpp::String& id)
{
    auto dbResult = this->m_database->deleteUserById(id);
    
    // if error, return code to client
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    // no error!
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "User was successfully deleted";

    return status;

}

oatpp::Object<StatusDto> UserService::deleteUserByName(const oatpp::String& name)
{
    auto dbResult = m_database->deleteUserByName(name);

    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "User was successfully deleted";
    return status;
}

oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getUserList(const oatpp::UInt32& offset, const oatpp::UInt32& limit)
{
    auto userList = UserPageDto::createShared();

    userList->limit = limit;
    userList->offset = offset;

    return userList;
}

oatpp::Object<UserDto> UserService::getUserById(const oatpp::String& id)
{
    auto user = UserDto::createShared();

    return user;
}