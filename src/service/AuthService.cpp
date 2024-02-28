
#include "AuthService.hpp"
#include "../Utils.hpp"

oatpp::Object<AuthDto> AuthService::signUp(const oatpp::Object<SignUpDto>& dto) 
{
  auto user = UserModel::createShared();
  user->id = XUtils::generate_uuid();
  user->userName = dto->userName;
  user->email = dto->email;
  user->pswhash = XUtils::hash_string(dto->pswhash);

  auto dbResult = m_database->createUser(user);
  if(!dbResult->isSuccess()) 
  {
    OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
  }

  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Vector<oatpp::String>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_401, "Unauthorized")

  auto newUserId = result[0][0];

  auto payload = std::make_shared<JWT::Payload>();
  payload->userId = newUserId;

  auto auth = AuthDto::createShared();
  auth->token = m_jwt->createToken(payload);

  return auth;

}

oatpp::Object<AuthDto> AuthService::signIn(const oatpp::Object<SignInDto>& dto) 
{
  auto dbResult = m_database->authenticateUser(dto->userName, XUtils::hash_string(dto->password));
  if(!dbResult->isSuccess()) 
  {
    OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
  }
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized")

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Vector<oatpp::String>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_401, "Unauthorized")

  auto userId = result[0][0];

  auto payload = std::make_shared<JWT::Payload>();
  payload->userId = userId;

  auto auth = AuthDto::createShared();
  auth->token = m_jwt->createToken(payload);

  return auth;
}

oatpp::Object<AuthDto> AuthService::signInEmail(const oatpp::Object<SignInEmailDto>& dto) 
{
  auto dbResult = m_database->authenticateEmail(dto->email, XUtils::hash_string(dto->password));
  if(!dbResult->isSuccess()) 
  {
    OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
  }
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized")

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Vector<oatpp::String>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_401, "Unauthorized")

  auto userId = result[0][0];

  auto payload = std::make_shared<JWT::Payload>();
  payload->userId = userId;

  auto auth = AuthDto::createShared();
  auth->token = m_jwt->createToken(payload);

  return auth;
}

oatpp::Object<StatusDto> AuthService::deleteUserById(const oatpp::String& userId) 
{
  auto dbResult = m_database->deleteUserById(userId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "User was successfully deleted";
  return status;
}

oatpp::Object<UserDto> AuthService::signInInfo(const oatpp::String& id)
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