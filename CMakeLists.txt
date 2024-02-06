cmake_minimum_required(VERSION 3.1)
project(xsolar-usermanager)

set(CMAKE_CXX_STANDARD 11)

add_library(xsolar-usermanager-lib
        src/auth/AuthHandler.cpp
        src/auth/AuthHandler.hpp
        src/auth/JWT.cpp
        src/auth/JWT.hpp
        src/controller/StaticController.hpp
        src/controller/AuthController.hpp
        src/controller/AdminController.hpp
        src/db/model/UserModel.hpp
        src/db/UserDb.hpp
        src/dto/AuthDto.hpp
        src/dto/PageDto.hpp
        src/dto/SignInDto.hpp
        src/dto/SignUpDto.hpp
        src/dto/StatusDto.hpp
        src/interceptor/AuthInterceptor.cpp
        src/interceptor/AuthInterceptor.hpp
        src/service/AuthService.cpp
        src/service/AuthService.hpp
        src/service/UserService.cpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp
)

## include directories

target_include_directories(xsolar-usermanager-lib PUBLIC src)

find_package(OpenSSL)

## link libs

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-swagger      1.3.0 REQUIRED)
find_package(oatpp-postgresql   1.3.0 REQUIRED)
find_package(oatpp-openssl      1.3.0 REQUIRED)

find_package(jwt-cpp REQUIRED PATHS /usr/local/cmake)

target_link_libraries(xsolar-usermanager-lib
        # oatpp
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
        PUBLIC oatpp::oatpp-openssl

        # third-party
        PUBLIC jwt-cpp::jwt-cpp
        PUBLIC OpenSSL::SSL
        PUBLIC OpenSSL::Crypto

)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(xsolar-usermanager-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(xsolar-usermanager-exe src/App.cpp)
target_link_libraries(xsolar-usermanager-exe xsolar-usermanager-lib)

add_executable(xsolar-usermanager-test
        test/FullTest.cpp
        test/FullTest.hpp
        test/tests.cpp
)
target_link_libraries(xsolar-usermanager-test xsolar-usermanager-lib)

enable_testing()
add_test(project-tests xsolar-usermanager-test)
