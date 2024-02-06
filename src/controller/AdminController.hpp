#ifndef USER_MANAGEMENT_ADMINCONTROLLER_HPP
#define USER_MANAGEMENT_ADMINCONTROLLER_HPP

#include "service/UserService.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include <memory>
#include <oatpp/core/macro/component.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class AdminController : public oatpp::web::server::api::ApiController 
{
public:
    AdminController(const std::shared_ptr<ObjectMapper>& objectMapper)
        : oatpp::web::server::api::ApiController(objectMapper)
    {}

private:
    UserService m_userService; // Create user service.

public:
    static std::shared_ptr<AdminController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    {
        return std::make_shared<AdminController>(objectMapper);
    }

    ENDPOINT_INFO(deleteUser) 
    {
        info->summary = "Delete User";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }

    ENDPOINT("DELETE", "admin/delete", deleteUser,
        BUNDLE(String, id))
        {
            return createDtoResponse(Status::CODE_200, this->m_userService.deleteUserById(id));
        }
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // USER_MANAGEMENT_ADMINCONTROLLER_HPP