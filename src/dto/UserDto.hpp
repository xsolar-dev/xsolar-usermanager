#ifndef USER_MANAGEMENT_USERDTO_HPP
#define USER_MANAGEMENT_USERDTO_HPP

#include "dto/PageDto.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(String, id);
  DTO_FIELD(String, userName);
  DTO_FIELD(String, email);
  DTO_FIELD(String, password);
  
};

class UserPageDto : public PageDto<oatpp::Object<UserDto>>
{
  DTO_INIT(UserPageDto, PageDto<oatpp::Object<UserDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif /* USER_MANAGEMENT_AUTHDTO_HPP */