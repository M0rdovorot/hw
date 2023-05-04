#pragma once

#include <memory>
#include <boost/beast.hpp>
#include "database_manager.hpp"

class IRequestHandler {
public:
  virtual void ReadRequest(std::string json) = 0;
private:
  virtual void JsonParser(std::string json) = 0;
  virtual void CalculateRecommendations(Profile& profile, std::vector<Profile>& recommended_profiles) = 0;
};

class RequestHandler : public IRequestHandler {
public:
  RequestHandler(std::shared_ptr<IDatabaseManager> database_manager, std::shared_ptr<IRecommendation> recommendation) {}
  virtual void ReadRequest(std::string json) override {}
private:
  virtual void JsonParser(std::string json) override {}
  virtual void CalculateRecommendations(Profile& profile, std::vector<Profile>& recommended_profiles) override {}
  /*Request Parametres*/
};
