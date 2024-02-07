#ifndef USERSERVICE_H
#define USERSERVICE_H

#pragma once
#include "auth/JWT.hpp"

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/SignUpDto.hpp"
#include "dto/SignInDto.hpp"
#include "dto/AuthDto.hpp"
#include "dto/StatusDto.hpp"
#include "dto/UserDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UserService
{
private:
  typedef oatpp::web::protocol::http::Status Status;

private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
  OATPP_COMPONENT(std::shared_ptr<JWT>, m_jwt); // Inject JWT component

public:
    UserService();
    ~UserService();

    oatpp::Object<StatusDto> deleteUserById(const oatpp::String& id);
    oatpp::Object<StatusDto> deleteUserByName(const oatpp::String& id);
    

private:

};

#endif