#pragma once

#include <iostream>
#include <fstream>
#include <string>

struct сounted_аrtists_t{
  int males;
  int females;
};

struct artist{
  std::string begin_year;
  std::string end_year;
  std::string id_gender;
  std::string id_artist;
};

int CountColumns(std::string& str);

void FindMaleAndFemaleId(std::string& id_male, std::string& id_female, std::istream& file_gender);

void FindArtistID(std::string& id_artist, std::istream& file_artist_type);

std::string CheckArtist(std::string& id_male, std::string& id_female, std::string& id_artist, std::string& year, std::istream& str);

сounted_аrtists_t CountMalesOrFemalesByYear(std::istream& file_artist, std::istream& file_artist_type,
                                              std::istream& file_gender, std::string& year);
