#include "invert_in.h"

const int HEADER_SPACER = 15;

std::mutex InvertedIndex::mutexIndexMap;

/*
* update or fill the documents base in which search will be performed
*/
void InvertedIndex::updateDocumentBase(const std::vector<std::string>& input_docs)
{
	if (input_docs.empty())
	{
		std::cerr << "\tindexing: no content in docs content base\n";
		return;
	}

	indexingIsOngoing = true;

	frequencyDictionary.clear();
	size_t docId = 0;
	for (const auto& content : input_docs)
	{
		std::thread index([this, &content, docId]() {indexTheFile(content, docId); });
		++docId;
		index.join();
	}
	indexingIsOngoing = false;
}

/*
* get the count of \'word\' entries in ready documents base	
*/
std::vector<Entry> InvertedIndex::getWordCount(const std::string& word)
{
	if (indexingIsOngoing)
	{
		std::cout << "index is ongoing, please repeat the request later.\n";
		return {};
	}
	auto it = frequencyDictionary.find(word);
	if (it != frequencyDictionary.end())
	{
		return it->second;
	}
	else
	{
		return {};
	}
}

/*
* perform the indexing of the separate file
 */
void InvertedIndex::indexTheFile(const std::string& fileContent, size_t docId)
{
	std::map<std::string, Entry> fileFreqDictionary;
	Entry entry{};
	entry.doc_id = docId;
	entry.count = 1;
	std::istringstream ist(fileContent);
	for (std::string word; ist >> word; )
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });

		std::pair<std::string, Entry> file_word_frequency{ word, entry };
		if (!fileFreqDictionary.emplace(file_word_frequency).second)
		{
			fileFreqDictionary.find(word)->second.count += 1;
		}
	}
	mutexIndexMap.lock();
	for (const auto& wordIterator : fileFreqDictionary)
	{
		std::pair<std::string, std::vector<Entry>> wordFrequency;
		wordFrequency.first = wordIterator.first;
		std::vector<Entry> entryVector{ wordIterator.second };
		wordFrequency.second = entryVector;
		if (!frequencyDictionary.emplace(wordFrequency).second)
		{
			frequencyDictionary.find(wordFrequency.first)->second.push_back(wordIterator.second);
		}
	}
	mutexIndexMap.unlock();
}

/*
* get the word count in certain document	 
*/
size_t InvertedIndex::getWordCountInDoc(const std::string& word, const size_t doc_id) const
{
	if (indexingIsOngoing) {
		std::cout << "index is ongoing, please repeat the request later.\n";
		return 0;
	}
	size_t wordCountInDoc = 0;
	auto it = frequencyDictionary.find(word);
	if (it != frequencyDictionary.end()) {
		auto entryVector = it->second;
		for (auto entry : entryVector) {
			if (entry.doc_id == doc_id) wordCountInDoc += entry.count;
		}
	}
	else {
		std::cout << "word \"" << word << "\" not found.\n";
	}
	return wordCountInDoc;
}