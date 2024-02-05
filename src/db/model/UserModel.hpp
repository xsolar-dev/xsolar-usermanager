#ifndef USER_MANAGEMENT_DB_MODEL_USERMODEL_HPP
#define USER_MANAGEMENT_DB_MODEL_USERMODEL_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class UserModel : public oatpp::DTO {

  DTO_INIT(UserModel, DTO)

  DTO_FIELD(String, id);
  DTO_FIELD(String, userName, "username");
  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, password, "password");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* USER_MANAGEMENT_DB_MODEL_USERMODEL_HPP */
