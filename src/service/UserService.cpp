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
    oatpp::UInt32 countToFetch = limit;

    if (countToFetch > 10)
        countToFetch = 10;

    auto dbResult = m_database->getAllUsers(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

    oatpp::Vector<oatpp::Object<UserDto>> users({});
    for(auto& item : * items) 
    {
        // convert dbModel to DTO
        auto user = UserDto::createShared();
        user->id = item->id;
        user->userName = item->userName;
        user->password = item->password;
        user->email = item->email;

        users->push_back(user);
    }


    auto userList = UserPageDto::createShared();
    userList->limit = countToFetch;
    userList->offset = offset;
    userList->items = users;

    return userList;
}

oatpp::Object<UserDto> UserService::getUserById(const oatpp::String& id)
{
    auto user = UserDto::createShared();

    return user;
}