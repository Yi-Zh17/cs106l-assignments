/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Yi Zhang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename)
{
	std::set<std::string> applicants;
	std::ifstream ifs(filename);
	if (ifs.is_open())
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			applicants.insert(line);
		}
	}
	ifs.close();
	return applicants;
}

// Helper function to get initials
std::vector<char> get_initials(std::string name) {
	std::vector<char> ini;
	ini.push_back(name[0]);
	auto it = ini.cbegin();
	while(*it != ' ' && it != ini.cend()) {
		++it;
	}
	++it;
	ini.push_back(*it);
	return ini;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string *> find_matches(std::string name, std::set<std::string> &students)
{
	// Declare a queue
	std::queue<const std::string *> matches;
	// Store initials of the name
	std::vector<char> name_init = get_initials(name);
	// Use iterator
	auto it = students.cbegin();
	// Iteration
	while(it != students.cend()) {
		std::string cur_name = *it;
		std::vector<char> cur_init = get_initials(cur_name);
		// Push to queue if initials match
		if (cur_init == name_init) {
			std::string* ptr = &cur_name;
			matches.push(ptr);
		}
		++it;
	}
	return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string *> &matches)
{
	if(matches.empty()) {
		return "NO MATCHES FOUND.";
	}
	size_t size = matches.size();
	int index = int(size / 2);
	while(index > 0) {
		matches.pop();
	}
	auto ptr = matches.front();
	return *ptr;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
