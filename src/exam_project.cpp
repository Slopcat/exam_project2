// exam_project.cpp: определяет точку входа для приложения.
//
#include <iostream>
#include "converter_js.h"
#include "invert_in.h"
#include "search_serve.h"

void writeAnswers(const std::vector<std::vector<RelativeIndex>>& allRequestsResults)
{
    if (allRequestsResults.empty())
    {
        std::cout << "no matches are found.\n";
        return;
    }
    std::vector<std::vector<std::pair<int, float>>> allRequestsResultsReadyForJSON;
    for (auto& requestResult : allRequestsResults)
    {
        std::vector<std::pair<int, float>> requestResultReadyForJSON;
        for (auto& pageRelevance : requestResult)
        {
            std::pair<int, float> relevancePair;
            relevancePair.first = (int)pageRelevance.doc_id;
            relevancePair.second = pageRelevance.rank;
            requestResultReadyForJSON.push_back(relevancePair);
        }
        allRequestsResultsReadyForJSON.push_back(requestResultReadyForJSON);
    }
    ConverterJSON::getInstance()->putAnswers(allRequestsResultsReadyForJSON);
}

int main()
{
    
    ConverterJSON::getInstance()->readConfigFile();
    ConverterJSON::getInstance()->readRequestFile();
    std::vector<std::string> documents = ConverterJSON::getInstance()->getTextDocuments();
    auto* invertedIndex = new InvertedIndex();
    invertedIndex->updateDocumentBase(documents);

    
    std::cout << "searching\n";
    SearchServer searchServer(*invertedIndex);
    searchServer.setMaxResponses(ConverterJSON::getInstance()->getMaxResponses());
    auto allRequestsResults = searchServer.search(ConverterJSON::getInstance()->getRequests());
    writeAnswers(allRequestsResults);
    std::cout << "end of search.\n";
    ConverterJSON::getInstance()->deletInstance();
    std::cin.get();
    return 0;
}
