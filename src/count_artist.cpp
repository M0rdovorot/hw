#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "count_artist.hpp"

int CountColumns(std::string& str){
  int counter = 0;
  for (size_t i = 0; i < str.size(); ++i){
    if (str[i] == '\t'){
      counter++;
    }
  }
  return counter + 1;
}

void FindMaleAndFemaleId(std::string& id_male, std::string& id_female, std::istream& file_gender){
  std::string tmp;
  bool male_find_flag = false;
  bool female_find_flag = false;

  while(getline(file_gender, tmp)){
    if (male_find_flag && female_find_flag)
      break;

    if(CountColumns(tmp) != 6){
      throw "Wrong gender format file.";
    }

    if (tmp.find("Male") != -1){
      male_find_flag = true;
      id_male = tmp.substr(0, tmp.find('\t'));
    }

    if (tmp.find("Female") != -1){
      female_find_flag = true;
      id_female = tmp.substr(0, tmp.find('\t'));
    }
  }

  if (!male_find_flag && !female_find_flag)
    throw "Wrong gender format file.";
}

void FindArtistID(std::string& id_artist, std::istream& file_artist_type){
  std::string tmp;
  bool artist_type_find_flag = false;

  while(getline(file_artist_type, tmp)){
    if (CountColumns(tmp) != 6){
      throw "Wrong artist type format file.";
    }

    if (tmp.find("Person") != -1){
      id_artist = tmp.substr(0, tmp.find('\t'));
      return;
    }
  }

  throw "Wrong artist type format file.";
}

std::string CheckArtist(std::string& id_male, std::string& id_female, std::string& id_artist, std::string& year, std::istream& str){
  int tab_counter = 0;
  artist tmp_artist = {"", "", "", ""};
  std::string tmp = "";

  while (getline(str, tmp, '\t'))
  {
    tab_counter++;
    switch (tab_counter){
      case 5:
        tmp_artist.begin_year = tmp;
        break;
      case 8:
        tmp_artist.end_year = tmp;
        break;
      case 11:
        tmp_artist.id_artist = tmp;
        break;
      case 13:
        tmp_artist.id_gender = tmp;
        break;
    }
    if (tab_counter > 13)
      break;
  }

  if (tmp_artist.id_artist != id_artist){
    return "";
  }

  if (tmp_artist.begin_year.size() != 4){
    return "";
  }

  if (stoi(tmp_artist.begin_year) <= stoi(year) && (tmp_artist.end_year.size() != 4 || stoi(tmp_artist.end_year) >= stoi(year))){
    if (tmp_artist.id_gender == id_male){
      return "Male";
    }
    if (tmp_artist.id_gender == id_female){
      return "Female";
    }
    return "";
  }
  return "";
}

сounted_аrtists_t CountMalesOrFemalesByYear(std::istream& file_artist, std::istream& file_artist_type, std::istream& file_gender, std::string& year){
  std::string id_male = "";
  std::string id_female = "";
  std::string id_artist = "";

  FindMaleAndFemaleId(id_male, id_female, file_gender);
  FindArtistID(id_artist, file_artist_type);

  int male_counter = 0;
  int female_counter = 0;
  bool correct_flag = false;
  std::string tmp;

  while(getline(file_artist, tmp)){
    if (!correct_flag && CountColumns(tmp) != 19){
      throw "Wrong artist file format.";
    }
    else{
      correct_flag = true;
    }

    std::istringstream tmp_stream(tmp);
    tmp = CheckArtist(id_male, id_female, id_artist, year, tmp_stream);

    if (tmp == "Male")
      male_counter++;
    if (tmp == "Female"){
      female_counter++;
    }
  }
  return {male_counter, female_counter};
}