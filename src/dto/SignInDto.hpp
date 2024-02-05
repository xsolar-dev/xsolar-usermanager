#ifndef USER_MANAGEMENT_SIGNINDTO_HPP
#define USER_MANAGEMENT_SIGNINDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class SignInDto : public oatpp::DTO {

  DTO_INIT(SignInDto, DTO)

  DTO_FIELD(String, userName, "username");
  DTO_FIELD(String, password, "password");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* USER_MANAGEMENT_SIGNINDTO_HPP */
