//
// Created by mark on 12/23/18.
//

#include "file_repository.h"

file_repository::file_repository(std::string & path)
    : bricks_path(path) { }

std::string file_repository::build_filepath(int32_t & brick_identificator)
{
    std::stringstream filepath_stream;
    filepath_stream << bricks_path;
    if (bricks_path.back() != PATH_SEPARATOR)
        filepath_stream << PATH_SEPARATOR;
    filepath_stream << brick_identificator << brick_extension;
    return filepath_stream.str();
}

#ifdef _WIN32

std::vector<std::string> file_repository::get_brick_filenames()
{
	std::vector<std::string> brick_filenames;
	std::string search_path = bricks_path;
	if (bricks_path.back() != PATH_SEPARATOR)
		search_path += PATH_SEPARATOR;
	std::string path_pattern = search_path + "*." + brick_extension;
	WIN32_FIND_DATA find_data;
	HANDLE find_handler = FindFirstFile(path_pattern.c_str(), &find_data);
	if (find_handler != INVALID_HANDLE_VALUE)
	{
		do {
			if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				brick_filenames.push_back(find_data.cFileName);
		} while (FindNextFile(find_handler, &find_data));
		FindClose(find_handler);
	}
	return brick_filenames;
}

#else

std::vector<std::string> file_repository::get_brick_filenames()
{
    const std::regex re("\\d+?" + brick_extension);
    DIR * directory;
    struct dirent * entry;
    std::vector<std::string> brick_filenames;
    int32_t brick_number;
    std::vector<int32_t> brick_numbers;
    if ((directory = opendir(bricks_path.c_str())) != nullptr)
    {
        while ((entry = readdir(directory)) != nullptr)
        {
            std::string filename = entry->d_name;
            std::smatch match;
            if (std::regex_search(filename, match, re)) {
                brick_number = std::stoi(filename);
                brick_numbers.push_back(brick_number);
            }
        }
    }
    std::sort(brick_numbers.begin(), brick_numbers.end());
    for (int32_t & _brick_number : brick_numbers)
    {
        std::stringstream brick_stream;
        brick_stream << _brick_number << ".brick";
        brick_filenames.push_back(brick_stream.str());
    }
    return brick_filenames;
}

#endif // _WIN32

std::vector<int32_t> file_repository::get_identificators()
{
    std::vector<std::string> filenames = get_brick_filenames();
    std::vector<int32_t> brick_numbers(filenames.size());
    for (auto & filename : filenames)
        brick_numbers.push_back(std::stoi(filename));
    return brick_numbers;
}

void file_repository::load_brick(brick * empty_brick, int32_t & brick_identificator)
{
    std::string brick_filename = build_filepath(brick_identificator);
    std::string line;
    std::vector<std::string> lines;
    std::ifstream brick_file(brick_filename);
    if (brick_file.is_open())
    {
        while (std::getline(brick_file, line))
            lines.push_back(line);

        transaction transaction;
        empty_brick->set_header_hash(lines.at(0));
        empty_brick->set_previous_hash(lines.at(1));
        int32_t nonce = std::stoi(lines.at(2));
        empty_brick->set_nonce(nonce);
        empty_brick->set_bits(lines.at(3));
        long brick_timestamp = std::stol(lines.at(4));
        empty_brick->set_timestamp(brick_timestamp);
        transaction.set_sender(lines.at(5));
        transaction.set_receiver(lines.at(6));
        transaction.set_content(lines.at(7));
        long transaction_timestamp = std::stol(lines.at(8));
        transaction.set_timestamp(transaction_timestamp);
        empty_brick->set_transaction(transaction);
        empty_brick->set_identificator(brick_identificator);
    }
}

void file_repository::save_brick(brick & filled_brick, int32_t & brick_identificator)
{
    std::string brick_filename = build_filepath(brick_identificator);
    std::ofstream brick_file(brick_filename);
    if (brick_file.is_open())
    {
        brick_file << filled_brick.get_header_hash() << std::endl;
        brick_file << filled_brick.get_previous_hash() << std::endl;
        brick_file << filled_brick.get_nonce() << std::endl;
        brick_file << filled_brick.get_bits() << std::endl;
        brick_file << filled_brick.get_timestamp() << std::endl;
        transaction transaction = filled_brick.get_transaction();
        brick_file << transaction.get_sender() << std::endl;
        brick_file << transaction.get_receiver() << std::endl;
        brick_file << transaction.get_content() << std::endl;
        brick_file << transaction.get_timestamp() << std::endl;

        brick_file.close();
    }
}
