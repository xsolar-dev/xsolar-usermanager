
#ifndef USER_MANAGEMENT_USERDB_HPP
#define USER_MANAGEMENT_USERDB_HPP

#include "model/UserModel.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class UserDb : public oatpp::orm::DbClient 
{
public:

      UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
      : oatpp::orm::DbClient(executor)
      {

            oatpp::orm::SchemaMigration migration(executor, "auth_service");
            migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/AuthService/001_init.sql");
            // TODO - Add more migrations here.
            migration.migrate(); // <-- run migrations. This guy will throw on error.

            OATPP_LOGD("UserDb", "Migration - OK");
      }

      QUERY(createUser,
            "INSERT INTO users "
            "(id, username, email, pswhash) VALUES "
            "(:user.id, :user.username, :user.email, :user.pswhash) "
            "RETURNING id;",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::Object<UserModel>, user))

      QUERY(changeUserPassword,
            "UPDATE users "
            "SET "
            " pswhash=:newPassword "
            "WHERE "
            " id=:id AND pswhash=:oldPassword",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, userId, "id"),
            PARAM(oatpp::String, oldPassword),
            PARAM(oatpp::String, newPassword))

      QUERY(forceChangeUserPassword,
            "UPDATE users "
            "SET "
            " pswhash=:newPassword "
            "WHERE "
            " id=:id;",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, userId, "id"),
            PARAM(oatpp::String, oldPassword))

      QUERY(authenticateUser,
            "SELECT id FROM users WHERE username=:username AND pswhash=:password",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, username),
            PARAM(oatpp::String, password))

      QUERY(authenticateEmail,
            "SELECT id FROM users WHERE email=:email AND pswhash=:password",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, email),
            PARAM(oatpp::String, password))

      QUERY(userInfo,
            "SELECT id, email, username FROM users WHERE id=:id",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, id))           

      QUERY(deleteUserById,
            "DELETE FROM users WHERE id=:id;",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, id))

      QUERY(deleteUserByName,
            "DELETE from users WHERE username=:username",
            PREPARE(true),
            PARAM(oatpp::String, username))

      QUERY(getAllUsers,
            "SELECT * FROM users LIMIT :limit OFFSET :offset",
            PREPARE(true), // prepared statement!            
            PARAM(oatpp::UInt32, limit),
            PARAM(oatpp::UInt32, offset))

      QUERY(getUserById,
            "SELECT * FROM users WHERE id=:id",
            PREPARE(true),
            PARAM(oatpp::String, id))

      QUERY(updateUser,
            "UPDATE users SET "
            "username = :user.username, email = :user.email, pswhash = :user.pswhash "            
            "WHERE id = :user.id",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::Object<UserModel>, user))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //USER_MANAGEMENT_USERDB_HPP
