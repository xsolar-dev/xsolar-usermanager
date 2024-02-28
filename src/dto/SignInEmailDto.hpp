#ifndef USER_MANAGEMENT_SIGNINEMAILDTO_HPP
#define USER_MANAGEMENT_SIGNINEMAILDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class SignInEmailDto : public oatpp::DTO {

  DTO_INIT(SignInEmailDto, DTO)

  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, password, "password");

};

#include OATPP_CODEGEN_END(DTO)

#endif