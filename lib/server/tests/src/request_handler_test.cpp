#include <gtest/gtest.h>
#include "request_handler_test.hpp"

TEST(RequestHandlerTest, LogInCase) {
  std::shared_ptr<IDatabaseManager> database_manager_ptr(new GMockDatabaseManager());
  IDatabaseManager* database_manager_row = database_manager_ptr.get();

  std::shared_ptr<IRecommendation> recommendation_ptr(new GMockRecommendation());
  IRecommendation* recommendation_row = recommendation_ptr.get();

  RequestHandler request_handler(database_manager_ptr, recommendation_ptr);

  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), authorise(User{"chel@mail.ru", "12345"}));

  request_handler.ReadRequest(R"({\t"request":"log in",\n\t"email":"chel@mail.ru",\n\t"password":"12345"\n})");
}

TEST(RequestHandlerTest, LogOutCase) {
  std::shared_ptr<IDatabaseManager> database_manager_ptr(new GMockDatabaseManager());
  IDatabaseManager* database_manager_row = database_manager_ptr.get();

  std::shared_ptr<IRecommendation> recommendation_ptr(new GMockRecommendation());
  IRecommendation* recommendation_row = recommendation_ptr.get();

  RequestHandler request_handler(database_manager_ptr, recommendation_ptr);

  //EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), ... );
  // I should check only response in this case

  request_handler.ReadRequest(R"({\t"request":"log out",\n\t"id":21415\n})");
}

TEST(RequestHandlerTest, RegistrationCase) {
  std::shared_ptr<IDatabaseManager> database_manager_ptr(new GMockDatabaseManager());
  IDatabaseManager* database_manager_row = database_manager_ptr.get();

  std::shared_ptr<IRecommendation> recommendation_ptr(new GMockRecommendation());
  IRecommendation* recommendation_row = recommendation_ptr.get();

  RequestHandler request_handler(database_manager_ptr, recommendation_ptr);

  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), addUser(User{"chel@mail.ru", "12345"}));

  request_handler.ReadRequest(R"({\t"request":"registration",\n\t"email":"chel@mail.ru",\n\t"password":"12345"\n})");
}

TEST(RequestHandlerTest, LikeCase) {
  std::shared_ptr<IDatabaseManager> database_manager_ptr(new GMockDatabaseManager());
  IDatabaseManager* database_manager_row = database_manager_ptr.get();

  std::shared_ptr<IRecommendation> recommendation_ptr(new GMockRecommendation());
  IRecommendation* recommendation_row = recommendation_ptr.get();

  RequestHandler request_handler(database_manager_ptr, recommendation_ptr);

  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), makeMatch(12345, 54321));

  request_handler.ReadRequest(R"({\t"request":"like",\n\t"author_id":54321,\n\t"target_id":12345\n})");
}

TEST(RequestHandlerTest, DislikeCase) {
  std::shared_ptr<IDatabaseManager> database_manager_ptr(new GMockDatabaseManager());
  IDatabaseManager* database_manager_row = database_manager_ptr.get();

  std::shared_ptr<IRecommendation> recommendation_ptr(new GMockRecommendation());
  IRecommendation* recommendation_row = recommendation_ptr.get();

  RequestHandler request_handler(database_manager_ptr, recommendation_ptr);

  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), breakMatch(12345, 54321));

  request_handler.ReadRequest(R"({\t"request":"dislike",\n\t"author_id":54321,\n\t"target_id":12345\n})");
}

TEST(RequestHandlerTest, GetNextProfilesCase) {
  std::shared_ptr<IDatabaseManager> database_manager_ptr(new GMockDatabaseManager());
  IDatabaseManager* database_manager_row = database_manager_ptr.get();

  std::shared_ptr<IRecommendation> recommendation_ptr(new GMockRecommendation());
  IRecommendation* recommendation_row = recommendation_ptr.get();

  RequestHandler request_handler(database_manager_ptr, recommendation_ptr);

  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), getUserForm(54321));
  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), getRecommendForms(Form{54321}));
  EXPECT_CALL(*dynamic_cast<GMockRecommendation*>(recommendation_row), recommend);
  EXPECT_CALL(*dynamic_cast<GMockDatabaseManager*>(database_manager_row), editRecommendations);
  

  request_handler.ReadRequest(R"({\t"request":"get next profiles",\n\t"author_id":54321\n})");
}