#include "UserService.h"
#include "dto/StatusDto.hpp"
#include "dto/UserDto.hpp"
#include <oatpp/web/protocol/http/Http.hpp>
#include "../Utils.hpp"

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

    auto dbResult = m_database->getAllUsers(countToFetch, offset);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserModel>>>();

    oatpp::Vector<oatpp::Object<UserDto>> users({});
    for(auto& item : * items) 
    {
        // convert dbModel to DTO
        auto user = UserDto::createShared();
        user->id = item->id;
        user->userName = item->userName;
        user->pswhash = item->pswhash;
        user->email = item->email;

        users->push_back(user);
    }


    auto userList = UserPageDto::createShared();
    userList->limit = countToFetch;
    userList->offset = offset;
    userList->count = users->size();
    userList->items = users;

    return userList;
}

oatpp::Object<UserDto> UserService::getUserById(const oatpp::String& id)
{
    auto dbResult = m_database->getUserById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User story not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserModel>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");


    auto user = UserDto::createShared();
    user->id = result[0]->id;
    user->userName = result[0]->userName;
    user->pswhash = result[0]->pswhash;
    user->email = result[0]->email;

    return user;
}

oatpp::Object<StatusDto> UserService::createUser(const oatpp::Object<SignUpDto>& dto) 
{
    auto user = UserModel::createShared();
    user->id = XUtils::generate_uuid();
    user->userName = dto->userName;
    user->email = dto->email;
    user->pswhash = XUtils::hash_string(dto->pswhash);

    auto dbResult = m_database->createUser(user);

    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "User was successfully deleted";


    if(!dbResult->isSuccess()) 
    {
        status->status = "ERR";
        status->code = 500;
        status->message = dbResult->getErrorMessage();

        OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
    }

    
    return status;
}

oatpp::Object<StatusDto> UserService::updateUserInfo(const oatpp::String& id, const oatpp::Object<UserDto>& dto)
{
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "User was successfully deleted";

    auto user = UserModel::createShared();
    user->id = id;
    user->userName = dto->userName;
    user->email = dto->email;
    user->pswhash = XUtils::hash_string(dto->pswhash);

    auto dbResult = m_database->updateUser(user);
    if(!dbResult->isSuccess()) 
    {
        status->status = "ERR";
        status->code = 500;
        status->message = dbResult->getErrorMessage();

        OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
    }
    return status;
}