#ifndef USER_MANAGEMENT_SIGNUPDTO_HPP
#define USER_MANAGEMENT_SIGNUPDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class SignUpDto : public oatpp::DTO {

  DTO_INIT(SignUpDto, DTO)

  DTO_FIELD(String, userName, "username");
  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, pswhash, "pswhash");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* USER_MANAGEMENT_SIGNUPDTO_HPP */
