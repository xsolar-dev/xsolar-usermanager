
#ifndef USER_MANAGEMENT_USERDB_HPP
#define USER_MANAGEMENT_USERDB_HPP

#include "model/UserModel.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class UserDb : public oatpp::orm::DbClient {
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
            "(uuid_generate_v4(), :user.username, :user.email, crypt(:user.password, gen_salt('bf', 8))) "
            "RETURNING id;",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::Object<UserModel>, user))

      QUERY(changeUserPassword,
            "UPDATE users "
            "SET "
            " pswhash=crypt(:newPassword, gen_salt('bf', 8)) "
            "WHERE "
            " id=:id AND pswhash=crypt(:oldPassword, pswhash);",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, userId, "id"),
            PARAM(oatpp::String, oldPassword),
            PARAM(oatpp::String, newPassword))

      QUERY(authenticateUser,
            "SELECT id FROM users WHERE username=:username AND pswhash=crypt(:password, pswhash);",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, username),
            PARAM(oatpp::String, password))

      QUERY(deleteUserById,
            "DELETE FROM users WHERE id=:id;",
            PREPARE(true), // prepared statement!
            PARAM(oatpp::String, id))

      QUERY(deleteUserByName,
            "DELETE from users WHERE username=:username;",
            PREPARE(true),
            PARAM(oatpp::String, username))

      QUERY(getAllUsers,
            "SELECT * FROM users LIMIT :limit OFFSET :offset;",
            PREPARE(true), // prepared statement!            
            PARAM(oatpp::UInt32, offset),
            PARAM(oatpp::UInt32, limit))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //USER_MANAGEMENT_USERDB_HPP
