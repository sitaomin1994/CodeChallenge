#include "longest_strand.h"

int main() {

    //time measure
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();

    //file names
    std::vector<std::string> file_name = {};

    //read files name
    std::string path = "../data/";
    std::cout << fs::current_path() << std::endl;
    for (const auto &entry : fs::directory_iterator(path))
        file_name.push_back(entry.path());

    std::cout << "Reading data from " << path << std::endl;
    std::cout << "There are " << file_name.size() << " bytes files." << std::endl;

    //all combination of file pairs
    std::vector<std::pair<std::string, std::string>> file_pairs = generate_file_pairs(file_name);

    //Main process
    std::vector<std::tuple<std::string, std::string, int, int, int>> results;

    //iterate all pairs
    for (auto & file_pair : file_pairs){

        //seq1 and seq2
        std::vector<char> seq1 = get_file_content(file_pair.first);
        std::vector<char> seq2 = get_file_content(file_pair.second);

        //get longest sub strand
        auto result = longest_sub_strand(seq1, seq2);
        auto result_all = std::make_tuple(file_pair.first, file_pair.second, std::get<0>(result), std::get<1>(result), std::get<2>(result));
        results.push_back(result_all);

    }

    auto t2 = high_resolution_clock::now();

    //Display result result
    display_result(results);

    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Execution time: " << ms_int.count()/1000 << "s" << std::endl;

    return 0;
}

/**
 * get byte strands from file
 * @param file_name path of the filename
 * @return vector of byte strands
 */
std::vector<char> get_file_content(const std::string& file_name){

    const std::string& inputFile = file_name;
    std::ifstream infile(inputFile, std::ios_base::binary);
    std::vector<char> seq( (std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>() );

    return seq;
}

/**
 * generate all pairs of files from a list of files
 * @param file_name a list of files
 * @return file_pairs - all pairs of files
 */
std::vector<std::pair<std::string, std::string>> generate_file_pairs(std::vector<std::string> file_name){
    std::vector<std::pair<std::string, std::string>> file_pairs = {};
    for (auto i = file_name.begin(); i != file_name.end(); ++i) {
        for (auto j = i; ++j != file_name.end();) {
            file_pairs.emplace_back(*i, *j);
        }
    }
    return file_pairs;
}

/**
 * Find longest common sub strand between two byte sequences
 * @param seq1 sequence 1
 * @param seq2 sequence 2
 * @return tuple of length of common strands, offset of 1st sequence, offset of 2nd sequence
 */
std::tuple<int, int, int> longest_sub_strand(std::vector<char> seq1, std::vector<char> seq2){

    /**
     * solving problem using dynamic programming
     */
    int m = seq1.size();
    int n = seq2.size();

    /**
     * Create a table to store lengths of longest common suffixes of substrings.
     * Note that dp_table[i][j] contains the length of longest common suffix of X[0...i-1] and Y[0...j-1]
     */
    std::vector<std::vector<int>> dp_table (m+1, std::vector<int> (n+1));

    int length = 0;
    int offset1 = 0, offset2 = 0;

    for(int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if(i == 0 || j ==0){
                dp_table[i][j] = 0;
            }else if(seq1[i-1] == seq2[j-1]){
                dp_table[i][j] = dp_table[i-1][j-1] + 1;
                if(dp_table[i][j] > length){
                    length = dp_table[i][j];
                    offset1 = i;
                    offset2 = j;
                }
            }else{
                dp_table[i][j] = 0;
            }
        }
    }

    return std::make_tuple(length, offset1 - length, offset2 - length);
}

/**
 * Comparator
 * @param a a tuple of result
 * @param b a tuple of result
 * @return compare result
 */
bool comp(const std::tuple<std::string, std::string, int, int, int>& a,
          const std::tuple<std::string, std::string, int, int, int>& b)
{
    return (std::get<2>(a) < std::get<2>(b));
}

/**
 * display the result of algorithm
 * @param results - results contains all information
 */
void display_result(std::vector<std::tuple<std::string, std::string, int, int, int>> results){

    //Display result result
    auto max_element = std::max_element(results.begin(), results.end(), comp);
    std::string file_name1 = std::get<0>(*max_element);
    std::string file_name2 = std::get<1>(*max_element);
    int length = std::get<2>(*max_element);
    int offset1 = std::get<3>(*max_element);
    int offset2 = std::get<4>(*max_element);

    std::cout << "====================================================================" << std::endl;
    std::cout << "Maximum common strands is between " << file_name1 << "and" << file_name2 << ":" << std::endl;
    std::cout << "length of common strands:" << length << std::endl;
    std::cout << "offset of " << file_name1 << " : " << offset1  << std::endl;
    std::cout << "offset of " << file_name2 << " : " << offset2  << std::endl;
    std::cout << "=====================================================================" << std::endl;
}
