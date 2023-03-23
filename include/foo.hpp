#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include <string>

int CountColumns(std::string& str);

void FindMaleAndFemaleId(std::string& id_male, std::string& id_female, std::ifstream& file_gender);

void FindArtistID(std::string& id_artist, std::ifstream& file_artist_type);

std::string CheckArtist(std::string& id_male, std::string& id_female, std::string& id_artist, std::string& year, std::string& str);

std::pair<int, int> CountMalesOrFemalesByYear(std::ifstream& file_artist, std::ifstream& file_artist_type,
                                              std::ifstream& file_gender, std::string& year);
