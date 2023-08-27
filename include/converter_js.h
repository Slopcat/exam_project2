#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

class ConverterJSON
{
public:

 /*
* get the address of a static object Converter JSON
*  @return instance of the singleton
*/
    static ConverterJSON* getInstance();  
 /*
 * get a vector of words
 * @return content of files listed in config.json
 */
    std::vector<std::string> getTextDocuments();
/*
 * get the max responses per request
 * @return max responses count
 */
    int getResponsesLimit() const;    
/*
* get the requests from requests.json
* @param[in] answers - vector of answers to be placed into answers.json file
 */
    std::vector<std::string> getRequests(); 
 /*
 * put requests results into "answers" file
 * @param[in] answers - vector of answers to be placed into answers.json file
 */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);    
 /*
 * read config file specified in CONFIG_FILE_PATH
 */
    void readConfigFile(std::string path = "config.json");
 /*
 * read request file specified in REQUEST_FILE_PATH
 */
    void readRequestFile(const std::string & = "requests.json");
 /*
 * get maximal responses quantity, which can be returned be Search Server
 * @return maximal responses quantity
 */
    int getMaxResponses() const;
 /*
 * deletes the created class
 */
    void deletInstance();

private:
    ConverterJSON() = default; 
    static ConverterJSON* instance;
    const std::string ANSWERS_FILE_PATH = "answers.json";
    std::string applicationName;
    std::string applicationVersion;
    int maxResponses{ 5 };
    std::vector<std::string> resourcesPaths;
    std::vector<std::string> textDocuments;
    std::vector<std::string> requests;
};