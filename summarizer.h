#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

string cleanUpText(string s);
string trimSpaces(string s);
string strToLower(string s);
vector<string> strToVec(string s);
bool checkIfStopWord(string s);
vector<string> getWords(string s);
vector<string> getSentences(string s);
map<string, int> getWordCount(vector<string> words);
map<string, double> getTFWords(map<string, int> wordCount, int totalWords);
map<int, double> getTFSentences(vector<string> sentences, map<string, double> tfWords);
map<string, double> getIDFWords(map<string, int> wordCount, int totalSentences);
map<int, double> getIDFSentences(vector<string> sentences, map<string, double> idfWords);
map<int, double> getTFIDF(vector<string> sentences, map<int, double> tf, map<int, double> idf);
vector<pair<int, double>> sortTFIDF(map<int, double> tfidf);
vector<pair<int, double>> getSummary(string paragraph);

vector<pair<int, double>> getSummary(string paragraph)
{
    vector<string> words = getWords(paragraph);
    vector<string> sentences = getSentences(paragraph);

    map<string, int> wordCount = getWordCount(words);

    map<string, double> tfWords = getTFWords(wordCount, words.size());
    map<int, double> tfSentences = getTFSentences(sentences, tfWords);

    map<string, double> idfWords = getIDFWords(wordCount, sentences.size());
    map<int, double> idfSentences = getIDFSentences(sentences, idfWords);

    map<int, double> tfidf = getTFIDF(sentences, tfSentences, idfSentences);
    vector<pair<int, double>> sortedTFIDF = sortTFIDF(tfidf);
    /*
	for(auto pair: sortedTFIDF){
	 	cout << sentences[pair.first] << " --> " << pair.second << "\n\n";
	}
	*/
    return sortedTFIDF;
}

vector<pair<int, double>> sortTFIDF(map<int, double> tfidf)
{
    vector<pair<int, double>> sorted;
    copy(tfidf.begin(), tfidf.end(), back_inserter<vector<pair<int, double>>>(sorted));
    sort(sorted.begin(), sorted.end(),
         [](const pair<int, double> &l, const pair<int, double> &r) {
             return l.second > r.second;
         });
    return sorted;
}

map<int, double> getTFIDF(vector<string> sentences, map<int, double> tf, map<int, double> idf)
{
    map<int, double> tfidf;
    for (int i = 0; i < sentences.size(); i++)
    {
        tfidf[i] = tf[i] * idf[i];
    }
    return tfidf;
}

map<int, double> getIDFSentences(vector<string> sentences, map<string, double> idfWords)
{
    map<int, double> idfSentences;
    for (int i = 0; i < sentences.size(); i++)
    {
        vector<string> words = getWords(sentences[i]);
        double total_idf_words = 0;
        for (string word : words)
        {
            total_idf_words += idfWords[word];
        }
        idfSentences[i] = total_idf_words / words.size();
    }
    return idfSentences;
}

map<string, double> getIDFWords(map<string, int> wordCount, int totalSentences)
{
    map<string, double> idfWords;
    for (auto pair : wordCount)
    {
        idfWords[pair.first] = log10(totalSentences / (pair.second * 1.0));
    }
    return idfWords;
}

map<int, double> getTFSentences(vector<string> sentences, map<string, double> tfWords)
{
    map<int, double> tfSentences;
    for (int i = 0; i < sentences.size(); i++)
    {
        vector<string> words = getWords(sentences[i]);
        double total_tf_words = 0;
        for (string word : words)
        {
            total_tf_words += tfWords[word];
        }
        tfSentences[i] = total_tf_words / words.size();
    }
    return tfSentences;
}

map<string, double> getTFWords(map<string, int> wordCount, int totalWords)
{
    map<string, double> tfWords;
    for (auto pair : wordCount)
        tfWords[pair.first] = (pair.second * 1.0) / totalWords;
    return tfWords;
}

map<string, int> getWordCount(vector<string> words)
{
    map<string, int> wordCount;
    for (int i = 0; i < words.size(); i++)
    {
        string word = words[i];
        if (wordCount.find(word) != wordCount.end())
        {
            int currCount = wordCount[word];
            wordCount[word] = ++currCount;
        }
        else
        {
            wordCount.insert(make_pair(word, 1));
        }
    }
    return wordCount;
}

vector<string> getSentences(string s)
{
    vector<string> strVec;
    stringstream ss(s);
    string temp;
    while (getline(ss, temp, '.'))
    {
        strVec.push_back(temp);
    }
    return strVec;
}

vector<string> getWords(string s)
{
    s = cleanUpText(s);
    vector<string> words = strToVec(s);
    return words;
}

string cleanUpText(string s)
{

    string regex_patterns[] = {"[\'/]\\w", "[\'\"!@#$%^&*,.]", "\\s+"};
    //Clean up text - remove punctuations and multiple spaces.
    for (int i = 0; i < 3; i++)
    {
        regex r(regex_patterns[i]);
        s = (i == 0 ? regex_replace(s, r, "") : regex_replace(s, r, " "));
    }
    return s;
}

string strToLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

vector<string> strToVec(string s)
{
    vector<string> strVec;
    stringstream ss(s);
    string temp;
    while (getline(ss, temp, ' '))
    {
        if (!checkIfStopWord(temp))
            strVec.push_back(strToLower(temp));
        continue;
    }
    return strVec;
}

bool checkIfStopWord(string s)
{
    vector<string> stopwords = {"a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during", "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their", "theirs", "them", "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours", "yourself", "yourselves", "us", "also", "can", "keep", "just", "it", "in"};

    return (find(stopwords.begin(), stopwords.end(), s) != stopwords.end());
}
