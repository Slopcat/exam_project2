#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct Entry
{
    size_t doc_id, count;

    bool operator ==(const Entry& other) const
    {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex
{
public:
    InvertedIndex() = default;
    void updateDocumentBase(const std::vector<std::string>& input_docs);    
    std::vector<Entry> getWordCount(const std::string& word);
    size_t getWordCountInDoc(const std::string& word, const size_t doc_id) const; // ADDITIONAL METHOD

private:    
    void indexTheFile(const std::string& fileContent, size_t docId);
    std::map<int, std::string> document_list;
    static std::mutex mutexIndexMap; 
    std::map<std::string, std::vector<Entry>> frequencyDictionary; 
    bool indexingIsOngoing;
};