#include <iostream>
#include <fstream>
#include <utility>
#include <string>

int CountColumns(std::string& str){
  int counter = 0;
  for (size_t i = 0; i < str.size(); ++i){
    if (str[i] == '\t'){
      counter++;
    }
  }
  return counter + 1;
}

void FindMaleAndFemaleId(std::string& id_male, std::string& id_female, std::ifstream& file_gender){
  std::string tmp;
  while(getline(file_gender, tmp)){
    if (id_male != "-1" && id_female != "-1")
      break;
    if(CountColumns(tmp) != 6){
      throw "Wrong gender format file.";
    }
    if (tmp.find("Male") != std::string::npos)
      id_male = tmp.substr(0, tmp.find('\t'));
    if (tmp.find("Female") != std::string::npos)
      id_female = tmp.substr(0, tmp.find('\t'));
  }
  if (id_male == "-1" && id_female == "-1")
    throw "Wrong gender format file.";
}
void FindArtistID(std::string& id_artist, std::ifstream& file_artist_type){
  std::string tmp;
  while(getline(file_artist_type, tmp)){
    if (id_artist != "-1"){
      break;
    }
    if (CountColumns(tmp) != 6){
      throw "Wrong artist type format file.";
      return;
    }
    if (tmp.find("Person") != std::string::npos)
      id_artist = tmp.substr(0, tmp.find('\t'));
  }
  if (id_artist == "-1")
    throw "Wrong artist type format file.";
}

std::string CheckArtist(std::string& id_male, std::string& id_female, std::string& id_artist, std::string& year, std::string& str){
  int tab_counter = 0;
  std::string tmp_begin_year = "";
  std::string tmp_end_year = "";
  std::string tmp_id_gender = "";
  std::string tmp_id_artist = "";
  for (size_t i = 0; i < str.size(); ++i){
    if (str[i] != '\t' && tab_counter == 4){
      tmp_begin_year += str[i];
    }
    if (str[i] != '\t' && tab_counter == 7){
      tmp_end_year += str[i];
    }
    if (str[i] != '\t' && tab_counter == 10){
      tmp_id_artist += str[i];
    }
    if (str [i] != '\t' && tab_counter == 12){
      tmp_id_gender += str[i];
    }
    if (str[i] == '\t')
      tab_counter++;
    if (tab_counter > 12)
      break;
  }
  if (tmp_id_artist != id_artist){
    return "Not a person";
  }
  if (tmp_begin_year.size() != 4){
    return "Can't count";
  }
  if (stoi(tmp_begin_year) <= stoi(year) && (tmp_end_year.size() != 4 || stoi(tmp_end_year) >= stoi(year))){
    if (tmp_id_gender == id_male){
      return "Male";
    }
    if (tmp_id_gender == id_female){
      return "Female";
    }
    return "Neither";
  }
  return "Didn't live";
}

std::pair<int, int> CountMalesOrFemalesByYear(std::ifstream& file_artist, std::ifstream& file_artist_type, std::ifstream& file_gender, std::string& year){
  std::string tmp;
  std::string id_male = "-1";
  std::string id_female = "-1";
  std::string id_artist = "-1";
  int male_counter = 0;
  int female_counter = 0;
  bool correct_flag = false;
  FindMaleAndFemaleId(id_male, id_female, file_gender);
  FindArtistID(id_artist, file_artist_type);
  while(getline(file_artist, tmp)){
    if (!correct_flag && CountColumns(tmp) != 19){
      throw "Wrong artist file format.";
    }
    else{
      correct_flag = true;
    }
    tmp = CheckArtist(id_male, id_female, id_artist, year, tmp);
    if (tmp == "Male")
      male_counter++;
    if (tmp == "Female"){
      female_counter++;
    }
  }
  return std::make_pair(male_counter, female_counter);
}
